#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/PostDominators.h"


BasicBlock *getSingleLoopExitSuccessor(Loop *L) {
    SmallVector<BasicBlock *, 4> ExitingBlocks;
    L->getExitingBlocks(ExitingBlocks);

    BasicBlock *UniqueExit = nullptr;

    for (BasicBlock *Exit : ExitingBlocks) {
        Instruction *TI = Exit->getTerminator();
        for (unsigned i = 0; i < TI->getNumSuccessors(); ++i) {
            BasicBlock *Succ = TI->getSuccessor(i);
            if (!L->contains(Succ)) {
                if (UniqueExit && UniqueExit != Succ) {
      
                    return nullptr;
                }
                UniqueExit = Succ;
            }
        }
    }

    return UniqueExit; // null se non trovato o se ambiguità
}


BasicBlock *getGuardBlock(Loop *L, DominatorTree &DT) {
    for (auto *Pred : predecessors(L->getLoopPreheader())) {
     
        Instruction *TI = Pred->getTerminator();
        unsigned succInLoop = 0;
        unsigned succOutLoop = 0;

        for (unsigned i = 0; i < TI->getNumSuccessors(); ++i) {
            BasicBlock *Succ = TI->getSuccessor(i);
            if (L->contains(Succ) || Succ == L->getLoopPreheader())
                ++succInLoop;
            else
                ++succOutLoop;
        }
	errs() << "-----------" << succInLoop << " " << succOutLoop <<"\n";
        if (succInLoop == 1 && succOutLoop == 1)
            return Pred; // trovato il guard block
    }

    return nullptr;
}

bool singleBranchBlock(BasicBlock *BB) {
    // Controlla se il blocco ha esattamente una sola istruzione
    if (BB->size() != 1)
        return false;

    // Prendi la prima (e unica) istruzione
    Instruction &I = BB->front();

    // Verifica se è una BranchInst
    return isa<BranchInst>(I);
}




void fase1Fusion(LoopInfo &LI, DominatorTree &DT) {
 	//Questa prima parte da sistemare, in generale  penso non va bene  (non considera nested loop)
    auto Loops = LI.getLoopsInPreorder(); // ordinati in preorder, i sotto-loop dopo il padre
	//di conseguenza anche questo non va bene
    if (Loops.size() < 2) {
        errs() << "[FASE 1 FUSION] Meno di due loop. Fusione non applicabile.\n";
        return;
    }

    for (size_t i = 0; i + 1 < Loops.size(); ++i) {
        Loop *L0 = Loops[i];
        Loop *L1 = Loops[i + 1];


	      BasicBlock *L0Exit = L0->getExitingBlock();       //attenzione potrebbero essere di più, penso fallisca in tal caso il passo
        BasicBlock *L0ExitSucc = getSingleLoopExitSuccessor(L0);
        BasicBlock *L1Preheader = L1->getLoopPreheader();
        BasicBlock *L0Guard = getGuardBlock(L0, DT);

        bool adjacent = false;

        // Caso normale
        if (L0ExitSucc && L1Preheader &&
            L0ExitSucc == L1Preheader &&
            singleBranchBlock(L1Preheader))
            {
            adjacent = true;
            errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " sono adiacenti (caso normale).\n";
            }

        // Caso guarded loop [da controllare], non conviene prima controllare L0 sia guarded?
        if (!adjacent && L0Guard && L1Preheader) {
            for (unsigned j = 0; j < L0Guard->getTerminator()->getNumSuccessors(); ++j) {
                BasicBlock *succ = L0Guard->getTerminator()->getSuccessor(j);
                if (!L0->contains(succ) && succ == L1Preheader) {
                    adjacent = true;
                    errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " sono adiacenti (caso guarded).\n";
                    break;
                }
            }
        }

        if (!adjacent) {
            errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " NON sono adiacenti.\n";
        }
    }
}