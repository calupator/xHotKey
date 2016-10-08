// xHotKeyCore.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "xHotKeysCore.h"

#include <string>
#include <Windows.h>

std::string toString(const wchar_t* str)
{
	char ch[260];
	char DefChar = ' ';
    WideCharToMultiByte(CP_ACP, 0, str, -1, ch, 260, &DefChar, NULL);
    
    //A std:string  using the char* constructor.
	return std::string(ch);
};

// Пример экспортированной переменной
XHKCORE_API int nxHotKeyCore=0;

// Пример экспортированной функции.
XHKCORE_API int fnxHotKeyCore(void)
{
	return 42;
}

namespace xHotKeyCore{

	Beholder* xHotKeys::bh = 0;
	DWORD xHotKeys::m_dwLastTick = 0;
	DWORD xHotKeys::m_dwNextTick = 0;
	map<unsigned int, HotKey*> *xHotKeys::g_hk = new map<unsigned int, HotKey*>();

xHotKeys::~xHotKeys(void)
{
	if (bh)
		delete bh;
	bh = NULL;
	if (g_hk)
		delete g_hk;
	g_hk = NULL;
}

void xHotKeys::Init()
{
    Settings::LoadSettings("settings.xml");

	bh = new Beholder();
	bh->SelectCard(0);
	string name = toString(bh->GetName(0));
}

bool xHotKeys::Start(HWND hwnd)
{
	HotKey::SetHandle(hwnd);
	if (g_hk->empty() == false)
		RegisterHotKey();
	return true;
}

bool xHotKeys::HotKeys(MSG *msg)
{
	if(msg->message == WM_HOTKEY)
	{
        // ... проверяем идентификатор HotKey
		map<unsigned int, HotKey*>::const_iterator it = g_hk->find(msg->wParam);
		if (it != g_hk->end()) // Проверка на наличие HotKey с этим ID
		{
			it->second->Execute(); // Вызов команды с соответствующим ID
		}
		return true;
	}

	m_dwNextTick = GetTickCount();
	if ((m_dwNextTick - m_dwLastTick) > SKIP_TICKS)
	{
		unsigned int key = bh->GetRemoteEx();
		if (key != 0)
		{
			for (std::map<unsigned int, HotKey*>::const_iterator it2 = g_hk->begin(); it2 != g_hk->end(); it2++)
			{
				map<unsigned int, Beholder::ButtonRC>::const_iterator it3 = it2->second->remote->find(key);
				if (it3 != it2->second->remote->end())
				{
					// Check that the ID is our key and we are registerd
					if (it3->first == key)
					{
						// Fire the event and pass on the event if our handlers didn't handle it
						it2->second->Execute();
					}
				}
			}
		}
		m_dwLastTick = m_dwNextTick;
	}
	return false;
}

void xHotKeys::RegisterHotKey()
{
	for each (pair<unsigned int, HotKey*> it in *g_hk)
	{
		it.second->Register();
	}
}

} // end namespace xHotKeyCore
