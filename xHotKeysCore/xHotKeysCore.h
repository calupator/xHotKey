// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� XHOTKEYCORE_EXPORTS,
// ��������� � ��������� ������. ������ ������ �� ������ ���� ��������� �� � ����� �������,
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� XHOTKEYCORE_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifdef XHOTKEYCORE_EXPORTS
#define XHKCORE_API __declspec(dllexport)
#else
#define XHKCORE_API __declspec(dllimport)
#endif


// ���� ����� ������������� �� xHotKeyCore.dll
class XHKCORE_API xHotKeyCore {
public:
	xHotKeyCore(void);
public:	
	ULONG count;
	// TODO. �������� ����� ���� ������.
};

extern XHKCORE_API int nxHotKeyCore;

XHKCORE_API int fnxHotKeyCore(void);
