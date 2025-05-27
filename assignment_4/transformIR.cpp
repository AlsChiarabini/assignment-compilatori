
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

void fusion(Loop *L0, Loop *L1, ScalarEvolution &SE) {
    errs() << "[FUSION] Trasformazione dell'IR...\n";

    PHINode *IV0 = getIndVar(L0, SE);
    PHINode *IV1 = getIndVar(L1, SE);

    if (IV0 && IV1) {
        IV1->replaceAllUsesWith(IV0);
        errs() << "[FUSION] IV sostituita correttamente\n";
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
    //NOTA: stiamo supponendo che il body abbia un semplice branch (non condizionale al latch che cambiamo con firstBodyL1)

	// Qui facciamo la stessa supposizione
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




