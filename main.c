#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//extern void asmfunc();
extern void kernel_asm(long long int n, double* X, double* Y, double* Z, double A);

static void kernel_c(long long int n, double* X, double* Y, double* Z, double A) {
	int i;
	for (i = 0; i < n; i++) {
		Z[i] = ((A * X[i]) + Y[i]);
	}

};

int main() {

	//initialize                        //2^20
	unsigned long long int ARRAY_SIZE = 1048576;
	unsigned long long int ARRAY_BYTES = ARRAY_SIZE * sizeof(double);
	double A = 2.0; //constant A
	long long int i; //counter

	//Initialize clock
	clock_t start, end;
	double time_taken;

	//declare arrays
	double *X;
	double *Y;
	double *Z;

	X = (double*)malloc(ARRAY_BYTES);
	if (X == NULL) { //test to see if malloc fails --> exit the program if so
		printf("Memory allocation failed for X\n");
		return 1; 
	}
	Y = (double*)malloc(ARRAY_BYTES);
	if (Y == NULL) {
		printf("Memory allocation failed for Y\n");
		return 1;
	}
	Z = (double*)malloc(ARRAY_BYTES);
	if (Z == NULL) {
		printf("Memory allocation failed for Z\n");
		return 1; 
	}
	//C initialize arrays
	for (i = 0; i < ARRAY_SIZE; i++) {
		//double x = 1.0;
		X[i] = 1.0 + i;
	}

	for (i = 0; i < ARRAY_SIZE; i++) {
		//double y = 11.0;
		Y[i] = 11.0 + i;
	}

	for (i = 0; i < ARRAY_SIZE; i++) {
		Z[i] = 0;
	}

	//C
	//call clock
	start = clock();

	kernel_c(ARRAY_SIZE, X, Y, Z, A);

	end = clock();

	//in miliseconds
	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);


	//C printing
	printf("Kernel C function ==> Z: \n");

	for (i = 0; i < 10; i++) {
		printf("Z[%lld] = %f\n", i, Z[i]);
	}
	printf("Kernel C Function Time : %f ms\n", time_taken);


	//Assembly initialize
	for (i = 0; i < ARRAY_SIZE; i++) {
		//double x = 1.0;
		X[i] = 1.0 + i;
	}

	for (i = 0; i < ARRAY_SIZE; i++) {
		//double y = 11.0;
		Y[i] = 11.0 + i;
	}

	for (i = 0; i < ARRAY_SIZE; i++) {
		Z[i] = 0;
	}

	//Assembly 
	//start clock
	start = clock();

	kernel_asm(ARRAY_SIZE, X, Y, Z, A);

	end = clock();

	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);


	//Assembly Print
	printf("Kernel Assembly function ==> Z: \n");
	for (i = 0; i < 10; i++) {
		printf("Z[%lld] = %f\n", i, Z[i]);
	}
	printf("Kernel Assembly Function Time : %f ms \n ", time_taken);

	//release memory allocated to the arrays --> for more memory space 
	free(X);
	free(Y);
	free(Z);

	return 0;
}
