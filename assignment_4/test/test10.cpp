int main(){
	int a[10] = {0,0,0,0,0,0,0,0,0,0};
	int b[10];
	
	
	for (int i=4; i < 9 ; i++)
		a[i] = i;
	for (int j=5; j < 10; j++)
		b[j] = a[j+1];

	return a[0] + b[9];
}
