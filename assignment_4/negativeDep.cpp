#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"

using namespace llvm;


//NON CORRETTA DA SISTEMARE (controlla sia la funzione sotto che sopratutto questa)

bool foundNegativeDep(Instruction *I1, Instruction *I2, DependenceInfo &DA) {
    if (auto Dep = DA.depends(I1, I2, false)) {
        unsigned Levels = Dep->getLevels();

        for (unsigned Level = 1; Level <= Levels; ++Level) {
            const SCEV *DistanceSCEV = Dep->getDistance(Level);
            if (DistanceSCEV) {
                // Prova a castare a SCEVConstant
                if (const SCEVConstant *ConstDist = dyn_cast<SCEVConstant>(DistanceSCEV)) {
                    int64_t Distance = ConstDist->getAPInt().getSExtValue();
                    if (Distance < 0) {
                        errs() << "  Dipendenza negativa trovata tra:\n";
                        errs() << "  I1 (L1): " << *I1 << "\n";
                        errs() << "  I2 (L2): " << *I2 << "\n";
                        errs() << "  Distanza livello " << Level << ": " << Distance << "\n";
                        return true;
                    }
                } else {
                    // Non costante → considerata pericolosa
                    errs() << "  Dipendenza a distanza sconosciuta (non costante) tra:\n";
                    errs() << "  I1 (L1): " << *I1 << "\n";
                    errs() << "  I2 (L2): " << *I2 << "\n";
                    errs() << "  → Considerata pericolosa per sicurezza.\n";
                    return true;
                }
            }
        }
    }
    return false;
}



bool hasNegativeDistanceDependence(Loop *L1, Loop *L2, DependenceInfo &DA) {
    SmallVector<Instruction *, 16> MemInstL1, MemInstL2;

    // Estrai le istruzioni di L1 che leggono o scrivono memoria
    for (BasicBlock *BB : L1->blocks()) {
        for (Instruction &I : *BB) {
            if (I.mayReadOrWriteMemory())
                MemInstL1.push_back(&I);
        }
    }

    // Estrai le istruzioni di L2 che leggono o scrivono memoria
    for (BasicBlock *BB : L2->blocks()) {
        for (Instruction &I : *BB) {
            if (I.mayReadOrWriteMemory())
                MemInstL2.push_back(&I);
        }
    }

    // Analizza ogni coppia tra le istruzioni selezionate
    for (Instruction *I1 : MemInstL1) {
        for (Instruction *I2 : MemInstL2) {
            if (foundNegativeDep(I1,I2,DA))
            	errs() << "[FASE 4] Dipendenza negativa trovata\n";
            	return true;
        }
    }

    errs() <<"[FASE 4] Nessuna dipendenza negativa\n";
    return false;
}


