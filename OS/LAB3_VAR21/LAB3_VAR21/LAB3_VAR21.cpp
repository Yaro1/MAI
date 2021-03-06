// LAB3_VAR21.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include "process.h" 

#define THREADS_NUMBER 10
#define ITERATIONS_NUMBER 100
#define PAUSE 10 /* ms */

HANDLE hSemaphore;
LONG cMax = 8;
LONG dwCounter = 0;

struct WIG {
	int * was_in_graf;
	int size;
};

struct QUE {
	int * queue;
	int size;
};

struct Elem {
	int key;
	int num;
};

struct Data {
	Elem ** matrica;
	WIG * wig;
	int a;
	int b;
	int num;
	int min;
};

int NumMin(Elem ** matrica, WIG * wig, int a, int b, int num)
{
	int min = -1;
	QUE * q = (QUE *)malloc(sizeof(QUE));
	q->queue = (int*)malloc(sizeof(int) * num);
	q->size = 0;

	int index = 0;
	for (int i = 0; i < num; i++)
	{
		if (matrica[i][a].key == 0)
			continue;
		q->queue[index] = matrica[i][a].num;
		index++;
		q->size++;
	}
	wig->was_in_graf[wig->size] = a;
	wig->size++;
	
	for (int l = 0; l < q->size; l++)
	{
		int flag = 0;
		
		for (int k = 0; k < wig->size; k++)
		{
			
			if (wig->was_in_graf[k] == q->queue[l])
			{
				flag = 1;
			}
			
		}
		
		if (b == q->queue[l])
		{
			if (matrica[a][b].key != 0)
			{
				if (min == -1)
					min = matrica[a][b].key;
				else if (min > matrica[a][b].key)
					min = matrica[a][b].key;
			}
			continue;
		}
		if (flag == 0)
		{
			int prom_min = matrica[a][q->queue[l]].key;
			int vozvr_znach;
			vozvr_znach = NumMin(matrica, wig, q->queue[l], b, num);
			if (vozvr_znach == 0 || vozvr_znach == -1)
				continue;
			else
				prom_min += vozvr_znach;
			if (min == -1)
				min = prom_min;
			else if (min > prom_min)
				min = prom_min;
		}
	}

	return min;
}


DWORD WINAPI ThreadProc(CONST LPVOID lpParam) {
	DWORD i;
	Data * in = reinterpret_cast<Data*>(lpParam);
	in->min = NumMin(in->matrica, in->wig, in->a, in->b, in->num);
	//Sleep(PAUSE);
	dwCounter--;
	ExitThread(0);
}


VOID Error(CONST HANDLE hStdOut, CONST LPCWSTR szMessage) {
	DWORD dwTemp;
	TCHAR szError[256];
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);
	wsprintf(szError, TEXT("LastError = %d\r\n"), GetLastError());
	WriteConsole(hStdOut, szError, lstrlen(szError), &dwTemp, NULL);
	ExitProcess(0);
}

int Min(Data ** data, int size)
{
	int min = -1;
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (data[i]->min == -1 || data[i]->min == 0)
			continue;
		else if (flag == 0)
		{
			min = data[i]->min;
			flag = 1;
			continue;
		}
		else if (min > data[i]->min)
		{
			min = data[i]->min;
		}
	}
	return min;
}

// 0 : no way

int main(int argc, char *argv[])
{
	FILE *f;
	char *estr;

	if (argc > 1)
	{
		cMax = argv[1][0] - '0';
		printf("Max thread's is : %d\n", cMax);
	}

	int num;
	printf("Number of string in matrica is : \n");
	scanf("%d", &num);
	printf("\n");

	f = fopen("data1.txt", "r");
	if (f == NULL)
	{
		perror("Reading file data1.txt ");
	}

	Elem ** matrica = (Elem **)malloc(sizeof(Elem) * num);
	for(int i = 0; i < num;i++)
		matrica[i] = (Elem *)malloc(sizeof(Elem) * num);
	int size = 0;
	int str = 0;


	char c;
	int len;
	for(int i = 0;!feof(f);i++)
	{
		fscanf(f, "%c", &c);
		if (c == EOF)
			break;
		if (c == ' ' || c == '\n' || c == '\0')
			continue;
		len = c - '0';
		matrica[str][size].key = len;
		matrica[str][size].num = str;
		size++;
		if (size == num)
		{
			size = 0;
			str++;
		}
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
			printf("%d ", matrica[i][j].key);
		printf("\n");
	}
	fclose(f);
	printf("Reading is successful.\n");
	
	printf("Enter number's vertex : \n");
	int a, b;
	scanf("%d %d", &a, &b);
	a--;
	b--;
	
	WIG * wig = (WIG *)malloc(sizeof(WIG));
	wig->was_in_graf = (int *)malloc(sizeof(int) * num); // вершины которые посетил
	wig->size = 0;




	QUE * q = (QUE *)malloc(sizeof(QUE));
	q->queue = (int*)malloc(sizeof(int) * num);
	q->size = 0;

	int index = 0;
	int straight = -1;
	for (int i = 0; i < num; i++)
	{
		if (matrica[i][a].key == 0)
			continue;
		if (matrica[i][a].num == b)
		{
			straight = matrica[i][a].key;
			continue;
		}
		q->queue[index] = matrica[i][a].num;
		index++;
		q->size++;
	}
	wig->was_in_graf[wig->size] = a;
	wig->size++;

	int * mas_min = (int *)malloc(sizeof(int) * q->size);
	Data ** data = (Data **)malloc(sizeof(Data) * q->size);
	for(int i = 0; i < q->size;i++)
		data[i] = (Data *)malloc(sizeof(Data) * q->size);
	for (int i = 0; i < q->size; i++)
	{
		data[i]->a = q->queue[i];
		data[i]->b = b;
		data[i]->matrica = matrica;
		data[i]->num = num;
		data[i]->wig = wig;
		data[i]->min = -1;
		mas_min[i] = matrica[a][q->queue[i]].key;
	}

	/*
	hSemaphore = CreateSemaphore(
		NULL,	// нет атрибута
		cMax,	// начальное состояние
		cMax,	// максимальное состояние
		NULL	// без имени
	);
	if (hSemaphore == NULL)
		printf("error create semaphore");
	*/
	//TCHAR szMessage[256];
	DWORD dwTemp, i;
	HANDLE hThreads[THREADS_NUMBER];
	CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*
	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	if (NULL == hMutex) {
		Error(hStdOut, TEXT("Failed to create mutex.\r\n"));
	}
	*/

	for (i = 0; i < q->size; i++) {
		while (dwCounter >= cMax)
		{
			
		}
		dwCounter++;
		hThreads[i] = CreateThread(NULL, 0, &ThreadProc, (LPVOID)data[i], 0, NULL);
		if (NULL == hThreads[i]) {
			Error(hStdOut, TEXT("Failed to create thread.\r\n"));
		}
	}

	WaitForMultipleObjects(q->size, hThreads, TRUE, INFINITE);
	/*
	wsprintf(szMessage, TEXT("Counter = %d\r\n"), dwCounter);
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);
	*/

	for (i = 0; i < q->size; i++) {
		CloseHandle(hThreads[i]);
	}

	for (int i = 0; i < q->size; i++)
		if (data[i]->min != 0 || data[i]->min != -1)
			data[i]->min += mas_min[i];

	int min = Min(data,q->size);
	if (straight != -1)
	{
		if (min > straight)
		{
			min = straight;
		}
		if (min == -1 || min == 0)
		{
			min = straight;
		}
	}
	if (min == -1 || min == 0)
		printf("No any ways.\n");
	else
		printf("The minimum way is : %d.\n", min);


	for (int i = 0; i < q->size; i++)
	{
		free(data[i]);
	}
	free(data);
	for (int i = 0; i < num; i++)
	{
		free(matrica[i]);
	}
	free(matrica);
	free(mas_min);
	free(q);


	return 0;
}

