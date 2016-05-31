// Remote.cpp: определяет точку входа для приложения.
//
#include "stdafx.h"


#include "BeholdIRWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if(FindWindow(CBeholdIRWnd::ClassName, NULL) != NULL) return FALSE;

  HRESULT hres;

  // start application
  CBeholdIRWnd beholdIRWnd(hInstance);
  beholdIRWnd.Run();
  
  ::CoUninitialize();

	return 0;
}