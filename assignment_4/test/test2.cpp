int main(){
	int a[10];
	int b[10];
	for (int i=0; i < 10 ; i++)
		a[i] = i;

	int f = 23*a[0];

	for (int j=0; j < 10; j++)
		b[j] = a[j];

	return a[0] + b[9];
}
