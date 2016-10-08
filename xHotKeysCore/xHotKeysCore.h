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



extern XHKCORE_API int nxHotKeyCore;

XHKCORE_API int fnxHotKeyCore(void);

#include "Beholder.h"
#include "HotKey.h"
#include "Settings.h"
#include <map>
using namespace std;

namespace xHotKeyCore{
// ���� ����� ������������� �� xHotKeyCore.dll
class XHKCORE_API xHotKeys
{

public:
	~xHotKeys(void);

	void Init(void);
	bool Start(HWND handle);
	bool HotKeys(MSG *message);

private:
	void RegisterHotKey();

public:
	typedef pair <unsigned int, HotKey*> HotKey_Pair;
	static Beholder                      *bh;
	static map<unsigned int, HotKey*>    *g_hk;

private:
	static const int                     TICKS_PER_SECOND = 3;
	static const int                     SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	static DWORD                         m_dwLastTick;
	static DWORD                         m_dwNextTick;
};

} // end namespace xHotKeyCore
