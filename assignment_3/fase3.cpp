#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
#include <set>

using namespace llvm;

void fase3(Loop *L, std::vector<Istruction*> InstsForCodeMotion) {

    BasicBlock *preheader = L->getLoopPreHeader();
    if (!preheader) {
        errs() << "[FASE 3] --> Nessun preheader trovato, loop non in forma normale, impossibile farecode motion"
    }
}
