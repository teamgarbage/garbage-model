#include "main.h"
#include "wavfile.h"

#define FILENAME "hai.wav"

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

	printf("%d\n", getNodeCount(list));

	LPFRAME it = list;
	int i = 0;
	while(it != NULL)
	{
		// printf("%8x,%8x\t", it->leftSample, it->rightSample);
		// printf("%8d,%8d\t", it->leftSample, it->rightSample);
		// if(i++ % 5 == 0) putchar('\n');
		it = it->next;
	}

	return 0;
}