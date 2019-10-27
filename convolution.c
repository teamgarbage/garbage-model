#include "convolution.h"


#define FILTER_FSIZE 101
float filter[FILTER_FSIZE];

void initFilter(){
	srand(time(NULL));
	int i;
	for(i = 0; i<FILTER_FSIZE; i++){
		filter[i] = rand()%3;
	}
}

void convolution(float input[], int n, float output[]){
	int i, j;
	for(i = 0; i<n-FILTER_FSIZE+1; i++){
		output[i] = 0;
		for(j = 0; j<FILTER_FSIZE; j++){
			output[i]+=input[i+j]*filter[j];
		}
	}
}