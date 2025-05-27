void dfs(DominatorTree &DT, BasicBlock *BB, std::set<BasicBlock*> &DominatedSet) {
    DominatedSet.insert(BB);
    DomTreeNode *Node = DT.getNode(BB);
    for (DomTreeNode *Child : Node->children()) {
        BasicBlock *ChildBB = Child->getBlock();
        dfs(DT, ChildBB, DominatedSet);
    }
}

void p_dfs(PostDominatorTree &DT, BasicBlock *BB, std::set<BasicBlock*> &DominatedSet) {
    DominatedSet.insert(BB);
    DomTreeNode *Node = DT.getNode(BB);
    for (DomTreeNode *Child : Node->children()) {
        BasicBlock *ChildBB = Child->getBlock();
        p_dfs(DT, ChildBB, DominatedSet);
    }
}



bool controlFlowEquivalent(Loop *L0, Loop *L1, DominatorTree &DT, PostDominatorTree &PDT)
{
    BasicBlock *L0Header = nullptr;
    BasicBlock *L1Header = nullptr;

    

    //Consideriamo separatamente il caso Guarded   
    bool guardedCase = false;
   
    BasicBlock *G1 = getGuardBlock(L0, DT);
    BasicBlock *G2 = getGuardBlock(L1, DT);

    if (G1 && G2 && !L0->contains(G2)) {
	    L0Header = G1;
	    L1Header = G2;
	    guardedCase = true;
    } else {
	    L0Header = L0->getHeader();
	    L1Header = L1->getHeader();
   }

    
    //Dobbiamo considerare "manualmente" il caso in cui i due cicli abbiano la guardia e questa sia la stessa (nel senso di stesso BB)
    if ( guardedCase &&  L0Header == L1Header){	
    	
    	errs() <<"[Fase 3] CFE fallita.[guard uguali]\n";
        return false;		
    }


    
    bool L0DomL1 = true;
    std::set<BasicBlock*> DominatedSet;
    
    dfs(DT,L0Header, DominatedSet);
    if (DominatedSet.find(L1Header) == DominatedSet.end())
           L0DomL1 = false;
    

     bool L1PostDomL0 = true;
     std::set<BasicBlock*> PostDominatedSet;
    
    p_dfs(PDT,L1Header, PostDominatedSet);
    if (PostDominatedSet.find(L0Header) == PostDominatedSet.end())
           L1PostDomL0 = false;

    if (L0DomL1 && L1PostDomL0) {
        errs() << "[FASE 3] L0 domina L1 ed L1 domina L0 --> Sono control flow equivalent\n";
        return true;
    }
    else {
        errs() <<"[Fase 3] CFE fallita.\n";
        return false;
    }
}
