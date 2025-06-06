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

  //la visita del Loop parte dal loop stesso e continua nei sub loop
  bool visitaLoop(Loop *L) {
    bool IR_changed = false;
    std::vector<Instruction*> InvariantInsts = fase1(L);
    std::vector<Instruction*> InstsForCodeMotion = fase2(L, InvariantInsts);
    if (fase3(L, InstsForCodeMotion))
        IR_changed = true;

    for (Loop *SubL : L->getSubLoops()) {
        if (visitaLoop(SubL))
            IR_changed = true;
    }
    return IR_changed;
}


bool LICM(LoopInfo &LI) {
  bool changed = false;
  for (Loop *L : LI) {
      if (visitaLoop(L))
        changed = true; 
  }
  return changed;
}


struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();

    // Ottieni l'analisi LoopInfo
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

    bool changed = LICM(LI); 

    if (changed)
      errs() << "IR cambiata\n";  
  
    return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

} 

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

