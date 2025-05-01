int main() {
    int x = 3;
    int y = 5;
    int z = 0;
    int w = 1;

    for (int i = 0; i < 100; i++) {
        int a = x + y;          // loop-invariant (fuori)
        int b = a + 1;          // loop-invariant (dipende da a)
        int c = b * 2;          // loop-invariant (dipende da b)

        if (i % 2 == 0) {
            z = c + w;          // NON loop-invariant (modifica z)
        }

        w = z + i;              // NON loop-invariant (dipende da i)
    }

    return w;
}
