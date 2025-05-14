#include <iostream>
int main(){
	int a[10];
	int b[10];
	int n = 1;
	std::cin >> n;
	if (n>0){
		for (int i=0; i < 10 ; i++)
			a[i] = i;
	}
	for (int j=0; j < 10; j++)
		b[j] = a[j];

	return a[0] + b[9];
}
