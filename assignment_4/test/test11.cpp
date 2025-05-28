int main(){
	int a[10] = {0,0,0,0,0 ,0,0,0,0,0};
	
	for (int i=4; i < 8 ; i++)
		a[i] = i;
	for (int j=4; j < 8; j++)
		a[j-1] = j;		//WAW

	return a[0] + a[5];
}
