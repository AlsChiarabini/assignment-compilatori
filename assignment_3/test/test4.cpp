int main () {
    int a = 2;
    int b = 1;
    int var;
    int var2;

    int c = a*b;
    int i = 0;

    do {
        var = a*b;		//loop inv + DominatesAllExit
        var2 = var*3;		//loop inv + dominatesAllExit

        i++;
    } while (i < 10); 
	
    int user = var * 10;
    int user2 = var * 12;
    return 0;
}
