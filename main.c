#include "main.h"
#include "wavfile.h"
#include "dft.h"


// #define FILENAME "hai.wav"
#define FILENAME "/home/alvis/desktop/sound-classification/wav/test.wav"

int main()
{

	FILE *fp;
	WavFile wavInfo;
	LPFRAME list;

	fp = fopen(FILENAME, "rb");
	if(!fp) return 1;

	list = loadWavFileData(fp, &wavInfo);
	if(!list) return 2;

	fclose(fp);
	/* 			finished load wav data from wavfile,	data type: **link list**		*/



	float *data0;		/* just take one channel data	*/
	//float *data1;
	int countOfSamples = getNodeCount(list);

	data0 = (float*)malloc(countOfSamples*sizeof(float));
	// data1 = (float*)malloc(n*sizeof(float));
	if(!data0)return 2;
	// if(!data1)return 2;
	countOfSamples = ListToFloats(list, data0, countOfSamples, 0);
	// n = ListToFloats(list, data1, n, 1);
	/*			finished store data with a array of float rather then link list			*/


	
	Vector c0[5000];
	// Vector c1[5000];
	int freqBegin, freqEnd;
	freqBegin = 0;
	freqEnd = 5000;
	int n_c = dft(data0, countOfSamples, c0, freqBegin, freqEnd);
	
	float c0l[5000];
	abs_vector(c0, c0l, n_c);



	printf("pause");
	return 0;
}