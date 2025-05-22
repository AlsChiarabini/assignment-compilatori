void dfs(DominatorTree &DT, BasicBlock *BB, std::set<BasicBlock*> &DominatedSet) {
    DominatedSet.insert(BB);
    DomTreeNode *Node = DT.getNode(BB);
    for (DomTreeNode *Child : Node->children()) {
        BasicBlock *ChildBB = Child->getBlock();
        dfs(DT, ChildBB, DominatedSet);
    }
}

void dfs(PostDominatorTree &DT, BasicBlock *BB, std::set<BasicBlock*> &DominatedSet) {
    DominatedSet.insert(BB);
    DomTreeNode *Node = DT.getNode(BB);
    for (DomTreeNode *Child : Node->children()) {
        BasicBlock *ChildBB = Child->getBlock();
        dfs(DT, ChildBB, DominatedSet);
    }
}



bool controlFlowEquivalent(Loop *L0, Loop *L1, DominatorTree &DT, PostDominatorTree &PDT)
{
    BasicBlock *L0Header = nullptr;
    BasicBlock *L1Header = nullptr;

    /*
        Se L0 e L1 hanno un guard block, allora il loro header è il guard block,
        altrimenti il loro header è l'header del loop.
    */

    if (BasicBlock *guard = getGuardBlock(L0, DT)) {
        L0Header = guard;
    } else {
        L0Header = L0->getHeader();
    }
    
    if (BasicBlock *guard = getGuardBlock(L1, DT)) {
        L1Header = guard;
    } else {
        L1Header = L1->getHeader();
    }
    
    if (L0Header == L1Header){	//Se L0Header == L1Header allora hanno la stessa guardia (stesso BB) quindi l'esecuzione di uno esclude l'altro
    	errs() <<"[Fase 3] Fallita.\n";
        return false;		
    }

    // L0 domina L1?
    //bool L0DomL1 = DT.dominates(L0Header, L1Header);
    
    bool L0DomL1 = true;
    std::set<BasicBlock*> DominatedSet;
    
    dfs(DT,L0Header, DominatedSet);
    if (DominatedSet.find(L1Header) == DominatedSet.end())
           L0DomL1 = false;
    
    // L1 postdomina L0?
    //bool L1PostDomL0 = PDT.dominates(L1Header, L0Header);
     bool L1PostDomL0 = true;
     std::set<BasicBlock*> PostDominatedSet;
    
    dfs(PDT,L1Header, PostDominatedSet);
    if (PostDominatedSet.find(L0Header) == PostDominatedSet.end())
           L1PostDomL0 = false;

    if (L0DomL1 && L1PostDomL0) {
        errs() << "[FASE 3] L0 domina L1 ed L1 domina L0 --> Sono control flow equivalent\n";
        return true;
    }
    else {
        errs() <<"[Fase 3] Fallita.\n";
        return false;
    }
}
