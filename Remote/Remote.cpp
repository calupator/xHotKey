// Remote.cpp: определяет точку входа для приложения.
//
#include "stdafx.h"
#include "BeholdIRWnd.h"
#include <shellapi.h>



int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  
  char namedPipe[2];
  LPWSTR *szArglist;
  int nArgs;
  int i;
  LPSTR lp = GetCommandLine(); // you can see same command line argument here.
  szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
  if (szArglist != NULL)
  {
	  //sprintf(&namedPipe[0], "%S", szArglist[1]);
	  //sprintf(&namedPipe[1], "%S", szArglist[2]);
  }
  else
	  return 0;

  if(FindWindow(CBeholdIRWnd::ClassName, NULL) != NULL) return FALSE;

  HRESULT hres;

  // start application
  CBeholdIRWnd beholdIRWnd(hInstance, szArglist);
  beholdIRWnd.Run();
  
  ::CoUninitialize();

	return 0;
}