# assignment-compilatori

#Per il primo assignment: 
Compilato il file per testing cpp: 
clang -S -emit-llvm -Xclang -disable-O0-optnone prova.cpp -o prova.ll
opt -S -passes=mem2reg prova.ll -o prova.ll

Per eseguire le ottimizzazioni comando visto a lezione "opt .."

