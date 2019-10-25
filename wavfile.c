#include "wavfile.h"

void adjustNum(int *num, char sampleLen)
{
	int x, orNum;
	switch (sampleLen)
	{
	case 1:
		x = 0x80;
		orNum = 0xFFFFFF00;
		break;
	case 2:
		x = 0x8000;
		orNum = 0xFFFF0000;
		break;
	case 3:
		x = 0x800000;
		orNum = 0xFF000000;
	default:
		return;
	}

	if(*num & x)
	{
		*num = *num | orNum;
	}
}

LPFRAME loadWavFileData(FILE *fp, LPWAVFILE wavInfo)
{
	if(!fp) return NULL;
	if(!fread(wavInfo, sizeof(WavFile), 1, fp)) return NULL;
	LPFRAME list = createEmptyHead();
	LPFRAME tail = list;

	int i;
	char samplen = wavInfo->BitsPerSample/8;
	if(wavInfo->NumChannels == 1)
	{
		tail->leftSample = 0;
		while(fread(&tail->leftSample, samplen, 1, fp))
		{
			adjustNum(&tail->leftSample, samplen);
			tail->next = (LPFRAME)malloc(sizeof(Frame));
			tail = tail->next;
			tail->next = NULL;
			tail->leftSample = 0;
		}
	}
	else if(wavInfo->NumChannels == 2)
	{
		tail->leftSample = 0;
		tail->rightSample = 0;
		while(fread(&tail->leftSample, samplen, 1, fp))
		{
			fread(&tail->rightSample, samplen, 1, fp);

			adjustNum(&tail->leftSample, samplen);
			adjustNum(&tail->rightSample, samplen);

			tail->next = (LPFRAME)malloc(sizeof(Frame));
			tail = tail->next;
			tail->next = NULL;
			tail->leftSample = 0;
			tail->rightSample = 0;
		}
	}
	else
	{
		return NULL;
	}
	
	return list;
	
}

LPFRAME createEmptyHead()
{
	LPFRAME node = (LPFRAME)malloc(sizeof(Frame));
	node->next = NULL;
	return node;
}

LPFRAME createListHead(int left, int right)
{
	return createNode(left, right);
}

LPFRAME createNode(int left, int right)
{
	LPFRAME node = (LPFRAME)malloc(sizeof(Frame));
	node->leftSample = left;
	node->rightSample = right;
	node->next = NULL;
	return node;
}

LPFRAME addWateNode(LPFRAME list, LPFRAME node)
{
	if (!list)
	{
		return node;
	}

	LPFRAME it = list;
	while(it->next!=NULL) it = it->next;
	it->next = node;
	node->next = NULL;

	return list;
}

LPFRAME delWateNode(LPFRAME list, LPFRAME node)
{
	LPFRAME it;

	if(list == node)
	{
		it = list->next;
		free(list);
		return it;
	}

	it = list;
	while(it->next != NULL)
	{
		if(it->next == node)
		{
			it->next = node->next;
			free(node);
			return list;
		}
	}

	return list;
} 

int getNodeCount(LPFRAME list)
{
	LPFRAME it;
	int count = 0;
	for(it = list; it->next!=NULL; it = it->next)
	{
		count++;
	}
	return count;
}

int getMaxVaule(LPFRAME list)
{
	int x = list->leftSample;
	LPFRAME it;
	for(it = list; it!=NULL; it = it->next)
	{
		if(it->leftSample > x)
		{
			x = it->leftSample;
		}
	}
	return x;
}

int getMinVaule(LPFRAME list)
{
	int x = list->leftSample;
	LPFRAME it;
	for(it = list; it!=NULL; it = it->next)
	{
		if(it->leftSample < x)
		{
			x = it->leftSample;
		}
	}
	return x;
}