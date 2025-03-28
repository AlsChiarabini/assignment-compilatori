#include <iostream>
#include <cassert>

/*
int optimized_add(int x) {
    return x + 0;  // Il compilatore dovrebbe ottimizzarlo in `return x;`
}

int optimized_mul(int x) {
    return x * 1;  // Il compilatore dovrebbe ottimizzarlo in `return x;`
}

void test_optimization() {
    int val = 42;
    
    // Test per l'identità additiva
    assert(optimized_add(val) == val);
    
    // Test per l'identità moltiplicativa
    assert(optimized_mul(val) == val);

    std::cout << "Test passato: l'ottimizzazione funziona!" << std::endl;
}

int main() {
    test_optimization();
    return 0;
}
*/

int main() {
    int a = 10;
    int b = 20;
    int add_sub_nul = 0;
    int mul_div_nul = 1;

    int c = a + add_sub_nul;  
    int d = b * mul_div_nul;  
    int e = a - add_sub_nul;
    int f = b / mul_div_nul;

    return c + d + e + f; // 60
}

