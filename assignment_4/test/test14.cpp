int main(){
	int a[10];
	int b[10];
	for (int k=5; k < 10; k++){
		a[k] = k*(k/2);
		a[k] -= 1;
	}
	for (int i=0; i < 10 ; i++){
		a[i] = i;
		a[i] = a[i] + i;
	}
	for (int j=0; j < 10; j++)
		b[j] = a[j];

	return a[0] + b[2];
}
