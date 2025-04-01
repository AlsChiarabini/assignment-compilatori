#include <stdio.h>

// Questa funzione contiene casi per il passo 1 (operazioni con costanti)
int test_passo1(int x, int y) {
    int r1 = x + 0;         // Eliminabile: x + 0 = x
    int r2 = 0 + y;         // Eliminabile: 0 + y = y
    int r3 = x - 0;         // Eliminabile: x - 0 = x
    int r4 = x * 1;         // Eliminabile: x * 1 = x
    int r5 = 1 * y;         // Eliminabile: 1 * y = y
    int r6 = x / 1;         // Eliminabile: x / 1 = x
    
    // Usiamo i risultati per evitare che vengano eliminati dal compilatore
    return r1 + r2 + r3 + r4 + r5 + r6;
}

// Questa funzione contiene casi per il passo 2 (strength reduction)
int test_passo2(int x) {
    int r1 = x * 16;        // Convertibile in: x << 4
    int r2 = x * 15;        // Convertibile in: (x << 4) - x
    int r3 = x * 17;        // Convertibile in: (x << 4) + x
    int r4 = x / 8;         // Convertibile in: x >> 3
    int r5 = x * (-16);     // Convertibile in: 0 - (x << 4)
    int r6 = x / (-8);      // Convertibile in: 0 - (x >> 3)
    
    return r1 + r2 + r3 + r4 + r5 + r6;
}

// Questa funzione contiene casi per il passo 3 (operazioni duali)
int test_passo3(int x) {
    int a1 = x + 5;
    int b1 = a1 - 5;       // Eliminabile: Operazione duale di a1, risultato = x
    
    int a2 = x - 7;
    int b2 = a2 + 7;       // Eliminabile: Operazione duale di a2, risultato = x
    
    int a3 = x * 3;
    int b3 = a3 / 3;       // Eliminabile: Operazione duale di a3, risultato = x
    
    int a4 = x / 4;
    int b4 = a4 * 4;       // Eliminabile: Operazione duale di a4, risultato = x
    
    // Caso speciale con due costanti
    int a5 = 3 * 5;
    int b5 = a5 / 3;       // Eliminabile: risultato = 5
    
    return b1 + b2 + b3 + b4 + b5;
}

// Testa tutti e tre i passi insieme con casi più complessi
int test_combined(int x, int y) {
    // Combinazione di passo 1 e 2
    int r1 = (x + 0) * 16;    // (x + 0) -> x, x * 16 -> x << 4
    
    // Combinazione di passo 2 e 3
    int r2 = x * 8;
    int r3 = r2 / 8;         // r3 dovrebbe essere x dopo ottimizzazione
    
    // Combinazione di passo 1 e 3
    int r4 = x * 1;
    int r5 = r4 + 10;
    int r6 = r5 - 10;        // r6 dovrebbe essere x dopo ottimizzazione
    
    // Catena di ottimizzazioni 
    int r7 = x * 16;         // -> x << 4
    int r8 = r7 / 2;         // -> x << 3
    int r9 = r8 * 2;         // -> x << 4 (di nuovo)
    
    // Più operazioni ridondanti per aumentare i registri
    int s1 = y + 0;
    int s2 = s1 * 1;
    int s3 = s2 * 4;         // -> s2 << 2
    int s4 = s3 / 4;         // -> s2 (operazione duale)
    
    return r1 + r3 + r6 + r9 + s4;
}

// Funzione con molti registri e calcoli per raggiungere ~100 registri
int complex_function(int a, int b, int c) {
    // Creiamo molte variabili con operazioni che possono essere ottimizzate
    int vars[50]; // Dichiarazione di 50 variabili
    
    // Inizializzo tutte le variabili con operazioni ottimizzabili
    vars[0] = a + 0;
    vars[1] = b * 1;
    vars[2] = c - 0;
    vars[3] = a * 8;
    vars[4] = vars[3] / 8; // Duale di vars[3]
    vars[5] = b + 5;
    vars[6] = vars[5] - 5; // Duale di vars[5]
    vars[7] = c * 16;
    vars[8] = a * 15;
    vars[9] = b / 4;
    
    // E così via con pattern simili...
    for (int i = 10; i < 50; i++) {
        if (i % 5 == 0) vars[i] = vars[i-10] + 0;
        else if (i % 5 == 1) vars[i] = vars[i-5] * 1;
        else if (i % 5 == 2) vars[i] = vars[i-2] * 8;
        else if (i % 5 == 3) vars[i] = vars[i-1] / 8;
        else vars[i] = vars[i-4] - 0;
    }
    
    // Alcune operazioni con risultati che verranno poi usati
    int sum = 0;
    for (int i = 0; i < 50; i++) {
        sum += vars[i];
    }
    
    return sum;
}

int main() {
    int x = 42;
    int y = 24;
    int z = 10;
    
    printf("Test passo 1: %d\n", test_passo1(x, y));
    printf("Test passo 2: %d\n", test_passo2(x));
    printf("Test passo 3: %d\n", test_passo3(x));
    printf("Test combinato: %d\n", test_combined(x, y));
    printf("Test complesso: %d\n", complex_function(x, y, z));
    
    return 0;
}