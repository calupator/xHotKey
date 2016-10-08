#pragma once

#include <string>
#include <map>
#include "Global.h"
#include "Beholder.h"

using namespace std;

namespace xHotKeyCore{

class XHKCORE_API HotKey
{
private:
	static HWND   m_hHwnd;	// статический член класса HotKey, определяющий Handle главного окна.
	string        *m_sName; // Название команды
	string        *m_sExe; // Файл запуска
	string        *m_sArgs; // Аргумент командной строки
	string        *m_sWorkDir; // Рабочая папка
	string        *m_sSound; // Звуковой файл
	Modifiers     m_iModifiers; // Модификаторы горячих клавиш
	WindowState   m_iWinState; // Статус окна свернуто, развернуто
	Command       m_iCmd; // Системная команда
	bool          m_bIsRegister; // Флаг регистрации HotKey
	int           m_iId; // Идентификатор HotKey
	int           m_iPriority; // Приорирет процесса
	bool          m_bNewInst; // Флаг, запускать новый или активировать имеющийся процесс

public:
	map<unsigned int, Beholder::ButtonRC>           *remote; // Список кнопок пультов (код кнопки,
	                                                         // имяПульта/имяКнопки/IDПульта)
	typedef pair <unsigned int, Beholder::ButtonRC> ButtonRC_Pair;

protected:
	int           m_iVKey; // Код клавиши

public:
	HotKey(void);
	/*virtual*/ ~HotKey(void);
	static void SetHandle(HWND handle);
	void SetName(string* name);
	string* GetName(void);
	void SetPath(string* name);
	string* GetPath(void);
	void SetArgument(string* args);
	string* GetArgument(void);
	void SetWorkingDir(string* workDir);
	string* GetWorkingDir(void);
	void SetSound(string* Sound);
	string* GetSound(void);
	void SetModifier(Modifiers modifier);
	Modifiers GetModifier(void);
	void SetKey(int key);
	int GetKey(void);
	void SetWindowState(WindowState windowState);
	WindowState GetWindowState(void);
	void SetPriority(int priority);
	int GetPriority(void);
	void SetCommand(Command command);
	Command GetCommand(void);
	bool GetIsRegister(void);
	int GetID(void);
	void SetNewInstance(bool newInstance);
	bool GetNewInstance(void);
	void Register(void);
	void Unregister(void);
	void Execute(void);
	void ShellCommand(void);
	string* ToString(void);
	string GetKeyName(void);
	bool AddButtonRC(ButtonRC_Pair buttonRC);
	bool RemButtonRC(map<unsigned int, Beholder::ButtonRC>::iterator buttonRC);
};

} // end namespace xHotKeyCore
