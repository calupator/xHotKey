#include "StdAfx.h"
#include "BeholdIRWnd.h"
#include "BeholdProc.h"
#include "resource.h"
#include "Remote.h"

char CBeholdIRWnd::ClassName[] = "BeholderRC";
CBeholdIRWnd*	CBeholdIRWnd::s_beholdIRWnd = NULL;

CBeholdIRWnd::CBeholdIRWnd(HINSTANCE hInst, LPWSTR *namedPipe)
    : m_instance(hInst),
      m_window(NULL)
{
	  Pipe = namedPipe;
  if (s_beholdIRWnd != NULL)
  {
    throw ("ErrDupInst");
  }

  s_beholdIRWnd = this;
}

CBeholdIRWnd::~CBeholdIRWnd(void)
{
  if (s_beholdIRWnd == this)
    s_beholdIRWnd = NULL;
}

void CBeholdIRWnd::Run()
{
  if (!Initialize())
  {
    ::MessageBox(NULL, "ErrInitFail", ClassName, MB_OK | MB_ICONSTOP);
    return;
  }

  try
  {   
    // Main message loop:
    BOOL bRet;
    MSG  msg;
    while ((bRet = ::GetMessage(&msg, NULL, 0, 0)) != 0)
    {
      if (bRet == -1)
      {
        break;
      }
      else
      {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }
    }
  }
  catch(...)
  {
    ::MessageBox(NULL, "ErrUnknown", ClassName, MB_OK | MB_ICONSTOP);
  }

  Terminate();
}

bool CBeholdIRWnd::Initialize()
{
	MyRegisterClass();
	if (!InitInstance())
		return false;

	beholdProcess = new BeholdProc(m_window, Pipe);
	//Sleep(1000);
	beholdProcess->Start();
  
  return true;
}

void CBeholdIRWnd::Terminate()
{
	delete beholdProcess;
}

ATOM CBeholdIRWnd::MyRegisterClass()
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc		= CBeholdIRWnd::WndProc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= m_instance;
  wcex.hIcon			= ::LoadIcon(m_instance, MAKEINTRESOURCE(IDI_BEHOLDIR));
  wcex.hCursor			= ::LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName		= NULL;
  wcex.lpszClassName	= ClassName;
  wcex.hIconSm			= ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return ::RegisterClassEx(&wcex);
}

bool CBeholdIRWnd::InitInstance()
{
  m_window = ::CreateWindow(ClassName, ClassName, WS_OVERLAPPEDWINDOW,
              CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, m_instance, NULL);

  if (!m_window)
  {
      return false;
  }

  ::ShowWindow(m_window, SW_SHOW);
  //::ShowWindow(m_window, SW_HIDE);

  HICON hIcon = ::LoadIcon(m_instance, MAKEINTRESOURCE(IDI_SMALL));

  return true;
}

LRESULT CALLBACK CBeholdIRWnd::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
		break;

	case WM_DESTROY:
        ::PostQuitMessage(0);
		break;

	default:
        return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
