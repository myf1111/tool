// AutoTag.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include <sys/types.h>  
#include<string.h>

int _System(const char * cmd, char *pRetMsg, int msg_len, int mod = 0);

int main(int argc, char* argv[])
{
	char cmd[100] = "", resut[100] = "";
	char cmdd[100] = "";
	int status, tag;


	//system("git status");

	_System("git status", resut, 100, 2);
	if ((strstr(resut, "working tree clean") != NULL) && (strstr(resut, "nothing to commit") != NULL))
	{
		printf("***********nothing to commit,no need new tag***************");
		return 0;
	}

	if (argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL)
			return 0;
		while (feof(fp) == 0)
		{
			memset(cmdd, 0, 100 * sizeof(char));
			fgets(cmdd, 100, fp);
			system(cmdd);
		}
		//system(argv[1]);
		fclose(fp);
	}

	system("git fetch --tags");
	sprintf(cmd, "git describe --tags %cgit rev-list --tags --max-count=1%c", 96, 96);
	sprintf(cmd, "git tag");
	_System(cmd, resut, 100);

	if (strcmp("", resut) == 0)
	{
		tag = 1;
	}
	else
	{
		tag = atoi(resut) + 1;

	}


	sprintf(cmdd, "git tag %d", tag);
	system(cmdd);
	memset(cmdd, 0, 100 * sizeof(char));
	sprintf(cmdd, "git push origin %d", tag);
	system(cmdd);



	return 0;
}



int _System(const char * cmd, char pRetMsg[100], int msg_len = 10, int mod)
{
	FILE * fp;
	char * p = NULL;
	int res = -1;
	int ss = 0;

	char temp[100] = "0";
	if ((fp = _popen(cmd, "r")) == NULL)
	{
		printf("Popen Error!\n");
		return -2;
	}
	else
	{
		//get lastest result
		if (mod == 0)
		{
			while (fgets(pRetMsg, msg_len, fp) != NULL)
			{

				if (atoi(temp)<atoi(pRetMsg))
				{
					strncpy(temp, pRetMsg, 100);
				}
			}
			strncpy(pRetMsg, temp, 100);
		}
		else
		{
			while (fgets(pRetMsg, msg_len, fp) != NULL)
			{
				ss++;
				//printf("%s", pRetMsg);
			}
			if (ss > 0 && strcmp(pRetMsg, "") == 0)
			{
				strcpy(pRetMsg, "hello");
			}
		}
		if ((res = _pclose(fp)) == -1)
		{
			printf("close popenerror!\n");
			return -3;
		}

		if (strlen(pRetMsg)>99)
			pRetMsg[strlen(pRetMsg) - 1] = '\0';
		else
			pRetMsg[strlen(pRetMsg)] = '\0';
		return 0;
	}
}