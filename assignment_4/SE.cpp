#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"


using namespace llvm;

bool sameTime(const SCEV *TC0, const SCEV *TC1, ScalarEvolution &SE, size_t i) {
    if (isa<SCEVCouldNotCompute>(TC0) || isa<SCEVCouldNotCompute>(TC1)) {
        errs() << "[FASE 2] L" << i << " e L" << i + 1 << ": trip count non determinabile.\n";
        return false;
    }

    if (TC0 == TC1) {
        errs() << "[FASE 2] L" << i << " e L" << i + 1 << " iterano lo stesso numero di volte.\n";
        return true;
    } else {
        errs() << "[FASE 2] L" << i << " e L" << i + 1 << " iterano un numero diverso di volte.\n";
        return false;
    }
}

PHINode* getIndVar(Loop *L, ScalarEvolution &SE) {
    for (auto &I : *L->getHeader()) {
        if (auto *phi = dyn_cast<PHINode>(&I)) {
            const SCEV *scev = SE.getSCEV(phi);
            if (isa<SCEVAddRecExpr>(scev)) {
                return phi;
            }
        }
    }
    return nullptr;
}

void fase2Fusion(LoopInfo &LI, ScalarEvolution &SE) {
    auto Loops = LI.getLoopsInPreorder();
    if (Loops.size() < 2) return;

    for (size_t i = 0; i + 1 < Loops.size(); ++i) {
        Loop *L0 = Loops[i];
        Loop *L1 = Loops[i + 1];

        const SCEV *TC0 = SE.getBackedgeTakenCount(L0);
        const SCEV *TC1 = SE.getBackedgeTakenCount(L1);

        if (!sameTime(TC0, TC1, SE, i)) continue; // Vado alla prossima coppia di loop

        PHINode *phi0 = getIndVar(L0, SE);
        PHINode *phi1 = getIndVar(L1, SE);

        if (!phi0 || !phi1) {
            errs() << "[FASE 2] L" << i << " e L" << i + 1 << ": impossibile trovare IV valida.\n";
            continue;
        }

        // Fare solo IV0 == IV1 è troppo rigido, se usa i e j sono diverse
        // ma sono semanticamente equivalenti
        const SCEV *IV0 = SE.getSCEV(phi0);
        const SCEV *IV1 = SE.getSCEV(phi1);

        const auto *AR0 = dyn_cast<SCEVAddRecExpr>(IV0);
        const auto *AR1 = dyn_cast<SCEVAddRecExpr>(IV1);

        // Allora confronto la tripla {... ,... ,...}
        // Se sono uguali, allora sono semanticamente equivalenti
        if (AR0 && AR1 &&
            AR0->getStart() == AR1->getStart() &&
            AR0->getStepRecurrence(SE) == AR1->getStepRecurrence(SE) &&
            SE.getTypeSizeInBits(AR0->getType()) == SE.getTypeSizeInBits(AR1->getType())) {

            errs() << "[FASE 2] IV di L" << i << " e L" << i + 1 << " sono semanticamente equivalenti.\n";
        } else {
            errs() << "[FASE 2] IV di L" << i << " e L" << i + 1 << " NON sono equivalenti.\n";
        }
    }
}

