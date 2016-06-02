#pragma once
#include "Thread.h"
#include <stdio.h>
#include "BeholderRC.h"
#include <windows.h>
#include "BeholdRemote.h"


class BeholdProc
{

protected:

public:
	BeholdInfo		*info;
	BeholdRemote	*readKey;
	HWND			pointer;

	BeholdProc(HWND data = NULL, LPWSTR *nPipe = NULL)
	{
		char* namedPipe = new char;
		sprintf(namedPipe, "%S", nPipe[1]);
		info = new BeholdInfo(namedPipe);

		sprintf(namedPipe, "%S", nPipe[2]);
		readKey = new BeholdRemote(namedPipe);
		pointer = data;
		remote = new BeholderRC();
	}

	virtual ~BeholdProc(void)
	{
		if (info)
		{
			info->SetStop(true);
			delete info;
		}
		if (readKey)
		{
			readKey->SetStop(true);
			delete readKey;
		}
		if (remote)
			delete remote;
	}

	void Start()
	{
		if(info->IsRunning())
			info->SetStop(); //politely ask the thread to stop
		else
			info->Start(pointer);

		if(readKey->IsRunning())
			readKey->SetStop(); //politely ask the thread to stop
		else
			readKey->Start(pointer);

	}

	bool IsRunning()
	{
		if (info->IsRunning() && readKey->IsRunning())
			return true;
		return false;
	}

};
