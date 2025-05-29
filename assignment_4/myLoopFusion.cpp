#include "adiacenza.cpp"
#include "CFE.cpp"
#include "SE.cpp"
#include "negativeDep.cpp"
#include "transformIR.cpp"

bool fondiLoopsStessoLivello(Loop *ParentLoop,
                      DominatorTree &DT,
                      PostDominatorTree &PDT,
                      ScalarEvolution &SE,
                      DependenceInfo &DI) {
    bool Changed = false;

    auto &SubLoops = ParentLoop->getSubLoops();
    if (SubLoops.size() < 2)
        return false;

    for (size_t i = 0; i + 1 < SubLoops.size(); ++i) {
        Loop *L0 = SubLoops[i];
        Loop *L1 = SubLoops[i + 1];

        bool passedAllTest = true;

        if (!fase1Fusion(L0, L1, DT, i))                     passedAllTest = false;
        if (!fase2Fusion(L0, L1, SE, i))                     passedAllTest = false;
        if (!controlFlowEquivalent(L0, L1, DT, PDT))         passedAllTest = false;
        if (hasNegativeDistanceDependence(L0, L1, DI, SE))   passedAllTest = false;

        if (!passedAllTest)
            continue;

        errs() << "Subloop " << i << " e " << i + 1 << " passed all checks\n";
        fusion(L0, L1, SE, DT);
        Changed = true;
    }

    return Changed;
}


bool processaRic(Loop *L,
                          DominatorTree &DT,
                          PostDominatorTree &PDT,
                          ScalarEvolution &SE,
                          DependenceInfo &DI,
                          LoopInfo &LI) {
    bool Changed = false;

    for (Loop *SubL : L->getSubLoops()) {
        Changed |= processaRic(SubL, DT, PDT, SE, DI, LI);
    }


    Changed |= fondiLoopsStessoLivello(L, DT, PDT, SE, DI);

    return Changed;
}


bool fuseTopLevelLoops(std::vector<Loop *> &TopLoops,
                       DominatorTree &DT,
                       PostDominatorTree &PDT,
                       ScalarEvolution &SE,
                       DependenceInfo &DI) {
    bool Changed = false;

    for (size_t i = 0; i + 1 < TopLoops.size(); ++i) {
        Loop *L0 = TopLoops[i];
        Loop *L1 = TopLoops[i + 1];

        bool passedAllTest = true;

        if (!fase1Fusion(L0, L1, DT, i))                     passedAllTest = false;
        if (!fase2Fusion(L0, L1, SE, i))                     passedAllTest = false;
        if (!controlFlowEquivalent(L0, L1, DT, PDT))         passedAllTest = false;
        if (hasNegativeDistanceDependence(L0, L1, DI, SE))   passedAllTest = false;

        if (!passedAllTest)
            continue;

        errs() << "Top-level loop " << i << " e " << i + 1 << " passed all checks\n";
        fusion(L0, L1, SE, DT);
        Changed = true;
    }

    return Changed;
}


bool myLoopFusion(LoopInfo &LI, DominatorTree &DT, PostDominatorTree &PDT,
                  ScalarEvolution &SE, DependenceInfo &DI) {
    bool IRChanged = false;

    
    SmallVector<Loop*, 4> temp = LI.getLoopsInPreorder();
    std::vector<Loop*> allPreorderLoops(temp.begin(), temp.end());
    std::vector<Loop*> TopLoops;

    // Filtro prendendo i topLevel
    for (Loop *L : allPreorderLoops) {
        if (!L->getParentLoop()) {
            TopLoops.push_back(L);
        }
    }

    for (Loop *TopLoop : TopLoops) {
        IRChanged |= processaRic(TopLoop, DT, PDT, SE, DI, LI);
    }

    //Fusione dei top-level loop
    IRChanged |= fuseTopLevelLoops(TopLoops, DT, PDT, SE, DI);

    return IRChanged;
}


