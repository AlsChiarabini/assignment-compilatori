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


//  "prova_opt_<op>" tentano se possibile di ottimizzare il tipo di  operazione <op> 


namespace passo1 {
    bool modifica = false;

    Value* prova_opt_Somma(BinaryOperator *inst) {
        if (inst->getOpcode() == Instruction::Add) {
            
            for (auto Iter = inst->op_begin(); Iter != inst->op_end(); ++Iter) {
                Value *Operand = *Iter;
                if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
                    if (C->isZero()) {    //metodo per controllare direttamente il valore dell'operando
                        
                        if (inst->getOperand(0) == C) {
                            return inst->getOperand(1);
                        } else {
                            return inst->getOperand(0);
                        }
                    }
                }
            }
        }
        return nullptr;
    }
    
    Value* prova_opt_Sub(BinaryOperator *inst) {
        if (inst->getOpcode() == Instruction::Sub) {
            
            
            if (ConstantInt *C = dyn_cast<ConstantInt>(inst->getOperand(1))) {
                if (C->isZero()) {    // Caso specifico per "x - 0"
                    return inst->getOperand(0);  // Restituisci il primo operando
                }
            }
        }
        return nullptr;
    }
    
    
    // Controllo commutativo
    Value* prova_opt_Mul(BinaryOperator *inst) {
        if (inst->getOpcode() == Instruction::Mul) {
            
            for (auto Iter = inst->op_begin(); Iter != inst->op_end(); ++Iter) {
                Value *Operand = *Iter;
                if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
                    if (C->isOne()) {             
                      
                        if (inst->getOperand(0) == C) {
                            return inst->getOperand(1);
                        } else {
                            return inst->getOperand(0);
                        }
                    }
                }
            }
        }
        return nullptr;
    }
    
    Value* prova_opt_Div(BinaryOperator *inst) {        
        if (inst->getOpcode() == Instruction::SDiv || inst->getOpcode() == Instruction::UDiv) { 
            if (ConstantInt *C = dyn_cast<ConstantInt>(inst->getOperand(1))) {
                if (C->isOne()) { 
                    return inst->getOperand(0);
                }
            }
        }
        return nullptr;
    }
    
    bool runOnBasicBlock(BasicBlock &B) {
       
        for (auto it = B.begin(); it != B.end();) {
            Instruction &I = *it;
            auto *binOp = dyn_cast<BinaryOperator>(&I);
            ++it;       //passi alla prossima prima eventualmente di eliminarla (eraseFromP())
            if (!binOp) continue;
    
            Value *replacement = nullptr;
            replacement = prova_opt_Somma(binOp);
            if (!replacement) replacement = prova_opt_Sub(binOp);
            if (!replacement) replacement = prova_opt_Mul(binOp);
            if (!replacement) replacement = prova_opt_Div(binOp);
    
            if (replacement) {
                binOp->replaceAllUsesWith(replacement);
                binOp->eraseFromParent();
                modifica = true; // Indichiamo che abbiamo effettuato un'ottimizzazione
            }
        }
        return modifica;
    }

    bool runOnFunction(Function &F) {
        bool Transformed = false;
      
      
        for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
          if (runOnBasicBlock(*Iter)) {
            Transformed = true;
          }
        }
        return Transformed;
    }
}










