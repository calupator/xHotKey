#include <windows.h>
#pragma unmanaged

#define NUMHOOKS 7

// ���������� ����������

typedef struct _MYHOOKDATA
{
	int nType;
	HOOKPROC hkprc;
	HHOOK hhook;
} MYHOOKDATA;

MYHOOKDATA myhookdata[NUMHOOKS];

LRESULT WINAPI MainWndProc(HWND hwndMain, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	static BOOL afHooks[NUMHOOKS];
	int index;
	static HMENU hmenu;

	switch (uMsg)
	{
		case WM_CREATE:

			// ���������� ����������� ����.

			hmenu = GetMenu(hwndMain);

			// ������������� ��������� � ������� hook-�����. ��������������
			// ��������� ���� ���������� �� 0 �� 6 � ������������
			// �����. ��� ����� ���� ������������ ��� ������������� �������
			// ��������� ��� ����� ��� � ���� ��������� ��������� WM_COMMAND.

			myhookdata[IDM_CALLWNDPROC].nType = WH_CALLWNDPROC;
			myhookdata[IDM_CALLWNDPROC].hkprc = CallWndProc;
			myhookdata[IDM_CBT].nType = WH_CBT;
			myhookdata[IDM_CBT].hkprc = CBTProc;
			myhookdata[IDM_DEBUG].nType = WH_DEBUG;
			myhookdata[IDM_DEBUG].hkprc = DebugProc;
			myhookdata[IDM_GETMESSAGE].nType = WH_GETMESSAGE;
			myhookdata[IDM_GETMESSAGE].hkprc = GetMsgProc;
			myhookdata[IDM_KEYBOARD].nType = WH_KEYBOARD;
			myhookdata[IDM_KEYBOARD].hkprc = KeyboardProc;
			myhookdata[IDM_MOUSE].nType = WH_MOUSE;
			myhookdata[IDM_MOUSE].hkprc = MouseProc;
			myhookdata[IDM_MSGFILTER].nType = WH_MSGFILTER;
			myhookdata[IDM_MSGFILTER].hkprc = MessageProc;

			// �������������� ��� ������ � ������� � ����(FALSE)

			memset(afHooks, FALSE, sizeof(afHooks));

			return 0;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				 // ������������ ������ ������� hook-����� �� ����.

				case IDM_CALLWNDPROC:
				case IDM_CBT:
				case IDM_DEBUG:
				case IDM_GETMESSAGE:
				case IDM_KEYBOARD:
				case IDM_MOUSE:
				case IDM_MSGFILTER:

					// ���������� ������������� �������� ���� ��� ������
					// ������ ������� �������� � ������� hook-�����.

					index = LOWORD(wParam);

				   // ���� ��������� ��� ������������ ��������� �� ����������
					// ��� ��, ���������� ���
					// � �������� �������� ��������� ����� ����.

					if (!afHooks[index])
					{
						myhookdata[index].hhook = SetWindowsHookEx(
							myhookdata[index].nType,
							myhookdata[index].hkprc,
							(HINSTANCE) NULL, GetCurrentThreadId());
						CheckMenuItem(hmenu, index,
							MF_BYCOMMAND | MF_CHECKED);
						afHooks[index] = TRUE;
					}

					// ���� ��������� ��� ������������ ���������
					// ��� ����������, ������� ��� � ������� ���� ������� ��
					// ���������� �������� ����.

					else
					{
						UnhookWindowsHookEx(myhookdata[index].hhook);
						CheckMenuItem(hmenu, index,
							MF_BYCOMMAND | MF_UNCHECKED);
						afHooks[index] = FALSE;
					}

				default:
					return (DefWindowProc(hwndMain, uMsg, wParam,
						lParam));
			}
			break;

			//
			// ��������� ������ ���������.
			//

		default:
			return DefWindowProc(hwndMain, uMsg, wParam, lParam);
	}
	return NULL;
}

/****************************************************************
 ������������ ��������� WH_CALLWNDPROC

 ****************************************************************/

LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szCWPBuf[256];
	CHAR szMsg[16];
	HDC hdc;
	static int c = 0;
	int cch;

	if (nCode < 0)								  // �� ������ ��������� ���������
		return CallNextHookEx(myhookdata[CALLWNDPROC].hhook,
		  nCode, wParam, lParam);

	// �������� ������������ ���������� �������, ������� ���������������
	// ��������� ��������� � ������ � �������� �� � �����.

	LookUpTheMessage((PMSG) lParam, szMsg);

	hdc = GetDC(hwndMain);

	switch (nCode)
	{
		case HC_ACTION:
			cch = wsprintf(szCWPBuf,
			   "CALLWNDPROC - tsk: %ld, msg: %s, %d times   ",
				wParam, szMsg, c++);
			TextOut(hdc, 2, 15, szCWPBuf, cch);
			break;

		default:
			break;
	}

	ReleaseDC(hwndMain, hdc);

	return CallNextHookEx(myhookdata[CALLWNDPROC].hhook,
		 nCode, wParam, lParam);
}

/****************************************************************
 ������������ ��������� WH_GETMESSAGE

 ****************************************************************/

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szMSGBuf[256];
	CHAR szRem[16];
	CHAR szMsg[16];
	HDC hdc;
	static int c = 0;
	int cch;

	if (nCode < 0) // ��������� �� ������������

		return CallNextHookEx(myhookdata[GETMESSAGE].hhook,
		nCode, wParam, lParam);

	switch (nCode)
	{
		case HC_ACTION:
			switch (wParam)
			{
				case PM_REMOVE:
					lstrcpy(szRem, "PM_REMOVE");
					break;

				case PM_NOREMOVE:
					lstrcpy(szRem, "PM_NOREMOVE");
					break;

				default:
					lstrcpy(szRem, "Unknown");
					break;
			}

			// ����� ������������ ���������� �������,
			// ������� ��������������� ��������� ��������� � ������
			// � �������� �� � �����.

			LookUpTheMessage((PMSG) lParam, szMsg);

			hdc = GetDC(hwndMain);
			cch = wsprintf(szMSGBuf,
				"GETMESSAGE - wParam: %s, msg: %s, %d times   ",
				szRem, szMsg, c++);
			TextOut(hdc, 2, 35, szMSGBuf, cch);
			break;

		default:
			break;
	}

	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[GETMESSAGE].hhook,
		 nCode, wParam, lParam);
}

/****************************************************************
 ������������ ��������� WH_DEBUG

 ****************************************************************/

LRESULT CALLBACK DebugProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	HDC hdc;

	static int c = 0;
	int cch;

	if (nCode < 0)  // �� ������������� ���������
		return CallNextHookEx(myhookdata[DEBUG].hhook, nCode,
											   wParam, lParam);

	hdc = GetDC(hwndMain);

	switch (nCode)
	{
		case HC_ACTION:
			cch = wsprintf(szBuf,
				"DEBUG - nCode: %d, tsk: %ld, %d times   ",
				nCode,wParam, c++);
			TextOut(hdc, 2, 55, szBuf, cch);
			break;

		default:
			break;
	}

	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[DEBUG].hhook, nCode,
		 wParam, lParam);

}

/****************************************************************
 ������������ ��������� WH_CBT

 ****************************************************************/

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	CHAR szCode[128];
	HDC hdc;

	static int c = 0;
	int cch;

	if (nCode < 0)  // �� ������������ ���������
		return CallNextHookEx(myhookdata[CBT].hhook, nCode, wParam, lParam);

	hdc = GetDC(hwndMain);

	switch (nCode)
	{
		case HCBT_ACTIVATE:
			lstrcpy(szCode, "HCBT_ACTIVATE");
			break;

		case HCBT_CLICKSKIPPED:
			lstrcpy(szCode, "HCBT_CLICKSKIPPED");
			break;

		case HCBT_CREATEWND:
			lstrcpy(szCode, "HCBT_CREATEWND");
			break;

		case HCBT_DESTROYWND:
			lstrcpy(szCode, "HCBT_DESTROYWND");
			break;

		case HCBT_KEYSKIPPED:
			lstrcpy(szCode, "HCBT_KEYSKIPPED");
			break;

		case HCBT_MINMAX:
			lstrcpy(szCode, "HCBT_MINMAX");
			break;

		case HCBT_MOVESIZE:
			lstrcpy(szCode, "HCBT_MOVESIZE");
			break;

		case HCBT_QS:
			lstrcpy(szCode, "HCBT_QS");
			break;

		case HCBT_SETFOCUS:
			lstrcpy(szCode, "HCBT_SETFOCUS");
			break;

		case HCBT_SYSCOMMAND:
			lstrcpy(szCode, "HCBT_SYSCOMMAND");
			break;

		default:
			lstrcpy(szCode, "Unknown");
			break;
	}

	cch = wsprintf(szBuf, "CBT - nCode: %s, tsk: %ld, %d
times   ", szCode, wParam, c++);

	TextOut(hdc, 2, 75, szBuf, cch);
	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[CBT].hhook, nCode,
 wParam, lParam);

}

/****************************************************************
 ������������ ��������� WH_MOUSE

 ****************************************************************/

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	CHAR szMsg[16];
	HDC hdc;
	static int c = 0;
	int cch;

	if (nCode < 0)  // �� ������������ ���������
		return CallNextHookEx(myhookdata[MOUSE].hhook, nCode,
											  wParam, lParam);

			// ����� ������������ ���������� �������,
			// ������� ��������������� ��������� ��������� � ������
			// � �������� �� � �����.

	LookUpTheMessage((PMSG) lParam, szMsg);

	hdc = GetDC(hwndMain);
	cch = wsprintf(szBuf,
	  "MOUSE - nCode: %d, msg: %s, x: %d, y: %d, %d times   ", nCode, szMsg, LOWORD(lParam), HIWORD(lParam), c++);

	TextOut(hdc, 2, 95, szBuf, cch);
	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[MOUSE].hhook, nCode,
		 wParam, lParam);

}

/****************************************************************
 ������������ ��������� WH_KEYBOARD

 ****************************************************************/

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	HDC hdc;
	static int c = 0;
	int cch;

	if (nCode < 0)  // ��������� �� ������������
		return CallNextHookEx(myhookdata[KEYBOARD].hhook,
			   nCode, wParam, lParam);

	hdc = GetDC(hwndMain);
	cch = wsprintf(szBuf, "KEYBOARD - nCode: %d, vk: %d, %d times ", nCode, wParam, c++);

	TextOut(hdc, 2, 115, szBuf, cch);
	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[KEYBOARD].hhook, nCode, wParam, lParam);

}

/****************************************************************
 ������������ ��������� WH_MSGFILTER

 ****************************************************************/

LRESULT CALLBACK MessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	CHAR szMsg[16];
	CHAR szCode[32];
	HDC hdc;
	static int c = 0;
	int cch;

	if (nCode < 0)  // ��������� �� ������������
		return CallNextHookEx(myhookdata[MSGFILTER].hhook, nCode,
				wParam, lParam);

	switch (nCode)
	{
		case MSGF_DIALOGBOX:
			lstrcpy(szCode, "MSGF_DIALOGBOX");
			break;

		case MSGF_MENU:
			lstrcpy(szCode, "MSGF_MENU");
			break;

		case MSGF_SCROLLBAR:
			lstrcpy(szCode, "MSGF_SCROLLBAR");
			break;

		case MSGF_NEXTWINDOW:
			lstrcpy(szCode, "MSGF_NEXTWINDOW");
			break;

		default:
			wsprintf(szCode, "Unknown: %d", nCode);
			break;
	}

			 // ����� ������������ ���������� �������,
			// ������� ��������������� ��������� ��������� � ������
			// � �������� �� � �����.

	LookUpTheMessage((PMSG) lParam, szMsg);

	hdc = GetDC(hwndMain);
	cch = wsprintf(szBuf,
		"MSGFILTER  nCode: %s, msg: %s, %d times	",
		szCode, szMsg, c++);
	TextOut(hdc, 2, 135, szBuf, cch);
	ReleaseDC(hwndMain, hdc);
	return CallNextHookEx(myhookdata[MSGFILTER].hhook,
	nCode, wParam, lParam);
}
#pragma managed