#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constant.h"

using namespace llvm;

namespace passo3 {
        // si ritorna varOp SOLO se abbiamo trovato che le due operazioni siano duali  (es sub ==> mul) e che le costanti siano uguali
    // sono gestiti TUTTI i casi ovvero:
    // Nel caso classico abbiamo:    a=b/3  c=3*a oppure c=a*3
    // Se  la prima istruzione  è sum e mul potrebbero avere due costanti es  "mul 5,3" e cercheremo entrambi i casi!

    Value* trova_op_duale(BinaryOperator *BinOp, BinaryOperator *NextBinOp) {
        int64_t constVal = 0;
        int64_t constVal2 = 0;
        Value *varOp = nullptr;
    
        // Identifica la costante e la variabile in BinOp
        if (auto *C1 = dyn_cast<ConstantInt>(BinOp->getOperand(1))) {
            constVal = C1->getSExtValue();
            varOp = BinOp->getOperand(0);  
        } else if (auto *C2 = dyn_cast<ConstantInt>(BinOp->getOperand(0))) {
            constVal = C2->getSExtValue();
            varOp = BinOp->getOperand(1); 
        }
    
        // Identifica la costante in NextBinOp
        if (auto *C1 = dyn_cast<ConstantInt>(NextBinOp->getOperand(1))) {
            constVal2 = C1->getSExtValue();
        } else if (auto *C2 = dyn_cast<ConstantInt>(NextBinOp->getOperand(0))) {
            constVal2 = C2->getSExtValue();
        }
    
        // Verifica se le operazioni sono duali e restituisce la variabile per il replace
        if ((BinOp->getOpcode() == Instruction::Add && NextBinOp->getOpcode() == Instruction::Sub && constVal == constVal2) ||
            (BinOp->getOpcode() == Instruction::Sub && NextBinOp->getOpcode() == Instruction::Add && constVal == constVal2) ||
            (BinOp->getOpcode() == Instruction::Mul && NextBinOp->getOpcode() == Instruction::SDiv && constVal == constVal2 && constVal != 0) ||
            (BinOp->getOpcode() == Instruction::SDiv && NextBinOp->getOpcode() == Instruction::Mul && constVal == constVal2 && constVal != 0) ||
            (BinOp->getOpcode() == Instruction::Shl && NextBinOp->getOpcode() == Instruction::LShr && constVal == constVal2) ||
            (BinOp->getOpcode() == Instruction::LShr && NextBinOp->getOpcode() == Instruction::Shl && constVal == constVal2) ||
            (BinOp->getOpcode() == Instruction::Shl && NextBinOp->getOpcode() == Instruction::AShr && constVal == constVal2) ||
            (BinOp->getOpcode() == Instruction::AShr && NextBinOp->getOpcode() == Instruction::Shl && constVal == constVal2)) {
                //outs() << "Ottimizzazione effettuata: caso regolare\n";   per debug
            return varOp;
        }
    
    
        //Nel caso di mul e add potrei avere che BinOp siano due operandi costanti!  (vedi codice del test)
        // es    %1 = mul  3 , 5
        //       %2 = div %1 , 3     E anche %2 = div %1 , 5    sono ottimizzabili
        // attualmente quindi abbiamo controllato (per add/mul) solo il caso con la costante a 2° operando quindi testo anche l'altro
        if (BinOp->getOpcode() == Instruction::Add  ||  BinOp->getOpcode() == Instruction::Mul){
            if (auto *C = dyn_cast<ConstantInt>(BinOp->getOperand(0))){
                constVal = C->getSExtValue();
                varOp = BinOp->getOperand(1);
            }
            //verifico che ho una operazione duale alla add / mul
            if ((BinOp->getOpcode() == Instruction::Add && NextBinOp->getOpcode() == Instruction::Sub && constVal == constVal2) ||
                    (BinOp->getOpcode() == Instruction::Mul && NextBinOp->getOpcode() == Instruction::SDiv && constVal == constVal2 && constVal != 0)   ){
                        //outs() << "Ottimizzazione effettuata: caso 'speciale' per add/mul\n";    Per debug
                        return varOp;
                    }
        }
    
    
        return nullptr;
    }
    
    
    
    // in questa funzione avviene il controllo di idoneità tra BinOp (la istruzione in questione) e le successive, sono idonee se:
    // - entrambi hanno una costante , la successiva USA la prima e l'operazione è la duale    [per add e mul si considera la commutatività]
    //  es:  se ho  BinOP:   a=b-C   allora è idonea   c=a+C  oppure  c=C+a           ("C" costante) 
    //  il controllo che effettivamente le costanti siano uguali e le operazioni duali  viene lasciato a "trova_op_duali"
    bool controlla_prossime_istruzioni(BinaryOperator *BinOp) {
        bool modifica = false;
        Value *X = BinOp->getOperand(0);
        Value *Y = BinOp->getOperand(1);
    
        if (dyn_cast<ConstantInt>(Y) || 
            ((BinOp->getOpcode() == Instruction::Add || BinOp->getOpcode() == Instruction::Mul) && dyn_cast<ConstantInt>(X))) {
            
            std::vector<Instruction*> to_erase;
            
            for (User *U : BinOp->users()) {
                if (Instruction *NextInst = dyn_cast<Instruction>(U)) {
                    if (auto *NextBinOp = dyn_cast<BinaryOperator>(NextInst)) {
                        Value *A = NextBinOp->getOperand(0);
                        Value *B = NextBinOp->getOperand(1);
                        
                        if (A == BinOp || ((NextBinOp->getOpcode() == Instruction::Add || NextBinOp->getOpcode() == Instruction::Mul) && B == BinOp)) {
                            Value *replacement = trova_op_duale(BinOp, NextBinOp);
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
    
    
    //per ogni istruzione binaria cerca tra le prossime istruzioni una potenziale istruzione "duale"  
    bool runOnBasicBlock(BasicBlock &B) {
        bool modifica = false;
        for (auto Iter = B.begin(); Iter != B.end(); ++Iter) {
            if (auto *BinOp = dyn_cast<BinaryOperator>(&*Iter)) {
                if (controlla_prossime_istruzioni(BinOp))
                    modifica = true;
            }
        }
        return modifica;
    }
    
    
    
    
    
    
    bool runOnFunction(Function &F) {
        bool Transformed = false;
        for (auto &BB : F) {
            if (runOnBasicBlock(BB))
                Transformed = true;
        }
        return Transformed;
    }
}




