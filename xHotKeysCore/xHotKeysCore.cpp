// xHotKeyCore.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "xHotKeysCore.h"

// ������ ���������������� ����������
XHKCORE_API int nxHotKeyCore=0;

// ������ ���������������� �������.
XHKCORE_API int fnxHotKeyCore(void)
{
	return 42;
}

// ����������� ��� ����������������� ������.
// ��. ����������� ������ � xHotKeyCore.h
xHotKeyCore::xHotKeyCore()
{
	return;
}
