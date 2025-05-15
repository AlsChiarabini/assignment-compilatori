#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/PostDominators.h"

using namespace llvm;

#include "adiacenza.cpp"
#include "CFE.cpp"

namespace{

struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();

    // Ottieni l'analisi LoopInfo
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

    // Ottieni l'analisi DominatorTree
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    // Ottieni l'analisi PostDominatorTree
    PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
    errs()<<"Avvio fase1\n";
  
  //Qui chiamo la fase 1
   fase1Fusion(LI,DT);
  //Qui chiamo la fase 3
    fase3Fusion(LI,DT,PDT);
  
    return PreservedAnalyses::all();
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
          if (Name == "myLoopFusion") {
            FPM.addPass(MyFunctionPass());
            return true;
          }
          return false;
        });
    }
  };
}



