// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа XHOTKEYCORE_EXPORTS,
// заданного в командной строке. Данный символ не должен быть определен ни в одном проекте,
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции XHOTKEYCORE_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef XHOTKEYCORE_EXPORTS
#define XHKCORE_API __declspec(dllexport)
#else
#define XHKCORE_API __declspec(dllimport)
#endif


// Этот класс экспортирован из xHotKeyCore.dll
class XHKCORE_API xHotKeyCore {
public:
	xHotKeyCore(void);
public:	
	ULONG count;
	// TODO. Добавьте здесь свои методы.
};

extern XHKCORE_API int nxHotKeyCore;

XHKCORE_API int fnxHotKeyCore(void);
