#include "StdAfx.h"
#include "HotKey.h"


namespace xHotKeyCore{

HWND HotKey::m_hHwnd = NULL;	// статический член класса HotKey,
								// определ€ющий Handle главного окна.

HotKey::HotKey(void) :
			//m_hHwnd(NULL),
			m_sName(new string("")),
			m_sExe(new string("")),
			m_sArgs(new string("")),
			m_sWorkDir(new string("")),
			m_sSound(new string("")),
			m_iModifiers(Modifiers::None),
			m_iVKey(0),
			m_iWinState(WindowState::Normal),
			//m_priority = ProcessPriorityClass.Normal(""),
			m_iCmd(Command::Nothing),
			m_bIsRegister(false),
			m_iId(0),
			m_bNewInst(false)
{
	remote = new map<unsigned int, Beholder::ButtonRC>();
}

HotKey::~HotKey(void)
{
	m_iId = GlobalDeleteAtom(m_iId);
	Unregister();
}

void HotKey::SetHandle(HWND handle)
{
	m_hHwnd = handle;
}

void HotKey::SetName(string *name)
{
	m_sName = name;
}

string* HotKey::GetName(void)
{
	return m_sName;
}

void HotKey::SetPath(string *path)
{
	m_sExe = path;
}

string* HotKey::GetPath(void)
{
	return m_sExe;
}

void HotKey::SetArgument(string *args)
{
	m_sArgs = args;
}

string* HotKey::GetArgument(void)
{
	return m_sArgs;
}

void HotKey::SetWorkingDir(string *workDir)
{
	m_sWorkDir = workDir;
}

string* HotKey::GetWorkingDir(void)
{
	return m_sWorkDir;
}

void HotKey::SetSound(string *sound)
{
	m_sSound = sound;
}

string* HotKey::GetSound(void)
{
	return m_sSound;
}

void HotKey::SetModifier(Modifiers modifier)
{
	m_iModifiers = modifier;
}

Modifiers HotKey::GetModifier(void)
{
	return m_iModifiers;
}

void HotKey::SetKey(int key)
{
	m_iVKey = key;
}

int HotKey::GetKey(void)
{
	return m_iVKey;
}

void HotKey::SetWindowState(WindowState windowState)
{
	m_iWinState = windowState;
}

WindowState HotKey::GetWindowState(void)
{
	return m_iWinState;
}

void HotKey::SetPriority(int priority)
{
	m_iPriority = priority;
}

int HotKey::GetPriority(void)
{
	return m_iPriority;
}

void HotKey::SetCommand(Command command)
{
	m_iCmd = command;
}

Command HotKey::GetCommand(void)
{
	return m_iCmd;
}

bool HotKey::GetIsRegister(void)
{
	return m_bIsRegister;
}

int HotKey::GetID(void)
{
	if (m_iId == 0)
	{
		char txt[256];
		txt[0]=0;
		sprintf(txt,"%X",GetTickCount());
		m_iId = GlobalAddAtom(txt);
	}
	return m_iId;
}

void HotKey::SetNewInstance(bool newInstance)
{
	m_bNewInst = newInstance;
}

bool HotKey::GetNewInstance(void)
{
	return m_bNewInst;
}

void HotKey::Register(void)
{
	m_bIsRegister = RegisterHotKey(HotKey::m_hHwnd, m_iId, m_iModifiers, m_iVKey);
}

void HotKey::Unregister(void)
{
	m_bIsRegister = UnregisterHotKey(HotKey::m_hHwnd, m_iId);
}

void HotKey::Execute(void)
{
}

void HotKey::ShellCommand(void)
{
}

string* HotKey::ToString(void)
{
		string* str;
		*str = "";
		if (m_iModifiers & Modifiers::Windows)
		{
			*str =  "Win + ";
		}
		if (m_iModifiers & Modifiers::Control)
		{
			*str += "Ctrl + ";
		}
		if (m_iModifiers & Modifiers::Alt)
		{
			*str += "Alt + ";
		}
		if (m_iModifiers & Modifiers::Shift)
		{
			*str += "Shift + ";
		}

		if (m_iVKey != 0)
		{
			*str += GetKeyName();
		}
		if (*str == "")
		{
			*str =  "None";
		}
		return str;
}

string HotKey::GetKeyName(void)
{
	// —писок названий клавиш
	static string* s_pszKeys[256] = {
		new string("Unused"),
		new string("Left mouse button"),
		new string("Right mouse button"),
		new string("Control-break"),
		new string("Middle mouse button"),
		new string("X1 mouse button"),
		new string("X2 mouse button"),
		new string("Undefined"),
		new string("Backspace"), 
		new string("Tab"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Clear"),
		new string("Enter"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Shift"),
		new string("Control"), 
		new string("Alt"),
		new string("Pause"),
		new string("Caps Lock"),
		new string("IME Kana mode"),
		new string("Unknown"),
		new string("IME Junja mode"),
		new string("IME final mode"),
		new string("IME Hanja mode"),
		new string("Unknown"),
		new string("Esc"),
		new string("IME convert"),
		new string("IME nonconvert"),
		new string("IME accept"),
		new string("IME mode change"),
		new string("Space"),
		new string("Page Up"),
		new string("Page Down"),
		new string("End"),
		new string("Home"),
		new string("Left Arrow"),
		new string("Up Arrow"),
		new string("Right Arrow"),
		new string("Down Arrow"),
		new string("Select"),
		new string("Print"),
		new string("Execute"),
		new string("Print Screen"),
		new string("Ins"),
		new string("Del"),
		new string("Help"),
		new string("0"),
		new string("1"),
		new string("2"),
		new string("3"),
		new string("4"),
		new string("5"),
		new string("6"),
		new string("7"),
		new string("8"),
		new string("9"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("A"),
		new string("B"),
		new string("C"),
		new string("D"),
		new string("E"),
		new string("F"),
		new string("G"),
		new string("H"),
		new string("I"),
		new string("J"),
		new string("K"),
		new string("L"),
		new string("M"),
		new string("N"),
		new string("O"),
		new string("P"),
		new string("Q"),
		new string("R"),
		new string("S"),
		new string("T"),
		new string("U"),
		new string("V"),
		new string("W"),
		new string("X"),
		new string("Y"),
		new string("Z"),
		new string("Left Win"),
		new string("Right Win"),
		new string("App"),
		new string("Unknown"),
		new string("Sleep"),
		new string("Num 0"),
		new string("Num 1"),
		new string("Num 2"),
		new string("Num 3"),
		new string("Num 4"),
		new string("Num 5"),
		new string("Num 6"),
		new string("Num 7"),
		new string("Num 8"),
		new string("Num 9"),
		new string("Mul"),
		new string("Add"),
		new string("Separator"),
		new string("Sub"),
		new string("Decimal"),
		new string("Div"),
		new string("F1"),
		new string("F2"),
		new string("F3"),
		new string("F4"),
		new string("F5"),
		new string("F6"),
		new string("F7"),
		new string("F8"),
		new string("F9"),
		new string("F10"),
		new string("F11"),
		new string("F12"),
		new string("F13"),
		new string("F14"),
		new string("F15"),
		new string("F16"),
		new string("F17"),
		new string("F18"),
		new string("F19"),
		new string("F20"),
		new string("F21"),
		new string("F22"),
		new string("F23"),
		new string("F24"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Num Lock"),
		new string("Scroll Lock"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Left Shift"),
		new string("Right Shift"),
		new string("Left Control"),
		new string("Right Control"),
		new string("Left Alt"),
		new string("Right Alt"),
		new string("Browser Back"),
		new string("Browser Forward"),
		new string("Browser Refresh"),
		new string("Browser Stop"),
		new string("Browser Search"),
		new string("Browser Favorites"),
		new string("Browser Home"),
		new string("Volume Mute"),
		new string("Volume Down"),
		new string("Volume Up"),
		new string("Next Track"),
		new string("Previous Track"),
		new string("Stop Media"),
		new string("Play/Pause Media"),
		new string("Start Mail"),
		new string("Select Media"),
		new string("Start App 1"),
		new string("Start App 2"),
		new string("Unknown"),
		new string("Unknown"),
		new string(";:"),
		new string("=+"),
		new string("),<"),
		new string("-_"),
		new string(".>"),
		new string("/?"),
		new string("`~"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("Unknown"),
		new string("[{"),
		new string("\\|"),
		new string("]}"),
		new string("'\""),
		new string("OEM"),
		new string("Unknown"),
		new string("OEM"),
		new string("<> or \\|"),
		new string("OEM"),
		new string("OEM"),
		new string("IME Process key"),
		new string("OEM"),
		new string("VK_PACKET"),
		new string("Unknown"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("OEM"),
		new string("Attn"),
		new string("CrSel"),
		new string("ExSel"),
		new string("Erase EOF"),
		new string("Play"),
		new string("Zoom"),
		new string("Unknown"),
		new string("PA1"),
		new string("Clear"),
		new string("Unknown")
	};

	if(m_iVKey < 256)
	{
		m_iVKey &= 0xff;
		return "";
	}
    return(*s_pszKeys[m_iVKey]);
}

bool HotKey::AddButtonRC(ButtonRC_Pair buttonRC)
{
	remote->insert(buttonRC);
	return true;
}

bool HotKey::RemButtonRC(map<unsigned int, Beholder::ButtonRC>::iterator buttonRC)
{
	remote->erase(buttonRC);
	return true;
}

} // end namespace xHotKeyCore
