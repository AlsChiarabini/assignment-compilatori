#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Dominators.h"

#include "myLICM.cpp"

using namespace llvm;

namespace{

struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();

    //errs() << "Running FunctionPass on: " << F.getName() << "\n";

    // Ottieni l'analisi LoopInfo
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

    //Per sapere se la funzione/CFG abbia almeno un loop: 
    if (!LI.empty()) {
  	errs() << "Function " << F.getName() << " contains at least one loop.\n";
    } else {
  	errs() << "Function " << F.getName() << " does NOT contain any loops.\n";
    }
	
   // per ogni loop:  lancia le 3 fasi
   for (Loop *L : LI) {
        fase1(L);
        //fase2(L);
        //fase3(L);
    }
    

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

