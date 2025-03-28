#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {
    bool changed = false;

    for (auto Iter = B.begin(); Iter != B.end(); ) {  // Iteriamo sulle istruzioni del BasicBlock
        Instruction &Inst = *Iter++;
        
        if (BinaryOperator *BinOP = dyn_cast<BinaryOperator>(&Inst)) {  // Corretto il cast
            Value *OP1 = BinOP->getOperand(0);
            Value *OP2 = BinOP->getOperand(1);

            if (BinOP->getOpcode() == Instruction::Add) {  // Controlla se è una somma
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    if (C->isZero()) {
                        BinOP->replaceAllUsesWith(OP1);
                        Iter = BinOP->eraseFromParent(); // Iter aggiornato per evitare invalid iterator
                        changed = true;
                        continue;
                    }
                }
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP1)) {
                    if (C->isZero()) {
                        BinOP->replaceAllUsesWith(OP2);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }
            }

            if (BinOP->getOpcode() == Instruction::Sub) {  // Controlla se è una sottrazione
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    if (C->isZero()) {
                        BinOP->replaceAllUsesWith(OP1);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }
            }

            if (BinOP->getOpcode() == Instruction::Mul) {  // Controlla se è una moltiplicazione
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    if (C->isOne()) {
                        BinOP->replaceAllUsesWith(OP1);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP1)) {
                    if (C->isOne()) {
                        BinOP->replaceAllUsesWith(OP2);
                        Iter = BinOP->eraseFromParent();
                        changed = true;
                        continue;
                    }
                }
            }

            if (BinOP->getOpcode() == Instruction::SDiv) {  // Controlla se è una divisione
                if (ConstantInt *C = dyn_cast<ConstantInt>(OP2)) {
                    if (C->isOne()) {
                        BinOP->replaceAllUsesWith(OP1);
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
