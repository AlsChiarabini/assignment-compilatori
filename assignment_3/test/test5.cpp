int main () {
    int a = 2;
    int b = 1;
    int var = 0;
    
	
   for (int i = 0; i < 10; i++) {
        int num = 0;
        if (a*b > 0) {			//a*b loop inv
            num = a * 2;		//loop inv
        } else {
            num = b*3;			//loop inv
        }
        var = num + b;			//ancora loop inv + dead
    }
    // TEST NON SUPERATO:  perchè nell'ultima istruzione "num" è una PHINODE INVARIANT! --> cosa che non stiamo considerando ==> chiedi al prof se da implementare

    return 0;
}
