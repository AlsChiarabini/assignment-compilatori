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

struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();

    // Ottieni l'analisi LoopInfo
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

   bool changed = true;
   // per ogni loop:  lancia le 3 fasi
   
   for ( ; changed ; ){
   	    changed = false;
   	    //questo wrappa in fun "LICM"
	   for (Loop *L : LI) {
	    std::vector<Instruction*> InvariantInsts = fase1(L);
	    std::vector<Instruction*> InstsForCodeMotion = fase2(L, InvariantInsts);
	    if (fase3(L, InstsForCodeMotion))
	    	changed = true;   	
	    }	   
    }
    
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

