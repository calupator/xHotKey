#pragma once
#include "thread.h"
#include "BeholdProc.h"
#include "stdafx.h"

static BeholderRC *remote;

class BeholdRemote 
	: public Thread
{
public:
	BeholdRemote(char* namePipeGetKey)
	{
		sprintf(szPipeName, "%s%s", "\\\\.\\pipe\\", "pipe2");
		//sprintf(szPipeName, "%s%s", "\\\\.\\pipe\\", namePipeGetKey);
	}

	~BeholdRemote()
	{
		CloseHandle(hNamedPipe);
	}

protected:
	unsigned int ThreadProc()
	{
		// Создаем канал с процессом PIPES
		hNamedPipe = CreateFile(szPipeName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if(hNamedPipe == INVALID_HANDLE_VALUE)
		{
			SendMessage(data, WM_DESTROY, NULL, NULL);
			return 0;
		}
		while (!stop)
		{
			ULONG irKey = remote->GetRemoteEx();
			if (irKey > 0)
			{
				DWORD dwTime = ::GetTickCount();
				if (!(dwTime - m_dwLastExec < 200))
					//return 0;
				{
					if (irKey == 2255183011)
						;//SendMessage(hwnd, WM_DESTROY, NULL, NULL);
					m_dwLastExec = ::GetTickCount();
					//MessageBox(NULL, "", "", MB_OK);

					memset(szOutBuf, 0xcc, 80);
					sprintf(szOutBuf, "%d\n", irKey);
					if (!WriteFile(hNamedPipe, szOutBuf, strlen(szOutBuf), &cbWritten, NULL))
						break;
					Sleep(100);
				}
			}
		}
		return 0;
	}

protected:
	// Идентификатор канала Pipe
	HANDLE hNamedPipe;
	// Количество байт, переданных через канал
	DWORD  cbWritten;
	// Количество байт, принятых через канал
	DWORD  cbRead;
	// Буферы для приема/передачи данных
	char   szInBuf[80];
	char   szOutBuf[80];
	// Буфер для имени канала Pipe
	char   szPipeName[80];
	// Время последнего обращения
	DWORD m_dwLastExec;
};


class BeholdInfo 
	: public Thread
{
public:
	BeholdInfo(char* namePipeInfo)
	{
		wsprintf(szPipeName, "%s%s", "\\\\.\\pipe\\", "pipe1");
		//wsprintf(szPipeName, "%s%s", "\\\\.\\pipe\\", namePipeInfo);
	}

	~BeholdInfo()
	{
		CloseHandle(hNamedPipe);
	}

protected:
	unsigned int ThreadProc()
	{
		// Создаем канал с процессом PIPES
		hNamedPipe = CreateFile(szPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if(hNamedPipe == INVALID_HANDLE_VALUE)
		{
			SendMessage(data, WM_DESTROY, NULL, NULL);
			return 0;
		}

		// Цикл обмена данными с серверным процессом
		while(!stop)
		{
			memset(szOutBuf, 0, 80);
			// Получаем эту же команду обратно от сервера
			if(ReadFile(hNamedPipe, szInBuf, sizeof(szInBuf), &cbRead, NULL))
			{
				szInBuf[cbRead-2] = 0;
				if (strstr(szInBuf, "GetCardCount"))
				{
					sprintf(szOutBuf, "%d\n", remote->GetCount());
				}
				if (strstr(szInBuf, "SelectCard"))
				{
					memset(szInBuf, 0xcc, 80);
					if(ReadFile(hNamedPipe, szInBuf, sizeof(szInBuf), &cbRead, NULL))
					{
						szInBuf[cbRead-2] = 0;
						sprintf(szOutBuf, "%d\n", remote->SelectCard(atoi(szInBuf))? 1 : 0);
					}
				}
				if (strstr(szInBuf, "GetCardName"))
				{
					memset(szInBuf, 0xcc, 80);
					if(ReadFile(hNamedPipe, szInBuf, sizeof(szInBuf), &cbRead, NULL))
					{
						szInBuf[cbRead-2] = 0;
						sprintf(szOutBuf, "%s\n", remote->GetName(atoi(szInBuf)));
					}
				}
			}
			// Если произошла ошибка, выводим ее код и
			// завершаем работу приложения
			else
			{
				SendMessage(data, WM_DESTROY, NULL, NULL);
			}

			// В ответ на команду "exit" завершаем цикл
			// обмена данными с серверным процессом
			if(!strcmp(szInBuf, "exit"))
			{
				SendMessage(data, WM_DESTROY, NULL, NULL);
				break;
			}
			// Передаем введенную строку серверному процессу
			// в качестве команды
			if(!WriteFile(hNamedPipe, szOutBuf, strlen(szOutBuf), &cbWritten, NULL))
				;//break;				
		}
		return 0;
	}

protected:
	// Идентификатор канала Pipe
	HANDLE hNamedPipe;
	// Количество байт, переданных через канал
	DWORD  cbWritten;
	// Количество байт, принятых через канал
	DWORD  cbRead;
	// Буферы для приема/передачи данных
	char   szInBuf[80];
	char   szOutBuf[80];
	// Буфер для имени канала Pipe
	char   szPipeName[80];
};

