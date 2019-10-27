#include "dft.h"

int dft(float input[], int n_input, Vector output[], int c_begin, int c_end){
	int i, j;
	int k;

	k = 0;
	for(i = c_begin; i<c_end; i++)
	{
		output[k].image = 0;
		output[k].real = 0;
		for(j = 0; j<n_input; j++)
		{
			output[k].real += input[j] * cos(2*PI*i*j/n_input);
			output[k].image -= input[j] * sin(2*PI*i*j/n_input);
		}
		k++;
	}
	
}

float vabs(Vector v){
	return sqrt(pow(v.image,2) + pow(v.real, 2));
}

void abs_vector(Vector input[], float output[], int n){
	for(n = n-1;n>=0; n--){
		output[n] = sqrt(pow(input[n].image,2) + pow(input[n].real, 2));
	}
}

void normalize(float input[], float output[], int n){
	int i;
	float sigma, min;	// temporarily be used to store the max value.
	sigma = input[0];
	min = input[1];
	for(i = 0; i<n; i++){
		if(input[i] > sigma) {
			sigma = input[i];
			continue;
		}
		if(input[i] < min) min = input[i];
	}

	sigma -= min;

	for(i = 0; i<n; i++){
		output[i] = (input[i]-min)/sigma;
	}

}