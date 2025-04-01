#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"

// Include your implementations 
#include "./test/passo1"
#include "./test/passo2"
#include "./test/passo3"

using namespace llvm;

namespace {

// Pass 1 - Basic Arithmetic Optimizations
struct TestPass1 : PassInfoMixin<TestPass1> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    errs() << "Running Pass 1: Algebric identity Optimizations\n";
    errs() << "Function Name: " << F.getName() << "\n";
    passo1::runOnFunction(F);
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

// Pass 2 - Strength Reduction Optimizations
struct TestPass2 : PassInfoMixin<TestPass2> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    errs() << "Running Pass 2: Strength Reduction Optimizations\n";
    errs() << "Function Name: " << F.getName() << "\n";
    passo2::runOnFunction(F);
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

// Pass 3 - Multi-instruction Optimizations
struct TestPass3 : PassInfoMixin<TestPass3> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    errs() << "Running Pass 3: Multi instruction Optimizations\n";
    errs() << "Function Name: " << F.getName() << "\n";
    passo3::runOnFunction(F);
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

struct TestPassAll : PassInfoMixin<TestPassAll> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    errs() << "Running All Optimization Passes\n";
    errs() << "Function Name: " << F.getName() << "\n";
    
    bool changed = false;
    
    changed |= passo1::runOnFunction(F); // Pass 1
    changed |= passo2::runOnFunction(F); // Pass 2
    changed |= passo3::runOnFunction(F); // Pass 3
    
    return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

} // namespace

llvm::PassPluginLibraryInfo getTestPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LocalOpts", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  // Register different passes based on name
                  if (Name == "local-opts-1" || Name == "passo1") {
                    FPM.addPass(TestPass1());
                    return true;
                  }
                  if (Name == "local-opts-2" || Name == "passo2") {
                    FPM.addPass(TestPass2());
                    return true;
                  }
                  if (Name == "local-opts-3" || Name == "passo3") {
                    FPM.addPass(TestPass3());
                    return true;
                  }
                  if (Name == "local-opts-all" || Name == "local-opts") {
                    FPM.addPass(TestPassAll());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getTestPassPluginInfo();
}
