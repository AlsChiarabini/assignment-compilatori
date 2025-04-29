#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
#include <set>

using namespace llvm;

// Contiene tutte le istruzioni che identifichiamo come loop-invariant
static std::vector<Instruction*> loopInvariantInsts;

// Ricorsivamente verifica se un operando ha una definizione loop-invariant
bool isOperandInvariant(Value *op, Loop *L) {
    if (isa<Constant>(op)) return true;

    if (Instruction *inst = dyn_cast<Instruction>(op)) {
        if (!L->contains(inst)) return true; // il loop non contiene l'inst, quindi definita fuori dal loop
        if (isa<PHINode>(inst)) return false; // le PHI instruction non sono loop-invariant

        // Se l'istruzione è già marcata loop-invariant
        if (std::find(loopInvariantInsts.begin(), loopInvariantInsts.end(), inst) != loopInvariantInsts.end())
            return true;
        
        // Controllo ricorsivo: tutti i suoi operandi sono loop-invariant?
        bool allInvariant = true;
        for (unsigned i = 0; i < inst->getNumOperands(); ++i) {
            if (!isOperandInvariant(inst->getOperand(i), L)) {
                allInvariant = false;
                break;
            }
        }
        if (allInvariant) {
            loopInvariantInsts.push_back(inst);
            return true;
        }
    }
    return false;
}

void fase1(Loop *L) {
    loopInvariantInsts.clear(); // Pulisce la lista di istruzioni loop-invariant
    errs() << "[FASE 1] Analizzo istruzioni per loop-invariance...\n";

    for (BasicBlock *BB : L->blocks()) {
        for (Instruction &I : *BB) {
            if (auto *binOp = dyn_cast<BinaryOperator>(&I)) { 
                Value *op1 = binOp->getOperand(0);
                Value *op2 = binOp->getOperand(1);

                if (isOperandInvariant(op1, L) && isOperandInvariant(op2, L)) { // entrambi gli operandi sono loop-invariant rispetto al loop
                    loopInvariantInsts.push_back(binOp);
                    errs() << "Trovata loop-invariant: ";
                    binOp->print(errs());
                    errs() << "\n";
                }
            }
        }
    }

    errs() << "Totale istruzioni loop-invariant trovate: " << loopInvariantInsts.size() << "\n";
}

