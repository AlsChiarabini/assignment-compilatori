#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"

using namespace llvm;

// Commentare le load del secondo ciclo con le store del primo (e ragionare sul viceversa) --> detto dal prof
// Lavora con ScEv e primitive

Value *getPointerOperand(Instruction *I) {
    if (auto *LI = dyn_cast<LoadInst>(I)) return LI->getPointerOperand();
    if (auto *SI = dyn_cast<StoreInst>(I)) return SI->getPointerOperand();
    return nullptr;
}

bool isLoad(Instruction *I) {
    return isa<LoadInst>(I);
}

bool isStore(Instruction *I) {
    return isa<StoreInst>(I);
}


bool foundNegativeDep(Instruction *I1, Instruction *I2, DependenceInfo &DA, ScalarEvolution &SE) {
    if (auto Dep = DA.depends(I1, I2, true)) {
        //errs() << "\n[Dipendenza rilevata tra:]\n";
        //I1->print(errs()); errs() << "\n";
        //I2->print(errs()); errs() << "\n";

        Value *Ptr1 = getPointerOperand(I1);
        Value *Ptr2 = getPointerOperand(I2);
        if (!Ptr1 || !Ptr2) {
            errs() << "[FASE 4]Uno dei due puntatori è nullo\n";
            return false;
        }

        const SCEV *S1 = SE.getSCEV(Ptr1);
        const SCEV *S2 = SE.getSCEV(Ptr2);

        errs() << "SCEV1: " << *S1 << "\n";
        errs() << "SCEV2: " << *S2 << "\n";

        const SCEVAddRecExpr *AR1 = dyn_cast<SCEVAddRecExpr>(S1);
        const SCEVAddRecExpr *AR2 = dyn_cast<SCEVAddRecExpr>(S2);

        if (!AR1 || !AR2) {
            errs() << "[FASE 4]Almeno uno degli accessi non è un SCEVAddRecExpr (funzione ricorrente di i)\n";
            return false;
        }
        const SCEV *Start1 = AR1->getStart();
        const SCEV *Start2 = AR2->getStart();
	const SCEV *DiffStart = nullptr;
	if (isStore(I1) && isLoad(I2)) {
        	DiffStart = SE.getMinusSCEV(Start1, Start2);
        }
        if (isStore(I1) && isStore(I2)) {
        	DiffStart = SE.getMinusSCEV(Start1, Start2);
        }
        if (isa<SCEVCouldNotCompute>(DiffStart)) {
            errs() << "[FASE 4]Differenza tra gli start non calcolabile (SCEVCouldNotCompute)\n";
            return true;
        }
        if (const SCEVConstant *CDiff = dyn_cast<SCEVConstant>(DiffStart)) {
            int64_t D = CDiff->getAPInt().getSExtValue();
            if (D < 0) {
                errs() << "[FASE 4] Dipendenza negativa trovata! Distanza: " << D << "\n";
                return true;
            }
        } else {
            errs() << "[FASE 4]Differenza non costante: " << *DiffStart << "\n";
            return true;
        }
    }
    return false;
}


bool hasNegativeDistanceDependence(Loop *L1, Loop *L2, DependenceInfo &DA, ScalarEvolution &SE) {
    SmallVector<Instruction *, 16> MemInstL1, MemInstL2;

    for (BasicBlock *BB : L1->blocks())
        for (Instruction &I : *BB)
            if (I.mayReadOrWriteMemory())
                MemInstL1.push_back(&I);

    for (BasicBlock *BB : L2->blocks())
        for (Instruction &I : *BB)
            if (I.mayReadOrWriteMemory())
                MemInstL2.push_back(&I);

    for (Instruction *I1 : MemInstL1) {
        for (Instruction *I2 : MemInstL2) {
            if (foundNegativeDep(I1, I2, DA, SE))
                return true;
        }
    }

    errs() << "[FASE 4] Nessuna dipendenza negativa\n";
    return false;
}



