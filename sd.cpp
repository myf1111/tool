// sd.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL)
			return -1;
		int i;
		char commd[100]="";

		fscanf(fp, "%d", &i);
		fclose(fp);
	    fp = fopen(argv[1], "w");
		fprintf(fp, "%d", i+1);
		fclose(fp);

		sprintf(commd, "git tag %d", i + 1);
		system(commd);
	}

    return 0;
}

