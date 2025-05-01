#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
#include <set>

using namespace llvm;

void dfs(DominatorTree &DT, BasicBlock *BB, std::set<BasicBlock*> &DominatedSet) {
    DominatedSet.insert(BB);
    DomTreeNode *Node = DT.getNode(BB);
    for (DomTreeNode *Child : Node->children()) {
        BasicBlock *ChildBB = Child->getBlock();
        dfs(DT, ChildBB, DominatedSet);
    }
}

// creo il set dei blocchi dominati da inst
// controllo che gli exitingBlock siano in questo set
bool dominates_allExit(Instruction *inst, Loop *loop, DominatorTree &DT) {
    std::set<BasicBlock*> DominatedSet;
    BasicBlock *instBB = inst->getParent();
    dfs(DT, instBB, DominatedSet);


    SmallVector<BasicBlock*, 4> ExitingBlocks;
    loop->getExitingBlocks(ExitingBlocks);


    for (BasicBlock *exitBB : ExitingBlocks) {
        if (DominatedSet.find(exitBB) == DominatedSet.end())
            return false;
    }
    return true;
}

bool dead_afterLoop(Instruction *inst, Loop *loop) {
    for (User *U : inst->users()) {
        if (Instruction *useInst = dyn_cast<Instruction>(U)) {
            if (!loop->contains(useInst))
                return false;
        }
    }
    return true;
}





bool condition_for_codemotion(Instruction *inst, Loop *loop, DominatorTree &DT) {
    return dominates_allExit(inst, loop, DT) || dead_afterLoop(inst, loop);
}

// ⇒ questa roba la mettiamo su un altro file:    “fase2”
std::vector<Instruction*> fase2(Loop *L, const std::vector<Instruction*> &InvariantInsts) {
    std::vector<Instruction*> InstsForCodeMotion;


    // Costruzione del DominatorTree a partire dalla funzione
    Function *F = L->getHeader()->getParent();
    DominatorTree DT(*F);


    for (Instruction *inst : InvariantInsts) {
        if (condition_for_codemotion(inst, L, DT)) {
            InstsForCodeMotion.push_back(inst);
        }
    }

    errs() << "[FASE 2] Totale istruzioni code-motion trovate: " << InstsForCodeMotion.size() << "\n";
    for (Instruction *inst : InstsForCodeMotion) {
        errs() << "[FASE 2] Istruzione per code motion: ";
        inst->print(errs());
        errs() << "\n";
    }

    return InstsForCodeMotion;
}

