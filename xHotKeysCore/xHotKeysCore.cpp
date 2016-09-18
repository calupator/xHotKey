// xHotKeyCore.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "xHotKeysCore.h"

// Пример экспортированной переменной
XHKCORE_API int nxHotKeyCore=0;

// Пример экспортированной функции.
XHKCORE_API int fnxHotKeyCore(void)
{
	return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в xHotKeyCore.h
xHotKeyCore::xHotKeyCore()
{
	return;
}
