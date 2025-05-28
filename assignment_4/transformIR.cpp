
BasicBlock* getLatch(Loop *L) {
    BasicBlock *Header = L->getHeader();
    for (BasicBlock *BB : L->blocks()) {
        for (BasicBlock *Succ : successors(BB)) {
            if (Succ == Header) {
                return BB;
            }
        }
    }
    return nullptr;
}

BasicBlock* getBodyTail(Loop *L) {
    BasicBlock *Latch = getLatch(L);
    for (BasicBlock *BB : L->blocks()) {
        for (BasicBlock *Succ : successors(BB)) {
            if (Succ == Latch) {
                return BB;
            }
        }
    }
    return nullptr;
}
BasicBlock* getFirstBodyBlock(Loop *L) {
    BasicBlock *Header = L->getHeader();
    for (BasicBlock *Succ : successors(Header)) {
        if (L->contains(Succ)) return Succ;
    }
    return nullptr;
}

BasicBlock* getExitBlock(Loop *L) {
    BasicBlock *Header = L->getHeader();
    for (BasicBlock *Succ : successors(Header)) {
        if (!L->contains(Succ)) return Succ;
    }
    return nullptr;
}

bool guardedCase(Loop *L0, Loop *L1,DominatorTree &DT){
	BasicBlock *G1 = getGuardBlock(L0, DT);		//funzioni in CFE.cpp
    	BasicBlock *G2 = getGuardBlock(L1, DT);
	if (G1 && G2 && !L0->contains(G2))
		return true;
	return false;     
}
void modify_first_guard(Loop *L0, Loop *L1, DominatorTree &DT) {
    BasicBlock *G1 = getGuardBlock(L0, DT); // da CFE.cpp

    BranchInst *BI = dyn_cast<BranchInst>(G1->getTerminator());
    BasicBlock *ExitL1 = getExitBlock(L1);

     for (unsigned i = 0; i < BI->getNumSuccessors(); ++i) {
        BasicBlock *Succ = BI->getSuccessor(i);
        // Se questo successore non è dentro L0 e non è il preheader, allora è quello da sostituire
        if (!L0->contains(Succ) && Succ != L0->getLoopPreheader()) {
            BI->setSuccessor(i, ExitL1);
            errs() << "[modify_first_guard] Successo: Successor(" << i << ") aggiornato a ExitL1\n";
            return;
        }
    }

}


void fusion(Loop *L0, Loop *L1, ScalarEvolution &SE,DominatorTree &DT) {

    if (guardedCase(L0,L1,DT)){
    	modify_first_guard(L0,L1,DT);
    }

    PHINode *IV0 = getIndVar(L0, SE);
    PHINode *IV1 = getIndVar(L1, SE);

    if (IV0 && IV1) {
        IV1->replaceAllUsesWith(IV0);	
    } else {
        errs() << "[FUSION] Errore nell'ottenere le IV\n";
        return;
    }

    BasicBlock *Header0 = L0->getHeader();
    BasicBlock *Tail0   = getBodyTail(L0);
    BasicBlock *Latch0  = getLatch(L0);

    BasicBlock *FirstBodyL1 = getFirstBodyBlock(L1);
    BasicBlock *Tail1       = getBodyTail(L1);
    BasicBlock *Exit1       = getExitBlock(L1);

    if (!Header0 || !Tail0 || !Latch0 || !FirstBodyL1 || !Tail1 || !Exit1) {
        errs() << "[FUSION] Errore nel reperire blocchi fondamentali\n";
        return;
    }



    BranchInst *br = dyn_cast<BranchInst>(Tail0->getTerminator());
    br->setSuccessor(0, FirstBodyL1);


    BranchInst *br2 = dyn_cast<BranchInst>(Tail1->getTerminator());
    br2->setSuccessor(0, Latch0);


    BranchInst *br3 = dyn_cast<BranchInst>(Header0->getTerminator());
    for (unsigned i = 0; i < br3->getNumSuccessors(); ++i) {
	    BasicBlock *Succ = br3->getSuccessor(i);
	    if (!L0->contains(Succ)) {
		br3->setSuccessor(i, Exit1);
		break;
	    }
    }
    

    errs() << "[FUSION] Fusione completata\n";
}




