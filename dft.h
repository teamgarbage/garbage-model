#include <math.h>
#include <stdio.h>

#define PI 3.141592653589

typedef struct vector{
	float real;
	float image;
}Vector;

int dft(float input[], int n_input, Vector output[], int c_begin, int c_end);
float vabs(Vector v);
void abs_vector(Vector input[], float output[], int n);