#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/PostDominators.h"

bool controlFlowEquivalent(Loop *L0, Loop *L1, DominatorTree &DT, PostDominatorTree &PDT)
{
    BasicBlock *L0Header = L0->getHeader();
    BasicBlock *L1Header = L1->getHeader();

    // L0 domina L1?
    bool L0DomL1 = DT.dominates(L0Header, L1Header);
    // L1 postdomina L0?
    bool L1PostDomL0 = PDT.dominates(L1Header, L0Header);

    if (L0DomL1 && L1PostDomL0) {
        errs() << "[FASE 3] L0 domina L1 ed L1 domina L0 --> Sono control flow equivalent\n";
        return true;
    }
    else {
        if (!L0DomL1) errs() << "[FASE 3] L0 non domina L1\n";
        if (!L1PostDomL0) errs() << "[FASE 3] L1 non postdomina L0\n";
        return false;
    }
}

void fase3Fusion(LoopInfo &LI, DominatorTree &DT, PostDominatorTree &PDT) {
    auto Loops = LI.getLoopsInPreorder();
    if (Loops.size() < 2) {
        errs() << "[FASE 1 FUSION] Meno di due loop. Fusione non applicabile.\n";
        return;
    }

    for (size_t i = 0; i + 1 < Loops.size(); ++i) {
        Loop *L0 = Loops[i];
        Loop *L1 = Loops[i + 1];

        if (controlFlowEquivalent(L0, L1, DT, PDT)) {
            errs() << "[FASE 3 FUSION] L" << i << " e L" << i + 1 << " sono control flow equivalent.\n";
        } else {
            errs() << "[FASE 3 FUSION] L" << i << " e L" << i + 1 << " NON sono control flow equivalent.\n";
        }
    }
}
