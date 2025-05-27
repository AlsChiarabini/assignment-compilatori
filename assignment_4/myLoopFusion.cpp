#include "adiacenza.cpp"
#include "CFE.cpp"
#include "SE.cpp"
#include "negativeDep.cpp"
#include "transformIR.cpp"

bool myLoopFusion(LoopInfo &LI, DominatorTree &DT,PostDominatorTree &PDT,ScalarEvolution &SE,DependenceInfo &DI) {
    bool IRChanged = false;
    auto Loops = LI.getLoopsInPreorder(); 

    if (Loops.size() < 2) {
        errs() << "Meno di due loop. Fusione non applicabile.\n";
        return false;
    }

    for (size_t i = 0; i + 1 < Loops.size(); ++i) {
        Loop *L0 = Loops[i];
        Loop *L1 = Loops[i + 1];
	bool passedAllTest = true;
	//Chiama qui tutte le fasi e dopo la trasformazione  
	if (!fase1Fusion(L0,L1,DT,i))    	        passedAllTest = false;
	if (!fase2Fusion(L0,L1,SE,i))			passedAllTest = false;
	if (!controlFlowEquivalent(L0,L1,DT,PDT))       passedAllTest = false;
	if (hasNegativeDistanceDependence(L0,L1,DI,SE))    passedAllTest = false;

	if (!passedAllTest)	
		continue;
	
	errs() <<"Loop "<< i << " e " <<i+1 <<" passato tutte le fasi\n";
	
        //qui trasformazione
        fusion(L0,L1,SE);
    	IRChanged = true;
    }
    return IRChanged;
}

