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
        var = num + i;			//NON loop inv
    }

    return 0;
}
