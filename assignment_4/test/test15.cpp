int main(){
	int a[10];
	int b[10];
	for (int i=0; i < 2 ; i++){
		for (int k=0; k < 10; k++)
			a[k] = k + i;
		for (int j=0; j < 10; j++)
			b[j] = a[j];
	}
	

	return a[0] + b[9];
}
