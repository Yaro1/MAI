// LAB_1_2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <Windows.h>
#include <conio.h>

char * change_name(_TCHAR * s)
{
	int count = 0;
	char a = 0;
	a = s[count];
	for (; a != 0;)
	{
		count++;
		a = s[count];
	}
	count++;

	char * out = (char *)malloc(count + 1);
	for (int j = 0; j < count - 1; j++)
		out[j] = s[j];
	for (int j = count - 1; j != count - 5; j--)
		out[j] = out[j - 1];
	out[count - 5] = 'O';
	out[count] = 0;

	return out;
}

int conclusion(char * name)
{
	FILE * hi;
	char n;
	hi = fopen(name, "rt");
	while (!feof(hi))
	{
		int res = fscanf(hi, "%c", &n);
		if (n == EOF)
			break;
		printf("%c", n);
	}
	fclose(hi);
	return 0;
}

struct Handle {
	HANDLE hPipe;
};

int _tmain(int argc, _TCHAR* argv[])
{
	FILE * interaction;
	interaction = fopen("interaction.txt", "w");
	HANDLE hPipe;
	char buffer[1024];
	DWORD dwRead;

	// PIPE
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);


	FILE * log;
	log = fopen("log.txt", "w");
	if (log == nullptr)
		printf("Can't create log file\n");

	if (argc != 3)
	{
		fprintf(log, "Number of parametrs is not 3.\n");
		printf("Error. You should enter two name of file, whose programm sort.");
		return 0;
	}
	
	PROCESS_INFORMATION ProcessInfo1; //This is what we get as an [out] parameter
	ZeroMemory(&ProcessInfo1, sizeof(PROCESS_INFORMATION));
	STARTUPINFO StartupInfo1; //This is an [in] parameter
	TCHAR lpszClientPath1[] = L"1";
	ZeroMemory(&StartupInfo1, sizeof(StartupInfo1));
	StartupInfo1.cb = sizeof(STARTUPINFO); //Only compulsory field

	for(int i = 0; i < 7;i++)
		printf("%c", argv[1][i]);
	printf("\n");


	bool process1 = CreateProcess(L"sort.exe", //NULL
	//bool process = CreateProcess(L"sort.exe", //NULL
		argv[1], //lpszClientPath,
		NULL, NULL, true,
		CREATE_NEW_CONSOLE,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
		NULL, NULL,
		&StartupInfo1,
		&ProcessInfo1);
	if (process1 == false)
	{
		fprintf(log, "Error of creating first process.\n");
		printf("Error of creating first process.\n");
		return 0;
	}

	for (int i = 0; i < 7; i++)
		printf("%c", argv[2][i]);
	printf("\n");


	PROCESS_INFORMATION ProcessInfo2; //This is what we get as an [out] parameter
	ZeroMemory(&ProcessInfo2, sizeof(PROCESS_INFORMATION));
	STARTUPINFO StartupInfo2; //This is an [in] parameter
	TCHAR lpszClientPath2[] = L"2";
	ZeroMemory(&StartupInfo2, sizeof(StartupInfo2));
	StartupInfo2.cb = sizeof(STARTUPINFO); //Only compulsory field


	bool process2 = CreateProcess(L"sort.exe", //NULL
		//bool process = CreateProcess(L"sort.exe", //NULL
		argv[2], //lpszClientPath,
		NULL, NULL, true,
		CREATE_NEW_CONSOLE,// CREATE_NEW_CONSOLE|CREATE_SUSPENDED
		NULL, NULL,
		&StartupInfo2,
		&ProcessInfo2);
		
	if (process2 == false)
	{
		fprintf(log ,"Error of creating second process.\n");
		printf("Error of creating second process.\n");
		return 0;
	}

	// PIPE
	if (ConnectNamedPipe(hPipe, NULL) != FALSE)   
	{
		while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
		{
			buffer[dwRead] = '\0';
			fprintf(interaction, "%s", buffer);
		}
	}
	DisconnectNamedPipe(hPipe);
	fclose(interaction);


	WaitForSingleObject(ProcessInfo1.hProcess, INFINITE);
	fprintf(log, "Process1 is over sucess.\n");
	WaitForSingleObject(ProcessInfo2.hProcess, INFINITE);
	fprintf(log, "Process2 is over sucess.\n");

	CloseHandle(ProcessInfo1.hThread);
	CloseHandle(ProcessInfo1.hProcess);
	fprintf(log, "First process end work.\n");

	CloseHandle(ProcessInfo2.hThread);
	CloseHandle(ProcessInfo2.hProcess);
	fprintf(log,"Second process end work.\n");


	// НАПИСАТЬ ВЫВОД

	char * out1 = change_name(argv[1]);
	char * out2 = change_name(argv[2]);
	printf("%s\n", out1);
	conclusion(out1);
	fprintf(log ,"First file show ok.\n");
	printf("\n\n");
	printf("%s\n", out2);
	conclusion(out2);
	fprintf(log, "Second file show ok.\n");
	
	fclose(log);
	return 0; 
}
