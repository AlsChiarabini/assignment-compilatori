#include <iostream>

int main() {
    int a = 3;
    int b = 8;
    int mul_num = 16; // Potenza di 2 (shift a sinistra)
    int div_num = 8;  // Potenza di 2 (shift a destra)
    int mul_num_minus1 = 7; // 8 - 1 = 7, che è potenza di 2 (shift a sinistra)
    int mul_num_plus1 = 9;  // 8 + 1 = 9, che è potenza di 2 (shift a sinistra)
    
    // Test moltiplicazione con potenza di 2 (mul_num)
    int c = a * mul_num; // Ottimizzazione: a << 4 (moltiplicazione per 16)
    
    // Test divisione per potenza di 2 (div_num)
    int d = b / div_num; // Ottimizzazione: b >> 3 (divisione per 8)
    
    // Test moltiplicazione con num-1 che è una potenza di 2 (mul_num_minus1)
    int e = a * mul_num_minus1; // Ottimizzazione: (a << 3) - a (moltiplicazione per 7)
    
    // Test moltiplicazione con num+1 che è una potenza di 2 (mul_num_plus1)
    int f = a * mul_num_plus1; // Ottimizzazione: (a << 3) + a (moltiplicazione per 9)

    // La somma finale per verificare i risultati
    return c + d + e + f; // Dovrebbe essere il risultato ottimizzato

}


