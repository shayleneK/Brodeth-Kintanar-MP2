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

	//Initialize clock
	clock_t start, end;
	double time_taken;

	//C initialize
	double X[] = { 1.0, 2.0, 3.0 };
	double Y[] = { 11.0, 12.0, 13.0 };
	double Z[3];


	//C
	//call clock
	start = clock();

	kernel_c(n, X, Y, Z, A);

	end = clock();

	//in miliseconds
	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);


	//C printing
	printf("Kernel C function ==> Z: ");

	for (i = 0; i < n; i++) {
		printf("%f\n", Z[i]);
	}
	printf("Kernel C Function Time : %f ms\n", time_taken);


	//Assembly initialize
	X[0] = 1.0; X[1] = 2.0; X[2] = 3.0;
	Y[0] = 11.0; Y[1] = 12.0; Y[2] = 13.0;

	//Assembly 
	//start clock
	start = clock();

	kernel_asm(n, X, Y, Z, A);

	end = clock();

	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);


	//Assembly Print
	printf("Kernel Assembly function ==> Z: ");
	for (i = 0; i < n; i++) {
		printf("%f\n", Z[i]);
	}
	printf("Kernel Assembly Function Time : %f ms \n ", time_taken);

	return 0;
}
