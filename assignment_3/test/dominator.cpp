int main()
{
	int a = 5;
	
	if (a > 0){
        //Blocco C
        a = a + 1;
        if (a > 3){
            // blocco D
            a = 10;
        }else{
            // blocco E
            a = 11;
        }
        // blocco f
        a = a / 2;  
    } else {
        // blocco B
        a = a * (-1);
    }

    //blocco G
    a = a * a;
	
	return a;  
}

