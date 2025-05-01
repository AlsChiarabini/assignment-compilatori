#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
#include <set>

using namespace llvm;

bool instr1ComesBeforeinstr2(Instruction *a, Instruction *b) {
    BasicBlock *blockA = a->getParent();
    BasicBlock *blockB = b->getParent();

    // Le istruzioni sono nello stesso blocco
    if (blockA == blockB) {
        return b->comesBefore(a); // metodo LLVM, risponde a 'b compare fisicamente prima di a?'
    }

    //Le istruzioni sono in blocchi diversi
    Function *F = blockA->getParent();
    for (BasicBlock &BB : *F) {
        if (&BB == blockA) return false; // --> A compare prima di B, quindi nessun problema
        if (&BB == blockB) return true; // --> B compare prima di A, quindi ordiniamo
    }

    errs() << "Qua non devo mai arrivarci, ERRORE (per debugggg)"; return false;

}

void muoviInstr(Instruction *inst, BasicBlock *preheader) {
    inst->removeFromParent();
    inst->insertBefore(preheader->getTerminator()); // prendo punto finale e le metto prima di quello
    errs() << "Ho spostato l'istruzione (";
    inst->print(errs());
    errs() << ") nel preheader\n";
}

void fase3(Loop *L, std::vector<Instruction*> InstsForCodeMotion) {

    BasicBlock *preheader = L->getLoopPreheader();
    if (!preheader) {
        errs() << "Nessun preheader trovato, loop non in forma normale, impossibile farecode motion";
        return;
    }

    std::stable_sort(InstsForCodeMotion.begin(), InstsForCodeMotion.end(), instr1ComesBeforeinstr2); 
    
    // output --> vettore ordinato, non mi resta che muovere
    for (Instruction *inst : InstsForCodeMotion) {
        muoviInstr(inst, preheader);
    }

}
