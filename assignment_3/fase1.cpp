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

bool isOperandInvariant(Value *op, Loop *L);

bool isInstructionInvariant (Instruction &I, Loop *L) {
    if (auto *binOp = dyn_cast<BinaryOperator>(&I)) { 
        Value *op1 = binOp->getOperand(0);
        Value *op2 = binOp->getOperand(1);

        if (isOperandInvariant(op1, L) && isOperandInvariant(op2, L)) { //  se entrambi gli operandi sono loop-invariant rispetto al loop
            loopInvariantInsts.push_back(binOp);
            errs() << "[FASE 1] Trovata loop-invariant: ";
            binOp->print(errs());
            errs() << "\n";
            return true;
        }
    }
    return false;
}

bool isOperandInvariant(Value *op, Loop *L) {
    if (isa<Constant>(op)) return true;

    if (Instruction *inst = dyn_cast<Instruction>(op)) {
        if (!L->contains(inst)) return true; // il loop non contiene l'inst, quindi definita fuori dal loop

        // Se l'istruzione è già marcata loop-invariant
        if (std::find(loopInvariantInsts.begin(), loopInvariantInsts.end(), inst) != loopInvariantInsts.end())
            return true;
        
        // Controllo ricorsivo: tutti i suoi operandi sono loop-invariant? (se non già marcati tali)
        if (isInstructionInvariant(*inst, L)) {
            loopInvariantInsts.push_back(inst);
            return true;
        }
    }
    return false;
}



std::vector<Instruction*> fase1(Loop *L) {
    loopInvariantInsts.clear(); // Pulisce la lista di istruzioni loop-invariant
    errs() << "[FASE 1] Analizzo istruzioni per loop-invariance...\n";

    for (BasicBlock *BB : L->blocks()) {
        for (Instruction &I : *BB) {
            isInstructionInvariant(I,L);
        }
    }
    errs() << "[FASE 1] Totale istruzioni loop-invariant trovate: " << loopInvariantInsts.size() << "\n";
    return loopInvariantInsts;
}

