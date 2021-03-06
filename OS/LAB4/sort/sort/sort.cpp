// sort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <conio.h>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

#define MAXLINE 4096

int scmp(const void *p1, const void *p2)
{
	const char *s1, *s2;

	s1 = *(char **)p1;
	s2 = *(char **)p2;
	return strcmp(s1, s2);
}

int main(int argc, char *argv[])
{
	FILE *ifp, *ofp;
	char *lineptr[MAXLINE];
	char s[MAXLINE];
	int i, nl, j, k;

	HANDLE hFile;
	unsigned char* dataPtr;
	DWORD dwLength;
	DWORD dwWritten;
	DWORD dwFileSize;
	char * buff;
	hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, TEXT("result.txt"));
	if (hFile == NULL)
		return 0;
	dataPtr = (unsigned char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (dataPtr == nullptr)
		return 0;
	buff = (char*)dataPtr;
	dwFileSize = GetFileSize(hFile, nullptr);
		/*if (dwFileSize == INVALID_FILE_SIZE) {
			printf("fileMappingCreate - GetFileSize failed, fname =  %s\n", TEXT("result.txt"));
			CloseHandle(hFile);
			return 0;
		}
		*/


	if (argv[0][2] == '1')
	{
		if ((ofp = fopen("in1O.txt", "w")) == NULL)
		{
			while (1)
				printf("in1O.txt can't open\n");
			perror("fopen");
			return -1;
		}
	}
	if (argv[0][2] == '2')
	{
		if ((ofp = fopen("in2O.txt", "w")) == NULL)
		{
			while (1)
				printf("in2O.txt can't open\n");
			perror("fopen");
			return -1;
		}
	}

	ifp = fopen(argv[0], "r");
	if (ifp == NULL)
	{
		while(1)
			perror("fopen");
		return -1;
	}

	for (i = 0; i < MAXLINE; )
	{
		if (fgets(s, sizeof(s), ifp) == NULL)
			break;
		if (*s != '\n')
			lineptr[i++] = strdup(s);
	}

	nl = i;
	qsort(lineptr, nl, sizeof(char *), scmp);
	if (argv[0][2] == '1')
	{
		strcat(buff, "\nin1O.txt\n");
	}
	if (argv[0][2] == '2')
	{
		strcat(buff, "\nin2O.txt\n");
	}
	for (i = 0; i < nl; i++)
	{
		strcat(buff, lineptr[i]);
	}
	strcat(buff, "\n");
	for (i = 0; i < nl; i++)
	{
		fprintf(ofp, "%s", lineptr[i]);
		free(lineptr[i]);
	}


	
	int err = FlushViewOfFile("result.txt", sizeof(buff));
	fclose(ifp);
	fclose(ofp);
	return 0;
}