#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constant.h"

using namespace llvm;

// Funzione per verificare se un numero è una potenza di 2
bool isPowerOfTwo(int64_t num) {
    return num > 0 && (num & (num - 1)) == 0;
}

bool runOnBasicBlock(BasicBlock &B) {
    bool changed = false;

    for (auto Iter = B.begin(); Iter != B.end(); ) {  // Iteriamo sulle istruzioni del BasicBlock
        Instruction &Inst = *Iter++;

        if (BinaryOperator *BinOP = dyn_cast<BinaryOperator>(&Inst)) {  // Controlla se è un'operazione binaria
            Value *OP1 = BinOP->getOperand(0);
            Value *OP2 = BinOP->getOperand(1);

            if (BinOP->getOpcode() == Instruction::Mul) {  // Controlla se è una moltiplicazione
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {  // Verifica se l'operando destro è una costante
                    int64_t num = C->getSExtValue(); // Estrai il valore della costante con segno

                    // Controlla se num, num-1 o num+1 sono potenze di 2
                    if (isPowerOfTwo(num)) {
                        // Sostituisci con uno shift a sinistra
                        Instruction *newInst = BinaryOperator::CreateShl(OP1, ConstantInt::get(C->getType(), log2(num)), "", &Inst);
                        BinOP->replaceAllUsesWith(newInst);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    } else if (isPowerOfTwo(num - 1)) {
                        // Sostituisci con shift e sottrazione
                        Instruction *shlInst = BinaryOperator::CreateShl(OP1, ConstantInt::get(C->getType(), log2(num - 1)), "", &Inst);
                        Instruction *subInst = BinaryOperator::CreateSub(shlInst, OP1, "", &Inst);
                        BinOP->replaceAllUsesWith(subInst);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    } else if (isPowerOfTwo(num + 1)) {
                        // Sostituisci con shift e somma
                        Instruction *shlInst = BinaryOperator::CreateShl(OP1, ConstantInt::get(C->getType(), log2(num + 1)), "", &Inst);
                        Instruction *addInst = BinaryOperator::CreateAdd(shlInst, OP1, "", &Inst);
                        BinOP->replaceAllUsesWith(addInst);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }

                // Gestione caso particolare: moltiplicazione con 0
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP1)) {
                    if (C->isZero()) {
                        // Sostituisci con 0
                        BinOP->replaceAllUsesWith(C);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }

                // Gestione caso particolare: moltiplicazione con numeri negativi
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    if (C->isNegative()) {
                        int64_t absNum = -C->getSExtValue();
                        if (isPowerOfTwo(absNum)) {
                            // Esegui uno shift e una sottrazione
                            Instruction *shlInst = BinaryOperator::CreateShl(OP1, ConstantInt::get(C->getType(), log2(absNum)), "", &Inst);
                            Instruction *subInst = BinaryOperator::CreateSub(ConstantInt::get(C->getType(), 0), shlInst, "", &Inst);
                            BinOP->replaceAllUsesWith(subInst);
                            Iter = BinOP->eraseFromParent();
                            changed = true;
                            continue;
                        }
                    }
                }
            }

            if (BinOP->getOpcode() == Instruction::SDiv) {  // Controlla se è una divisione
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    int64_t num = C->getSExtValue();

                    // Controlla se l'operando destro è una potenza di 2
                    if (isPowerOfTwo(num)) {
                        // Sostituisci con uno shift a destra aritmetico, non logico
                        Instruction *newInst = BinaryOperator::CreateAShr(OP1, ConstantInt::get(C->getType(), log2(num)), "", &Inst);
                        BinOP->replaceAllUsesWith(newInst);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }
            }
        }
    }

    return changed;
}

bool runOnFunction(Function &F) {
    bool Transformed = false;

    for (auto &BB : F) {  // Itera direttamente sui BasicBlock della funzione
        if (runOnBasicBlock(BB)) {
            Transformed = true;
        }
    }

    return Transformed;
}
