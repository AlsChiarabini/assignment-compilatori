int main() {
    int a[10];
    int b[10];

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = a[i];
        for (int j = 0; j < 10; j++) {
            b[j] = a[j];
        }
        for (int j = 0; j < 10; j++) {
            a[j] = b[j];
        }
        for (int j = 0; j < 5; j++) {
            a[j] = b[j];
        }
    }


    for (int i = 0; i < 10; i++) {
        a[i] = 2*a[i];
        
        for (int j = 0; j < 5; j++) {
            a[j] = b[j];
        }
        for (int j = 0; j < 10; j++) {
            b[j] = a[j];
        }
        for (int j = 0; j < 10; j++) {
            a[j] = b[j];
            }

        }

return a[0] + b[9];
}

// result = 18