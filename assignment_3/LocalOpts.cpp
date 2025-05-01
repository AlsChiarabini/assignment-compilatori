#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"

#include "fase1.cpp"
#include "fase2.cpp"    
#include "fase3.cpp"

using namespace llvm;

namespace{
	// implementare changed
  void visitaLoop(Loop *L) {
    std::vector<Instruction*> InvariantInsts = fase1(L);
    std::vector<Instruction*> InstsForCodeMotion = fase2(L, InvariantInsts);
    fase3(L, InstsForCodeMotion);

    for (Loop *SubL : L->getSubLoops()) {
        visitaLoop(SubL);
    }
}

// TODO: sistema questione changed
bool LICM(LoopInfo &LI) {
  bool changed = false;
  for (Loop *L : LI) {
      visitaLoop(L);
      changed = true; // se fai ottimizzazione vera, puoi gestire questo in modo preciso
  }
  return changed;
}


struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();

    // Ottieni l'analisi LoopInfo
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

    bool changed = LICM(LI); // Da togliere bool a questo punto
    
	//questo va logicamente bene?
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

} // namespace

// Plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "MyFunctionPass", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "myLICM") {
            FPM.addPass(MyFunctionPass());
            return true;
          }
          return false;
        });
    }
  };
}

