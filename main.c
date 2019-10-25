#include "main.h"
#include "wavfile.h"

// #define FILENAME "hai.wav"
#define FILENAME "/home/alvis/desktop/sound-classification/wav/hai.wav"

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

	// printf("%d\n", getNodeCount(list));

	LPFRAME it = list;
	int i = 0;
	long sum_l = 0;
	long sum_r = 0;
	while(it != NULL)
	{
		// printf("%8x,%8x\t", it->leftSample, it->rightSample);
		// printf("%8d,%8d\t", it->leftSample, it->rightSample);
		// printf("%8lf,%8lf\t", it->leftSample, it->rightSample);
		// if(i++ % 5 == 0) putchar('\n');
		sum_l += it->leftSample;
		sum_r += it->rightSample;
		it = it->next;
	}

	// printf("%ld,%ld\n", sum_l, sum_r);
	// printf("%ld,%ld\n", sum_l/getNodeCount(list), sum_r/getNodeCount(list));

	printf("%d - %d = %d\n", getMaxVaule(list), getMinVaule(list), getMaxVaule(list) - getMinVaule(list));
	

	return 0;
}