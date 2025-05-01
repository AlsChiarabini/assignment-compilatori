int main () {
    int a = 2;
    int b = 1;
    int var;
    int var2;

    int c = a*b;
    int i = 0;

    do {
        var = a*b;
        var2 = var*3;

        i++;
    } while (i < 10); 

}








/*
    for (int i = 0; i < 10; i++) {
        int num = 0;
        if (a*b > 0) {
            num = a * 2;
        } else {
            num = b*3;
        }
        var = num + 1;
    }

    return var;
}


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
        res += d;     // Provato anche res = d+7 --> segna loop invariant, ok
        for (int j = 0; j < 3; j++) {
            res += a;
        }
    }

    a = a * a;
    
    return a;
}
*/