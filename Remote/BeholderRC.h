#pragma once

typedef ULONG (__cdecl GETCARDCOUNT) (void);		// Return the total number of Beholder WDM capture devices
typedef LPSTR (__cdecl GETCARDNAME) (IN ULONG ulCardIdx);	// Return the device name by index ulCardIdx
typedef BOOL  (__cdecl OPENCARD) (IN ULONG ulCardIdx);	// Initialize device by index ulCardIdx
typedef ULONG (__cdecl GETREMOTECODE) (void);		// Return the key pressed on remote contril unit
typedef ULONG (__cdecl GETREMOTECODEEX) (void);		// Return the full 32-bit code of key pressed on remote contril unit
typedef BOOL  (__cdecl UNINIT) (void);			// Free all resources


class BeholderRC
{
private:
  GETREMOTECODEEX*	pGetRemoteCodeEx;
  GETREMOTECODE*	pGetRemoteCode;
  GETCARDCOUNT*		pGetCardCount;
  OPENCARD*			pOpenCard;
  UNINIT*			pUnInit;
  GETCARDNAME*		pGetCardName;
  HMODULE			hLib;
  bool				init;

public:
	BeholderRC(void)
	{
		init = false;
		hLib = LoadLibrary("BeholdRC.dll");
		if (hLib)
		{
			pGetCardCount    = (GETCARDCOUNT*)    GetProcAddress(hLib, "GetCardCount");
			pOpenCard        = (OPENCARD*)        GetProcAddress(hLib, "OpenCard");
			pGetRemoteCode   = (GETREMOTECODE*)   GetProcAddress(hLib, "GetRemoteCode");
			pGetRemoteCodeEx = (GETREMOTECODEEX*) GetProcAddress(hLib, "GetRemoteCodeEx");
			pUnInit          = (UNINIT*)          GetProcAddress(hLib, "UnInit");
			pGetCardName     = (GETCARDNAME*)     GetProcAddress(hLib, "GetCardName");
			if (!pGetCardCount || !pOpenCard || !pGetRemoteCode || !pUnInit || !pGetCardName)
			{	// GetRemoteCodeEx may be absent in library. Don't check for it.
				FreeLibrary(hLib);
				hLib = NULL;
			}
		}
	}

	virtual ~BeholderRC(void)
	{
		if (pUnInit)
		{
			pUnInit();
		}
		FreeLibrary(hLib);
		hLib = NULL;
	}

	int GetRemoteEx(void)
	{
		ULONG code;
		if (hLib && init)
		{
			if (pGetRemoteCodeEx)
				return pGetRemoteCodeEx();
			// The BeholdTV software has old BeholdRC.dll. Emulate extended function
			code = pGetRemoteCode();
			if (code < 255)
				// Combine full NEC-standard code
				return 0x866B0000 | (code<<8) | (~code&0xFF);
		}
		return 0;
	}

	int GetRemote(void)
	{
		int  code;
		if (hLib && init)
		{
			code = pGetRemoteCode();
			if (code < 255)
				return code;
		}
		return -1;
	}

	int GetCount(void)
	{
		return pGetCardCount();
	}

	bool SelectCard(int index)
	{
		int  i, cnt;
		if (index >= 0 && hLib)
		{
			cnt = pGetCardCount();
			if (cnt > index)
			{
				for (i = 0; i < cnt; ++i)
				{
					if (pOpenCard(i))
					{
						if (index == 0)
						{
							init = true;
							return init;
						}
						--index;
					}
				}
			}
		}
		init = false;
		return init;
	}

	char* GetName(int index)
	{
		return pGetCardName(index);
	}
};
