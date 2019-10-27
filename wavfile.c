#include "wavfile.h"

void adjustNum(int *num, char bps){
	if(bps == 32) return;
	char emptybits = 32-bps;
	*num<<=emptybits;
	// *num/=pow(2,emptybits);

}

LPFRAME loadWavFileData(FILE *fp, LPWAVFILE wavInfo){
	if(!fp) return NULL;
	if(!fread(wavInfo, sizeof(WavFile), 1, fp)) return NULL;
	LPFRAME list = createEmptyHead();
	LPFRAME tail = list;

	int i;
	char sampleSizeB = wavInfo->BitsPerSample/8;
	if(wavInfo->NumChannels == 1){
		tail->samples[0] = 0;
		while(fread(&tail->samples[0], sampleSizeB, 1, fp))
		{
			adjustNum(&tail->samples[0], wavInfo->BitsPerSample);
			tail->next = (LPFRAME)malloc(sizeof(Frame));
			tail = tail->next;
			tail->next = NULL;
			tail->samples[0] = 0;
		}
	}
	else if(wavInfo->NumChannels == 2){
		tail->samples[0] = 0;
		tail->samples[1] = 0;
		while(fread(&tail->samples[0], sampleSizeB, 1, fp))
		{
			fread(&tail->samples[1], sampleSizeB, 1, fp);

			adjustNum(&tail->samples[0], wavInfo->BitsPerSample);
			adjustNum(&tail->samples[1], wavInfo->BitsPerSample);

			tail->next = (LPFRAME)malloc(sizeof(Frame));
			tail = tail->next;
			tail->next = NULL;
		tail->samples[0] = 0;
			tail->samples[1] = 0;
		}
	}
	else{
		return NULL;
	}
	
	return list;
	
}

LPFRAME createEmptyHead(){
	LPFRAME node = (LPFRAME)malloc(sizeof(Frame));
	node->next = NULL;
	return node;
}

LPFRAME createListHead(int left, int right){
	return createNode(left, right);
}

LPFRAME createNode(int s1, int s2){
	LPFRAME node = (LPFRAME)malloc(sizeof(Frame));
	node->samples[0] = s1;
	node->samples[1] = s2;
	node->next = NULL;
	return node;
}

LPFRAME addWateNode(LPFRAME list, LPFRAME node){
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

LPFRAME delWateNode(LPFRAME list, LPFRAME node){
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

int getNodeCount(LPFRAME list){
	LPFRAME it;
	int count = 0;
	for(it = list; it->next!=NULL; it = it->next)
	{
		count++;
	}
	return count;
}

int getMaxVaule(LPFRAME list, int channel){
	int x = list->samples[channel];
	LPFRAME it;
	for(it = list; it!=NULL; it = it->next)
	{
		if(it->samples[channel] > x)
		{
			x = it->samples[channel];
		}
	}
	return x;
}

int getMinVaule(LPFRAME list, int channel){
	int x = list->samples[channel];
	LPFRAME it;
	for(it = list; it!=NULL; it = it->next)
	{
		if(it->samples[channel] < x)
		{
			x = it->samples[channel];
		}
	}
	return x;
}


int ListToFloats(LPFRAME list, float result[], int n_result, int channel){

	int i;
	int n_node = getNodeCount(list);

	if(n_node < n_result){
		n_result = n_node;
	}

	LPFRAME it = list;
	for(i = 0; i<n_result; i++){
		result[i] = it->samples[channel];
		it = it->next;
		if(!it) return i+1;
	}

	return n_result;

}