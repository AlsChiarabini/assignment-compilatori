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
    if (BB->size() != 1)
        return false;

    // Prendi la prima (e unica) istruzione
    Instruction &I = BB->front();
    return isa<BranchInst>(I);
}

bool G1LinkedToG2(Loop *L0,BasicBlock *L0Guard,BasicBlock *L1Guard){
	for (unsigned j = 0; j < L0Guard->getTerminator()->getNumSuccessors(); ++j) {
		BasicBlock *succ = L0Guard->getTerminator()->getSuccessor(j);
		if (!L0->contains(succ) && succ == L1Guard) {
		            return true;
		}
	}
	return false;
}

//Controllo che il guard Block abbia solo la istruzione condizionale e il salto
bool onlyGuardBB(BasicBlock *BB) {
    auto it = BB->begin();
    if (it == BB->end())
        return false;

    Instruction *first = &*it;
    auto *cmp = dyn_cast<ICmpInst>(first);
    if (!cmp)
        return false;

    ++it;
    if (it == BB->end())
        return false;

    Instruction *second = &*it;
    auto *br = dyn_cast<BranchInst>(second);
    if (!br)
        return false;

    ++it;
    // Non ci devono essere altre istruzioni
    return it == BB->end();
}

//Controlla che la guardia sia la stessa
bool sameGuard(BasicBlock *G1, BasicBlock *G2) {

    auto *BI1 = dyn_cast<BranchInst>(G1->getTerminator());
    auto *BI2 = dyn_cast<BranchInst>(G2->getTerminator());

    if (!BI1 || !BI1->isConditional() || !BI2 || !BI2->isConditional())
        return false;

    auto *Cond1 = dyn_cast<ICmpInst>(BI1->getCondition());
    auto *Cond2 = dyn_cast<ICmpInst>(BI2->getCondition());

    if (!Cond1 || !Cond2)
        return false;

    // Devono avere lo stesso predicato (eq, ne, sgt, ...)
    if (Cond1->getPredicate() != Cond2->getPredicate())
        return false;

    //controllo ora gli operandi
    Value *L1 = Cond1->getOperand(0);
    Value *R1 = Cond1->getOperand(1);
    Value *L2 = Cond2->getOperand(0);
    Value *R2 = Cond2->getOperand(1);

    if (Cond1->isCommutative()) {
        return (L1 == L2 && R1 == R2) || (L1 == R2 && R1 == L2);
    } else {
        return (L1 == L2 && R1 == R2);
    }
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

        BasicBlock *L0Exit = getSingleLoopExitSuccessor(L0);
        BasicBlock *L1Preheader = L1->getLoopPreheader();
        BasicBlock *L0Guard = getGuardBlock(L0, DT);
        BasicBlock *L1Guard = getGuardBlock(L1, DT);
        

        bool adjacent = false;

        // Caso normale
        if (L0Exit && L1Preheader &&
            L0Exit == L1Preheader &&
            singleBranchBlock(L1Preheader))
            {
		    adjacent = true;
		    errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " sono adiacenti (caso normale).\n";
            }

        // Caso guarded loop 
        if (!adjacent && L0Guard && L1Guard) {
        	if (sameGuard(L0Guard,L1Guard)  &&  G1LinkedToG2(L0,L0Guard,L1Guard)){
        		if (singleBranchBlock(L0Exit) && singleBranchBlock(L1Preheader) && onlyGuardBB(L1Guard)){
        			 adjacent = true;
		    		errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " sono adiacenti (caso guarded).\n";
		    	}
        			
        	}    
        }

        if (!adjacent) {
            errs() << "[FASE 1 FUSION] L" << i << " e L" << i + 1 << " NON sono adiacenti.\n";
        }
    }
}

