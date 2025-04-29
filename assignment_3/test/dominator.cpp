int main() {
    int a = 5;
    int b = 10;
    int c = 3;

    if (a > 0){
        a = a + 1;
        if (a > 3){
            a = 10;
        } else {
            a = 11;
        }
        a = a / 2;  
    } else {
        a = a * (-1);
    }

    int res = 0;
    for (int i = 0; i < 5; i++) {
        int d = b + c; // <-- b e c sono costanti esterni → `d = b + c` è loop-invariant!
        res += d;
    }

    a = a * a;
    
    return a;
}
