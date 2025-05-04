int main () {
   int a = 2+4;
   int b = 2+5;
   int x;
   
   if ( a > 0 ) 
    	a = a;
    else
    	a = 2;
    
	
   for (int i = 0; i < 10; i++) {

        if (i % 2 == 0)
            x = 3*a;              //loop inv
        else
            x = 1 * i;          //non loop inv

    	for (int j = 0; j < 10 ; j++){
    		int var = a * b;      //loop inv per entrambi i cicli
            int v2 = var * i;            //loop inv solo ciclo interno
            int v3 = x * 3;                   //loop inv ciclo interno
            int v4 = x*j;                  //non loop inv
    	}
       
    }
  

    return 0;
}
