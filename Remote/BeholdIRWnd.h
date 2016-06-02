#pragma once

#include "BeholdProc.h"
#include <objbase.h>
#include "BeholderRC.h"

#include <stdio.h>

#define ID_TRAYICON         1
#define WM_TRAYICON         (WM_USER + 100)
#define WM_IRACTIVATED      (WM_USER + 101)

#define BIRW_BEHOLDTVTIMER     1
#define BIRW_IRACTIVATEDTIMER  2

class CBeholdIRWnd
{
public:
	static char ClassName[];
	CBeholdIRWnd(HINSTANCE hInst, LPWSTR *namedPipe);
	~CBeholdIRWnd(void);

	void Run();

protected:

	bool Initialize();
	void Terminate();

	ATOM MyRegisterClass();
	bool InitInstance();

protected:
	HINSTANCE       m_instance;
	HWND            m_window;
	BeholdProc		*beholdProcess;
	LPWSTR *Pipe;

protected:
	static DWORD m_dwLastExec;

	static CBeholdIRWnd*    s_beholdIRWnd;
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
};
