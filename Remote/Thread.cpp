#include "StdAfx.h"
#include "thread.h"

bool Thread::Start(HWND data, bool suspended)
{
	//cannot start twice
	if(hThread)
		return false;

	//start the thread
	this->data = data;
	unsigned int id;
	hThread = (HANDLE)_beginthreadex(NULL,0,_ThreadProc,this,(suspended)?CREATE_SUSPENDED:0,&id);
    	
	//set state
	running = (hThread!=0) ? true : false;

	return running;
}

bool Thread::Terminate(int ret)
{
	//cannot stop what doesn't exist
	if(!hThread)
		return false;

	//terminate
	running = !TerminateThread(hThread,ret);
	if(running==false)
	{
		stop = false;
		CloseHandle(hThread);
		hThread = 0;
	}

	return !running;
}

int Thread::Suspend()
{
	int ret = SuspendThread(hThread);
	running = (ret<=0);
	return ret;
}

int Thread::Resume()
{
	int ret = ResumeThread(hThread);
	running = (ret<=0);
	return ret;
}

unsigned int Thread::_ThreadProc(void* param)
{
	//invoke the virtual thread procedure
	Thread* pThread = (Thread*)param;
	int ret = pThread->ThreadProc();

	//set state
	pThread->running = false;
	CloseHandle(pThread->hThread);
	pThread->hThread = 0;
	pThread->SetStop(false);

	//exit
	_endthreadex(ret); //actual termination
	return ret; //we never get here
}

unsigned int Thread::ThreadProc()
{
	////////////////////////////////////////////////
	//this is an example of derived implementation//
	////////////////////////////////////////////////

	/*
	void* pData = GetData();
	
	//...

	while(true)
	{
		if(GetStop())
			return 0;
		
		//do something lengthy, but not too much
		//...
	}
	*/

	return 0; //always return rather than call _endthread[ex] or ExitThread
}
