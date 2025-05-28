#!/bin/bash

# Script per compilare e ottimizzare testX.cpp in testX.ll

# Numero di test
for i in {1..12}; do
    SRC="test$i.cpp"
    IR="test$i.ll"

    echo "🔧 Compilazione $SRC -> $IR..."
    clang-19 -S -emit-llvm -Xclang -disable-O0-optnone "$SRC" -o "$IR"

    if [ $? -ne 0 ]; then
        echo "❌ Errore durante la compilazione di $SRC"
        continue
    fi

    echo "⚙️  Ottimizzazione mem2reg su $IR..."
    opt-19 -S -passes=mem2reg "$IR" -o "$IR"

    if [ $? -ne 0 ]; then
        echo "❌ Errore durante l'ottimizzazione di $IR"
        continue
    fi

    echo "✅ Fatto: $IR"
    echo "-----------------------------"
done

