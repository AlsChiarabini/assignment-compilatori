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
        return false;
    }

    if (TC0 == TC1) {
        return true;
    } else {
        return false;
    }
}
/*
//estendi, la phinode oltre passare il controllo isa<SCEV...> deve essere uno degli operandi della icmp dell'header, per robustezza penso sia megio ottenere la 
//  icmp dal branch (che è l'ultima istruzione del BB)
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
*/
// versione robusta di getIndVar
PHINode* getIndVar(Loop *L, ScalarEvolution &SE) {
    BasicBlock *Header = L->getHeader();

    // Trova il branch condizionato dell'header
    auto *br = dyn_cast<BranchInst>(Header->getTerminator());
    if (!br || !br->isConditional()) return nullptr;

    // Estrai la condizione del branch: dovrebbe essere un ICmp
    auto *icmp = dyn_cast<ICmpInst>(br->getCondition());
    if (!icmp) return nullptr;

    // Come prima + controllo
    for (auto &I : *Header) {
        auto *phi = dyn_cast<PHINode>(&I);
        if (!phi) break;  // le PHI stanno sempre in cima al blocco

        const SCEV *scev = SE.getSCEV(phi);
        if (!isa<SCEVAddRecExpr>(scev)) continue;

        // Controllo che la PHI sia usata nella condizione del loop
        if (icmp->getOperand(0) == phi || icmp->getOperand(1) == phi) {
            return phi;
        }
    }

    return nullptr;
}

bool fase2Fusion(Loop* L0,Loop *L1, ScalarEvolution &SE,int i) {

        const SCEV *TC0 = SE.getBackedgeTakenCount(L0);
        const SCEV *TC1 = SE.getBackedgeTakenCount(L1);

        if (!sameTime(TC0, TC1, SE, i)){ 
        	errs() <<" [FASE 2] Fallita, loopTripCount diverso\n";
        	return false;
        }

        PHINode *phi0 = getIndVar(L0, SE);
        PHINode *phi1 = getIndVar(L1, SE);

        if (!phi0 || !phi1) {
            errs() << "[FASE 2] L" << i << " e L" << i + 1 << ": impossibile trovare IV valida.\n";
            return false;
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

            errs() << "[FASE 2] IV di L" << i << " e L" << i + 1 << " sono semanticamente equivalenti, fase 2 successo.\n";
            return true;
        } 
        else {
            errs() << "[FASE 2] IV di L" << i << " e L" << i + 1 << " NON sono equivalenti, fase 2 fallita.\n";
            return false;
        }
}

