#pragma once

#define XHKCORE_API __declspec(dllexport)

#ifdef _DEBUG
#import "..\Debug\BeholdService.tlb"
#elif NDEBUG
#import "..\Release\BeholdService.tlb"
#endif

using namespace BEHOLDSERVICELib;

namespace xHotKeyCore{

class XHKCORE_API Beholder
{
private:
	IBeholderRCPtr m_Tuner;
	unsigned long m_lIndex;

public:

	Beholder(void)
	{
		m_lIndex = 0;
		m_Tuner = IBeholderRCPtr(__uuidof(BeholderRC));
	}

	~Beholder(void)
	{
		//m_Tuner->UnInit();
	}

	bool IsInit(void);
	unsigned long GetCount(void);
	unsigned long GetSelectedCard(void);
	wchar_t* GetName(unsigned long i);
	bool GetSelectCard(unsigned long i);
	bool Run(wchar_t* path);
	unsigned long GetRemote(void);
	unsigned long GetRemoteEx(void);

	struct ButtonRC
	{
		wchar_t* NameRC;
        wchar_t* NameButton;
        unsigned long RemoteID;
	};
};
} // namespace xHotKeyCore
