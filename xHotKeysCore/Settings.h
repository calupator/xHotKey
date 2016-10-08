#pragma once

#include "Global.h"
#include <string>
using namespace std;

#include "HotKey.h"

namespace xHotKeyCore{

class XHKCORE_API Settings
{
public:
	Settings(string path);
	virtual ~Settings(void);
	static bool LoadSettings(string Path);


private:
	static string m_sPath;
public:
};

} // end namespace xHotKeyCore
