#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"

unsigned int loadFile(const char* fileName, unsigned char** data)
{
	FILE* file = fopen(fileName, "rb");
	if(file != NULL)
	{
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		fseek(file, 0, SEEK_SET);
		*data = (unsigned char*)malloc(sizeof(unsigned char) * length);
		fread(*data, sizeof(unsigned char), length, file);
		fclose(file);
		return length;
	}
	else
	{
		return -1;
	}
}