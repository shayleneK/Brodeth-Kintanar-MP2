#include <stdio.h>

//extern void asmfunc();
extern void asm(int n, double* X, double* Y, double* Z, double A);
int main() {
	double A = 2.0;
	double X[] = { 1.0, 2.0, 3.0 };
	double Y[] = { 11.0, 12.0, 13.0 };
	double Z[3];
	int n = 3;

	asm(n, X, Y, Z, A);

	printf("Z: ");
	int i;
	for (i = 0; i < n; i++) {
		printf("%f\n", Z[i]);
	}

	return 0;
}