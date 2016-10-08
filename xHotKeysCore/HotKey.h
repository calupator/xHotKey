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
	static HWND   m_hHwnd;	// ����������� ���� ������ HotKey, ������������ Handle �������� ����.
	string        *m_sName; // �������� �������
	string        *m_sExe; // ���� �������
	string        *m_sArgs; // �������� ��������� ������
	string        *m_sWorkDir; // ������� �����
	string        *m_sSound; // �������� ����
	Modifiers     m_iModifiers; // ������������ ������� ������
	WindowState   m_iWinState; // ������ ���� ��������, ����������
	Command       m_iCmd; // ��������� �������
	bool          m_bIsRegister; // ���� ����������� HotKey
	int           m_iId; // ������������� HotKey
	int           m_iPriority; // ��������� ��������
	bool          m_bNewInst; // ����, ��������� ����� ��� ������������ ��������� �������

public:
	map<unsigned int, Beholder::ButtonRC>           *remote; // ������ ������ ������� (��� ������,
	                                                         // ���������/���������/ID������)
	typedef pair <unsigned int, Beholder::ButtonRC> ButtonRC_Pair;

protected:
	int           m_iVKey; // ��� �������

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
