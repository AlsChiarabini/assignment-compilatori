int main(){
	int a[10] = {0,0,0,0,0,0,0,0,0,0};
	int b[10] = {0,0,0,0,0,0,0,0,0,0};
	for (int i=0; i < 10 ; i++){
		a[i] = i;
		if (a[i] > 5)
			a[i] = -i;
		else
			a[i] = i*i;
	}
	
	for (int j=0; j < 10; j++){
		b[j] = a[j];
		if (b[j]>0)
			b[j] = b[j] - 10;
		else
			b[j] = -b[j];
	}

	return a[0] + b[9];   //9
}
