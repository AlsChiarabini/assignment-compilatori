#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"

using namespace llvm;


//NON CORRETTA DA SISTEMARE (controlla sia la funzione sotto che sopratutto questa)

/*  
    Per ora controllo che, L1 dipendendo da L2, la distanza iter(L1) - iter(L2) sia negativa.
    Cosa aggiungo io --> controllo di flusso, non solo dipendnentemente alla distanza
    In termine tecnico, dipendenza RAW (cosi mi sembra di aver capito, RAW = Read After Write), 
    questo vuol dire che L1 legge qualcosa che L2 scrive, e non va bene una volta fuso
    es.:
        for (int i = 0; i < N; i++)  B[i] = ...; // L2: scrive
        for (int i = 0; i < N; i++)  A[i] = B[i]; // L1: legge
    Hanno distanza zero, ma non va bene

*/

bool foundNegativeDep(Instruction *I1, Instruction *I2, DependenceInfo &DA) {
    if (auto Dep = DA.depends(I1, I2, true)) {
        unsigned Levels = Dep->getLevels();

        // Se è una dipendenza di flusso (I1 legge ciò che I2 scrive),
        // allora la fusione è problematica indipendentemente dalla distanza costante,
        // poiché I1 (corpo di L1) verrebbe eseguito prima di I2 (corpo di L2) nel loop fuso.
        if (Dep->isFlow()) {
            errs() << "  [FASE 4] Trovata dipendenza di flusso (flow) da L2 a L1 che impedisce la fusione:\n";
            errs() << "    Sink (I1 in L1): " << *I1 << "\n";
            errs() << "    Source (I2 in L2): " << *I2 << "\n";

            // Puoi comunque stampare la distanza per debug, se disponibile e costante
            for (unsigned Level = 1; Level <= Levels; ++Level) {
                const SCEV *DistanceSCEV = Dep->getDistance(Level);
                if (DistanceSCEV) {
                    if (const SCEVConstant *ConstDist = dyn_cast<SCEVConstant>(DistanceSCEV)) {
                        errs() << "    Distanza (iter(I1) - iter(I2)) a livello " << Level << ": " << ConstDist->getAPInt().getSExtValue() << "\n";
                    } else {
                        errs() << "    Distanza a livello " << Level << ": Non costante (considerata pericolosa)\n";
                        // Se la distanza non è costante per una dipendenza di flusso, è comunque un problema.
                    }
                }
            }
            return true; // Blocca la fusione
        }

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

    // Estrai le istruzioni che accedono a memoria
    for (BasicBlock *BB : L1->blocks())
        for (Instruction &I : *BB)
            if (I.mayReadOrWriteMemory())
                MemInstL1.push_back(&I);

    for (BasicBlock *BB : L2->blocks())
        for (Instruction &I : *BB)
            if (I.mayReadOrWriteMemory())
                MemInstL2.push_back(&I);

    // Controlla ogni coppia
    for (Instruction *I1 : MemInstL1) {
        for (Instruction *I2 : MemInstL2) {
            if (foundNegativeDep(I1, I2, DA)) {
                errs() << "[FASE 4] Dipendenza negativa trovata\n";
                return true;
            }
        }
    }

    // Aggiunta, controllo inverso (sto impazzendo)
    for (Instruction *I2 : MemInstL2) { // Istruzione dal secondo loop (L1_loop)
        for (Instruction *I1 : MemInstL1) { // Istruzione dal primo loop (L0_loop)
            // Ora I_L1 è il potenziale Sink, I_L0 è la potenziale Source
            if (foundNegativeDep(I2, I1, DA)) { // Chiamata: foundNegativeDep(istr_L1, istr_L0, ...)
                errs() << "[FASE 4] Dipendenza problematica (tipo L0->L1 con iter(L1)<iter(L0)) trovata.\n";
                return true;
            }
        }
    }

    errs() << "[FASE 4] Nessuna dipendenza negativa\n";
    return false;
}



