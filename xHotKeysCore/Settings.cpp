#include "StdAfx.h"
#include "Settings.h"
#include "xHotKeysCore.h"
#include "TinyXML\TinyXML.h"

using namespace TinyXML;

namespace xHotKeyCore{

string Settings::m_sPath/* = NULL*/;

Settings::Settings(string Path)
{
	m_sPath = Path;
}

Settings::~Settings(void)
{
}

bool Settings::LoadSettings(string Path)
{
	//Открываем XML-файл:
	TiXmlDocument *xml_file = new TiXmlDocument(Path.c_str());
	if(!xml_file->LoadFile())
		return false; 

	TiXmlElement *xml_HotKeys = 0;
	xml_HotKeys = xml_file->FirstChildElement("HotKeys");

	TiXmlElement *xml_HotKey = 0;
	xml_HotKey = xml_HotKeys->FirstChildElement("HotKey");

	HotKey *hotkey;
	while(xml_HotKey != NULL)
	{
		hotkey = new HotKey();
		hotkey->SetName(new string(xml_HotKey->Attribute("Name")));
		hotkey->SetKey(atoi(xml_HotKey->Attribute("Key")));
		hotkey->SetModifier((Modifiers)atoi(xml_HotKey->Attribute("Modifier")));
		hotkey->SetSound(new string(xml_HotKey->Attribute("Sound")));
		hotkey->SetCommand((Command)atoi(xml_HotKey->Attribute("Command")));
		if (hotkey->GetCommand() == 0)
		{
			hotkey->SetPath(new string(xml_HotKey->Attribute("Path")));
			hotkey->SetArgument(new string(xml_HotKey->Attribute("Argument")));
			hotkey->SetWorkingDir(new string(xml_HotKey->Attribute("WorkingDir")));
			hotkey->SetWindowState((WindowState)atoi(xml_HotKey->Attribute("WindowStyle")));
			hotkey->SetPriority(atoi(xml_HotKey->Attribute("Priority")));
			hotkey->SetNewInstance((atoi(xml_HotKey->Attribute("NewInstance")) ? 1 : 0));
		}
		TiXmlElement *xml_Beholder = 0;
		xml_Beholder = xml_HotKey->FirstChildElement("Beholder");
		TiXmlElement *xml_Remote = 0;
		xml_Remote = xml_Beholder->FirstChildElement("RemoteControl");
		while(xml_Remote != NULL)
		{
			Beholder::ButtonRC butt;
			butt.NameRC = string(xml_Remote->Attribute("NameRC"));
			butt.NameButton = string(xml_Remote->Attribute("NameButton"));
			butt.RemoteID = atol(xml_Remote->Attribute("RemoteID"));
			
			hotkey->AddButtonRC(HotKey::ButtonRC_Pair(atoi(xml_Remote->Attribute("Code")), butt));
			xml_Remote = xml_Remote->NextSiblingElement("RemoteControl");
		}
		xHotKeys::HotKey_Pair hkPair(hotkey->GetID(),hotkey);
		xHotKeys::g_hk->insert(hkPair);
		xml_HotKey = xml_HotKey->NextSiblingElement("HotKey");
	}
	return true;
}

} // end namespace xHotKeyCore
