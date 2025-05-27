#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"

using namespace llvm;


bool foundNegativeDep(Instruction *I1, Instruction *I2, DependenceInfo &DA,ScalarEvolution &SE) {
    if (auto Dep = DA.depends(I1, I2, true)) {
        errs() << "\n[Dipendenza rilevata tra le seguenti istruzioni:]\n";
        I1->print(errs()); errs() << "\n";
        I2->print(errs()); errs() << "\n\n";

        //qui dobbiamo distinguere tra dip negativa o no
        Value *Ptr1 = getPointerOperand(I1);
	    Value *Ptr2 = getPointerOperand(I2);

	    const SCEV *S1 = SE.getSCEV(Ptr1);
	    const SCEV *S2 = SE.getSCEV(Ptr2);

	    errs() << "SCEV1: " << *S1 << "\n";
	    errs() << "SCEV2: " << *S2 << "\n";

	    const SCEV *Diff = SE.getMinusSCEV(S2, S1); // Distanza tra gli accessi

	    if (const SCEVConstant *CDiff = dyn_cast<SCEVConstant>(Diff)) {
		int64_t D = CDiff->getAPInt().getSExtValue();
		if (D < 0) {
		    errs() << "Dipendenza negativa dedotta manualmente! Distanza: " << D << "\n";
		    return true;
		}
	    } else {
		errs() << "Differenza non costante\n";
	    }
    }
    return false;
}

 



bool hasNegativeDistanceDependence(Loop *L1, Loop *L2, DependenceInfo &DA,ScalarEvolution &SE) {
    SmallVector<Instruction *, 16> MemInstL1, MemInstL2;

    // Estrai le istruzioni di L1 che leggono o scrivono memoria
    errs() << "Istruzioni load/store primo ciclo\n";
    for (BasicBlock *BB : L1->blocks()) {
        for (Instruction &I : *BB) {
            if (I.mayReadOrWriteMemory()){
                MemInstL1.push_back(&I);
                I.print(errs()); errs() << "\n";
            }
        }
    }

    // Estrai le istruzioni di L2 che leggono o scrivono memoria
    errs() << "Istruzioni load/store secondo ciclo\n";
    for (BasicBlock *BB : L2->blocks()) {
        for (Instruction &I : *BB) {
            if (I.mayReadOrWriteMemory()){
                MemInstL2.push_back(&I);
                I.print(errs()); errs() << "\n";
            }
        }
    }

    // Analizza ogni coppia tra le istruzioni selezionate
    for (Instruction *I1 : MemInstL1) {
        for (Instruction *I2 : MemInstL2) {
            if (foundNegativeDep(I1,I2,DA,SE) ||  foundNegativeDep(I2,I1,DA,SE)){ //??entrambe le direzioni?
            	errs() << "[FASE 4] Dipendenza negativa trovata\n";
            	return true;
            }
        }
    }

    errs() <<"[FASE 4] Nessuna dipendenza negativa\n";
    return false;
}


