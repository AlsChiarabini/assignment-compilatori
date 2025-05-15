int main(){
	int a[10];
	int b[10];
	for (int i=0; i < 10 ; i++)
		a[i] = i;

	int f = 23*a[0];	//Non ce adiacenza per colpa questa istruzione
				//Possibile opt: essendo che questa istruzione non ha influenza sul ciclo dopo si potrebbe fare cmq fusion e spostare l'ist sotto

	for (int j=0; j < 10; j++)
		b[j] = a[j];

	return a[0] + b[9];
}
