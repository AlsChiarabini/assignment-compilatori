int main(){
	int a[11] = {0,0,0,0,0,0,0,0,0,0,0};
	int b[10];
	for (int i=0; i < 10 ; i++)
		a[i] = i;
	for (int i=0; i < 10; i++)
		b[i] = a[i+1];

	return a[0] + b[9];
}
