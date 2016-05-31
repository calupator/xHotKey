#pragma once

#include <process.h>
#include <Windows.h>
class Thread
{
public:

	enum Priority
	{
		Idle = THREAD_PRIORITY_IDLE,
		Lowest = THREAD_PRIORITY_LOWEST,
		BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
		Normal = THREAD_PRIORITY_NORMAL,
		AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
		Highest = THREAD_PRIORITY_HIGHEST,
		TimeCritical = THREAD_PRIORITY_TIME_CRITICAL
	};

	inline Thread(void) : hThread(0), running(0), stop(0) {}
	inline ~Thread(void) {}
	bool Start(HWND data = NULL, bool suspended = false);
	inline void SetStop(bool stop = true) { this->stop = stop; }
	inline bool GetStop() { return stop; }
	bool Terminate(int ret = 0);
	int Suspend();
	int Resume();
	inline bool IsRunning() { return running; }
	inline bool IsStarted() { return (bool)hThread; }
	inline void* GetData() { return data; }
	inline bool SetPriority(Priority priority) { return SetThreadPriority(hThread,priority); }
	inline Priority GetPriority() { return (Priority)GetThreadPriority(hThread); }
	inline operator HANDLE() { return hThread; }

protected:
	static unsigned int __stdcall _ThreadProc(void* param);
	virtual unsigned int ThreadProc();

protected:
	HANDLE hThread;
	HWND data;
	bool running;
	bool stop;
};
