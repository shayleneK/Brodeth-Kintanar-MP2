#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//extern void asmfunc();
extern void kernel_asm(int n, double* X, double* Y, double* Z, double A);

static void kernel_c(int n, double* X, double* Y, double* Z, double A) {
	int i;
	for (i = 0; i < n; i++) {
		Z[i] = ((A * X[i]) + Y[i]);
	}

};

int main() {
	double A = 2.0; //constant A
	int n = 3; //size 
	int i; //counter

	//C initialize
	double X[] = { 1.0, 2.0, 3.0 };
	double Y[] = { 11.0, 12.0, 13.0 };
	double Z[3];

	//C
	kernel_c(n, X, Y, Z, A);

	//C printing
	printf("Kernel C function ==> Z: ");

	for (i = 0; i < n; i++) {
		printf("%f\n", Z[i]);
	}

	//Assembly initialize
	X[0] = 1.0; X[1] = 2.0; X[2] = 3.0;
	Y[0] = 11.0; Y[1] = 12.0; Y[2] = 13.0;

	//Assembly 
	kernel_asm(n, X, Y, Z, A);

	//Assembly Print
	printf("Kernel Assembly function ==> Z: ");
	for (i = 0; i < n; i++) {
		printf("%f\n", Z[i]);
	}

	return 0;
}
