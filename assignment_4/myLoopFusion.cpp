#include "adiacenza.cpp"
#include "CFE.cpp"

bool myLoopFusion(LoopInfo &LI, DominatorTree &DT,PostDominatorTree &PDT) {
    bool IRChanged = false;
    auto Loops = LI.getLoopsInPreorder(); 

    if (Loops.size() < 2) {
        errs() << "Meno di due loop. Fusione non applicabile.\n";
        return false;
    }

    for (size_t i = 0; i + 1 < Loops.size(); ++i) {
        Loop *L0 = Loops[i];
        Loop *L1 = Loops[i + 1];

	//Chiama qui tutte le fasi e dopo la trasformazione  
	if (!fase1Fusion(L0,L1,DT,i))    continue;
	
	
	errs() <<"\nLoop "<< i << " e " <<i+1 <<" passato tutte le fasi";
	IRChanged = true;
        //qui trasformazione
    }
    return IRChanged;
}

