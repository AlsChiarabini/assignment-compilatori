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

bool isOperandInvariant(Value *op, Loop *L,bool phiVisited);

// L'errore che da è perchè le phi-node devono essere raggruppate "in the top of BB" --> questo potrebbe portare problemi nell'ordine
bool isInstructionInvariant(Instruction &I, Loop *L, bool phiVisited) {
    if (auto *binOp = dyn_cast<BinaryOperator>(&I)) { 
        Value *op1 = binOp->getOperand(0);
        Value *op2 = binOp->getOperand(1);

        if (isOperandInvariant(op1, L, phiVisited) && isOperandInvariant(op2, L, phiVisited)) {
            loopInvariantInsts.push_back(binOp);
            errs() << "[FASE 1] Trovata loop-invariant: ";
            binOp->print(errs());
            errs() << "\n";
            return true;
        }
    } else if (auto *phi = dyn_cast<PHINode>(&I)) {
        if (phiVisited)
            return false; // evitiamo ricorsione infinita tra PHI

        bool allInvariant = true;
        for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
            Value *incoming = phi->getIncomingValue(i);
            if (!isOperandInvariant(incoming, L, true)) {
                allInvariant = false;
                break;
            }
        }

        if (allInvariant) {
            loopInvariantInsts.push_back(phi);
            errs() << "[FASE 1] Trovata PHINode loop-invariant: ";
            phi->print(errs());
            errs() << "\n";
            return true;
        }
    }

    return false;
}



// Ricorsivamente verifica se un operando ha una definizione loop-invariant
bool isOperandInvariant(Value *op, Loop *L,bool  phiVisited) {
    if (isa<Constant>(op)) return true;

    if (Instruction *inst = dyn_cast<Instruction>(op)) {
        if (!L->contains(inst)) return true; // il loop non contiene l'inst, quindi definita fuori dal loop

        // Se l'istruzione è già marcata loop-invariant
        if (std::find(loopInvariantInsts.begin(), loopInvariantInsts.end(), inst) != loopInvariantInsts.end())
            return true;
        
        // Controllo ricorsivo: tutti i suoi operandi sono loop-invariant?
        if (isInstructionInvariant(*inst, L,phiVisited)) {
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
            isInstructionInvariant(I,L,false);
        }
    }
    errs() << "[FASE 1] Totale istruzioni loop-invariant trovate: " << loopInvariantInsts.size() << "\n";
    return loopInvariantInsts;
}

// parto da var = a+b, guardo b, non l'ho mai vista quindi chiamo ancora isinstructioninvariant, quindi partendo da var io vado a controllare b alla fine --> ricorsione