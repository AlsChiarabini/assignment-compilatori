#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constant.h"

using namespace llvm;

//la funzione controlla se le due operazioni sono "duali" ovvero semplificabili
Value* trova_op_duale(BinaryOperator *BinOp, BinaryOperator *NextBinOp, Value *X, int64_t constVal, int64_t constVal2) {
   
    if (BinOp->getOpcode() == Instruction::Add &&                        // Caso: a = b + C, c = a - C  =>  c = b
        NextBinOp->getOpcode() == Instruction::Sub &&
        constVal == constVal2) {
        return X;
    }      
    else if (BinOp->getOpcode() == Instruction::Sub &&                  // Caso: a = b - C, c = a + C  =>  c = b
             NextBinOp->getOpcode() == Instruction::Add &&
             constVal == constVal2) {
        return X;
    }
    else if (BinOp->getOpcode() == Instruction::Mul &&                  // Caso: a = b * C, c = a / C → c = b
             NextBinOp->getOpcode() == Instruction::SDiv &&
             constVal == constVal2 && constVal != 0) {
        return X;
    }
    else if (BinOp->getOpcode() == Instruction::SDiv &&                 // Caso: a = b / C, c = a * C → c = b
             NextBinOp->getOpcode() == Instruction::Mul &&
             constVal == constVal2 && constVal != 0) {
        return X;
    }
    return nullptr;
}

// estendo quella zioporco di funzione prima, con il caso commutativo, 
// non la faccio dentro quella prima perché non voglio toccar niente
// Solo add e mul perché ordine non importante
Value* trova_op_duale_commutativo(BinaryOperator *BinOp, BinaryOperator *NextBinOp, Value *X, Value *Y, int64_t constVal, int64_t constVal2) {
    // Verifica se l'operazione è commutativa
    bool is_commutative = (BinOp->getOpcode() == Instruction::Add || BinOp->getOpcode() == Instruction::Mul);
    
    // Se non è commutativa, usa solo la funzione originale
    if (!is_commutative) {
        return trova_op_duale(BinOp, NextBinOp, X, constVal, constVal2);
    }
    
    // Per operazioni commutative, prova entrambi i casi
    // Inizio provando il primo caso, quindi variabile al primo posto: a = X op C
    Value* result = trova_op_duale(BinOp, NextBinOp, X, constVal, constVal2);
    if (result) return result;
    
    // Altrimenti costante al primo posto: a = C op X (caso commutativo)
    // Per Add: C + X → soggetto a X + C
    if (BinOp->getOpcode() == Instruction::Add && 
        NextBinOp->getOpcode() == Instruction::Sub &&
        constVal == constVal2) {
        return Y;
    }
    // Per Mul: C * X → soggetto a X * C
    else if (BinOp->getOpcode() == Instruction::Mul && 
             NextBinOp->getOpcode() == Instruction::SDiv &&
             constVal == constVal2 && constVal != 0) {
        return Y;
    }
    
    return nullptr;
}

// Data una istruzione binaria controlla le successive e chiama "trova_op_duale" per controllare se semplificabili
bool controlla_prossime_istruzioni(BinaryOperator *BinOp, BasicBlock::iterator Iter, BasicBlock &BB) {
    bool modifica = false;
    Value *X = BinOp->getOperand(0);
    Value *Y = BinOp->getOperand(1);
    
    // Caso 1: Y è una costante (caso nell'originale)
    if (auto *C1 = dyn_cast<ConstantInt>(Y)) {
        int64_t constVal = C1->getSExtValue();
        
        // Prima si bloccava, ora creo un vettore ed elimino tutte insieme 
        std::vector<Instruction*> to_erase;
        
        // Scorro x trovare duale
        for (auto NextIter = std::next(Iter); NextIter != BB.end(); ++NextIter) {
            Instruction *NextInst = &*NextIter;
            
            if (auto *NextBinOp = dyn_cast<BinaryOperator>(NextInst)) { // Se la prossima istruzione è una binaria (?)
                Value *A = NextBinOp->getOperand(0);
                Value *B = NextBinOp->getOperand(1);
                
                if (A == BinOp) {                       // quindi la seconda usa la prima
                    if (auto *C2 = dyn_cast<ConstantInt>(B)) {
                        int64_t constVal2 = C2->getSExtValue();
                        
                        // Siamo nella situazione "Binop = X <op> c1; ..;  NextBinop = Binop <op> c2"
                        Value *replacement = trova_op_duale(BinOp, NextBinOp, X, constVal, constVal2);
                        
                        // Se replacement allora trovata operazione duale e quindi semplificabile con "X"
                        if (replacement) {
                            NextBinOp->replaceAllUsesWith(replacement);
                            to_erase.push_back(NextBinOp);
                            modifica = true;
                        }
                    }
                }
            }
        }
        
        // Elimino tutto insieme a fine ciclo interno ZIOPORCO ZIOPROCO ZIOPORCO
        for (auto *Inst : to_erase) {
            Inst->eraseFromParent();
        }
    }
    
    // Caso 2: X è una costante (caso commutativo aggiunto, funziona? Non ne ho idea, qualcosa toglie)
    else if (auto *C1 = dyn_cast<ConstantInt>(X)) {
        int64_t constVal = C1->getSExtValue();
        
        std::vector<Instruction*> to_erase;
        
        for (auto NextIter = std::next(Iter); NextIter != BB.end(); ++NextIter) {
            Instruction *NextInst = &*NextIter;
            
            if (auto *NextBinOp = dyn_cast<BinaryOperator>(NextInst)) {
                Value *A = NextBinOp->getOperand(0);
                Value *B = NextBinOp->getOperand(1);
                
                if (A == BinOp) {
                    if (auto *C2 = dyn_cast<ConstantInt>(B)) {
                        int64_t constVal2 = C2->getSExtValue();
                        
                        // Siamo nella situazione "Binop = c1 <op> Y; ..;  NextBinop = Binop <op> c2"
                        Value *replacement = trova_op_duale_commutativo(BinOp, NextBinOp, X, Y, constVal, constVal2);
                        
                        if (replacement) {
                            NextBinOp->replaceAllUsesWith(replacement);
                            to_erase.push_back(NextBinOp);
                            modifica = true;
                        }
                    }
                }
            }
        }
        
        for (auto *Inst : to_erase) {
            Inst->eraseFromParent();
        }
    }
    
    return modifica;
}

bool runOnBasicBlock(BasicBlock &B) {
    bool changed = false;
    
    for (auto Iter = B.begin(); Iter != B.end(); ++Iter) {
        Instruction *Inst = &*Iter;
        
        if (auto *BinOp = dyn_cast<BinaryOperator>(Inst)) {
            if (controlla_prossime_istruzioni(BinOp, Iter, B))
                changed = true;
        }
    }
    
    return changed;
}

bool runOnFunction(Function &F) {
    bool Transformed = false;
    for (auto &BB : F) {
        if (runOnBasicBlock(BB))
            Transformed = true;
    }
    return Transformed;
}