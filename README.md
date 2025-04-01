# assignment-compilatori

#Per il primo assignment: 
Compilare il file per testing cpp: 
clang -S -emit-llvm -Xclang -disable-O0-optnone test.cpp -o test.ll
opt -S -passes=mem2reg test.ll -o test.ll

Per eseguire le ottimizzazioni comando visto a lezione "opt ..", scegliendo che passo applicare tra passo{1,2,3}, oppure local-opts per applicarli tutti.
infine llvm-dis... 

