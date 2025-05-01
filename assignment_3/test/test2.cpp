int main() {
    int a = 5;
    int b = 10;
    int c = 3;

    if ( a > 0 ) 
    	a = 1;
    else
    	a = 2;
    
    for (int i = 0; i < 10 ; ){
    	b = a * 3;	//loop inv
    	c = c + b;	//non loop inv
    	i += 1;
    }
    return c;
}
