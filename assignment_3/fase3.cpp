#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
#include <set>
#include <algorithm>

using namespace llvm;

bool ordUseDef(std::vector<Instruction*> &InstsForCodeMotion) {
    std::vector<Instruction*> sortedInstr;          // istruzioni già ordinate per essere spostate
    std::set<Instruction*> alreadyOrderedInstr;     // Istruzioni che ho già inserito in sortedInstr

    while (sortedInstr.size() < InstsForCodeMotion.size()) {
        bool progress = false; // Per tenere traccia se ho fatto almeno un cambiamento

        for (Instruction *inst : InstsForCodeMotion) {
            if (alreadyOrderedInstr.count(inst)) continue; // se l'ho già fatta, salto

            bool ready = true; // pronta per essere spostata
            /*
            Controllo le dipendenze, cioè se tutte le istruzioni da cui dipende una certa istruzione sono già state spostate
            Se non sono pronte, non posso spostarla
            */
            for (Use &operand : inst->operands()) {
                if (Instruction *opInst = dyn_cast<Instruction>(operand)) { // guardo se un operando è un'istruzione, in caso è una delle instr da cui inst dipende
                    if (std::find(InstsForCodeMotion.begin(), InstsForCodeMotion.end(), opInst) != InstsForCodeMotion.end()) { // controllo se opInst è una delle istruzioni che sto cercando di spostare
                        if (!alreadyOrderedInstr.count(opInst)) { // se non è già dtata guardata, non posso spostare inst
                            ready = false;
                            break;
                        }
                    }
                }
            }

            if (ready) {
                sortedInstr.push_back(inst);
                alreadyOrderedInstr.insert(inst);
                progress = true;
            }
        }

        if (!progress) {
            errs() << "[FASE 3] Errore: ciclo di dipendenze.\n";
            return false;
        }
    }

    InstsForCodeMotion = sortedInstr; // sovrascrivo con ordine corretto
    return true;
}


bool muoviInstr(Instruction *inst, BasicBlock *preheader) {
    inst->removeFromParent();
    inst->insertBefore(preheader->getTerminator());
    errs() << "[FASE 3] Ho spostato l'istruzione (";
    inst->print(errs());
    errs() << ") nel preheader\n";
    return true;
}

bool fase3(Loop *L, std::vector<Instruction*> InstsForCodeMotion) {
    BasicBlock *preheader = L->getLoopPreheader();
    if (!preheader) {
        errs() << "[FASE 3] Nessun preheader trovato, loop non in forma normale, impossibile fare code motion\n";
        return false;
    }

    if (!ordUseDef(InstsForCodeMotion)) {
        return false;
    }

    bool moved = false;
    for (Instruction *inst : InstsForCodeMotion) {
        if (muoviInstr(inst, preheader)) {
            moved = true;
        }
    }

    return moved;
}





/*
bool instr1ComesBeforeinstr2(Instruction *a, Instruction *b) {
    BasicBlock *blockA = a->getParent();
    BasicBlock *blockB = b->getParent();

    if (blockA == blockB) {
        return b->comesBefore(a);
    }

    Function *F = blockA->getParent();
    for (BasicBlock &BB : *F) {
        if (&BB == blockA) return false;
        if (&BB == blockB) return true;
    }

    errs() << "Qua non devo mai arrivarci, ERRORE (per debugggg)";
    return false;
}
*/