#include "main.h"
#include "wavfile.h"
#include "dft.h"
#include "convolution.h"


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


	/*
		codes above are not for the FPGA, what we need to send to the FPGA is the data0
	*/

	// normalization
	normalize(data0, data0, countOfSamples);		
	/*		暂时未定是对音频数据进行归一化处理还是对频域数据进行归一化处理
			但是按照MATLAB的实验来看，应该对音频数据进行归一化处理，这样得到的频域数据也比较好		*/
	
	Vector c0[5000];	// for saving the frequency domain data : from 0 to 4999, totally 5000 sample
	// Vector c1[5000];
	int freqBegin, freqEnd;
	freqBegin = 0;
	freqEnd = 5000;
	int n_c = dft(data0, countOfSamples, c0, freqBegin, freqEnd);
	/*********************************************************************************/
	/*			Discrete Fourier Transform(DFT), should be replace with FFT 		 */
	/*********************************************************************************/

	float c0l[5000];
	abs_vector(c0, c0l, n_c);
	// normalize(c0l, c0l, n_c);
	//	Discrete data after Fourier Transform will be change into vector, what we need is length of the vector

	float ff[4900];
	initFilter();
	convolution(c0l, n_c, ff);


	printf("pause");
	return 0;
}