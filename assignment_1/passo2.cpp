#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constant.h"
#include <cmath>

using namespace llvm;

namespace passo2 {
    bool changed = false;

    // funzione ottimizzata usando l'operatore AND bit a bit
    bool isPowerOfTwo(int64_t num) {
        return num > 0 && (num & (num - 1)) == 0;
    }

    /*  casi ottimizzati:
    *   x * 16  =  16 *  x =  (x<<4)
    *   x * 15 = 15* x  = (x<<4) -x    /    x*17 duale
    *   x * 0  = 0 * x = 0
    *   x * (-16) =  0 - (x << 4)
    */
    bool optimizeMul(BinaryOperator *BinOP) {
        if (BinOP->getOpcode() == Instruction::Mul) {
            Value *replacement = nullptr;
            for (int i = 0; i < 2; ++i) {
                if (ConstantInt *C = dyn_cast<ConstantInt>(BinOP->getOperand(i))) {
                    Value *otherOp = BinOP->getOperand(1 - i);
                    int64_t num = C->getSExtValue();

                    if (isPowerOfTwo(num)) {
                        replacement = BinaryOperator::CreateShl(otherOp, ConstantInt::get(C->getType(), log2(num)), "", BinOP);
                    } else if (isPowerOfTwo(num - 1)) {
                        Instruction *shlInst = BinaryOperator::CreateShl(otherOp, ConstantInt::get(C->getType(), log2(num - 1)), "", BinOP);
                        replacement = BinaryOperator::CreateSub(shlInst, otherOp, "", BinOP);
                    } else if (isPowerOfTwo(num + 1)) {
                        Instruction *shlInst = BinaryOperator::CreateShl(otherOp, ConstantInt::get(C->getType(), log2(num + 1)), "", BinOP);
                        replacement = BinaryOperator::CreateAdd(shlInst, otherOp, "", BinOP);
                    } else if (C->isZero()) {       //vedi terzo caso nel commento
                        replacement = C;
                    } else if (C->isNegative()) {       //vedi quarto caso nel commento
                        int64_t absNum = -num;
                        if (isPowerOfTwo(absNum)) {
                            Instruction *shlInst = BinaryOperator::CreateShl(otherOp, ConstantInt::get(C->getType(), log2(absNum)), "", BinOP);
                            replacement = BinaryOperator::CreateSub(ConstantInt::get(C->getType(), 0), shlInst, "", BinOP);
                        }
                    }
                    
                    //se rilevata una ottimizzazione: esegui
                    if (replacement) {
                        BinOP->replaceAllUsesWith(replacement);
                        BinOP->eraseFromParent();
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /* casi ottimizzati:
    *  x / 8 =  (x>>3)
    *  x / (-8) = 0 - (x>>3)
    */
    bool optimizeDiv(BinaryOperator *BinOP) {
        if (BinOP->getOpcode() == Instruction::SDiv) {
            if (ConstantInt *C = dyn_cast<ConstantInt>(BinOP->getOperand(1))) {
                int64_t num = C->getSExtValue();
                if (isPowerOfTwo(std::abs(num))) {
                    int shiftVal = static_cast<int>(log2(std::abs(num)));
                    Instruction *shiftInst = BinaryOperator::CreateAShr(BinOP->getOperand(0), ConstantInt::get(C->getType(), shiftVal), "", BinOP);
                    
                    if (num < 0) {
                        Instruction *negInst = BinaryOperator::CreateSub(ConstantInt::get(BinOP->getType(), 0), shiftInst, "", BinOP);
                        BinOP->replaceAllUsesWith(negInst);
                    } else {
                        BinOP->replaceAllUsesWith(shiftInst);
                    }
                    BinOP->eraseFromParent();
                    return true;
                }
            }
        }
        return false;
    }

    bool runOnBasicBlock(BasicBlock &B) {
        bool modifica = false;
        for (auto Iter = B.begin(); Iter != B.end(); ) {
            Instruction &Inst = *Iter++;
            if (BinaryOperator *BinOP = dyn_cast<BinaryOperator>(&Inst)) {
                changed = optimizeMul(BinOP) || optimizeDiv(BinOP);        //sfruttiamo il corto circuito
            }
        }
        return modifica;
    }

    bool runOnFunction(Function &F) {
        bool Transformed = false;
        for (auto &BB : F) {
            Transformed = runOnBasicBlock(BB);
        }
    return Transformed;
    }
}
