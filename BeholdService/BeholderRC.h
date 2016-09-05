// BeholderRC.h : Declaration of the CBeholderRC

#ifndef __BEHOLDERRC_H_
#define __BEHOLDERRC_H_

#include "resource.h"       // main symbols

typedef ULONG (__cdecl GETCARDCOUNT) (void);		// Return the total number of Beholder WDM capture devices
typedef LPSTR (__cdecl GETCARDNAME) (IN ULONG ulCardIdx);	// Return the device name by index ulCardIdx
typedef BOOL  (__cdecl OPENCARD) (IN ULONG ulCardIdx);	// Initialize device by index ulCardIdx
typedef ULONG (__cdecl GETREMOTECODE) (void);		// Return the key pressed on remote contril unit
typedef ULONG (__cdecl GETREMOTECODEEX) (void);		// Return the full 32-bit code of key pressed on remote contril unit
typedef BOOL  (__cdecl UNINIT) (void);			// Free all resources


/////////////////////////////////////////////////////////////////////////////
// CBeholderRC
class ATL_NO_VTABLE CBeholderRC : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBeholderRC, &CLSID_BeholderRC>,
	public IDispatchImpl<IBeholderRC, &IID_IBeholderRC, &LIBID_BEHOLDSERVICELib>
{
private:
	GETREMOTECODEEX* pGetRemoteCodeEx;
	GETREMOTECODE*   pGetRemoteCode;
	GETCARDCOUNT*    pGetCardCount;
	OPENCARD*        pOpenCard;
	UNINIT*          pUnInit;
	GETCARDNAME*     pGetCardName;
	HMODULE          hLib;
	bool             init;

public:
	CBeholderRC()
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

	virtual ~CBeholderRC(void)
	{
		if (pUnInit)
		{
			pUnInit();
		}
		FreeLibrary(hLib);
		hLib = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BEHOLDERRC)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBeholderRC)
	COM_INTERFACE_ENTRY(IBeholderRC)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IBeholderRC
public:
	STDMETHOD(GetRemoteEx)(/*[out, retval]*/ ULONG* code);
	STDMETHOD(GetRemote)(/*[out, retval]*/ ULONG* code);
	STDMETHOD(SelectCard)(/*[in]*/ ULONG* index, /*[out, retval]*/ VARIANT_BOOL* succes);
	STDMETHOD(Run)(/*[in]*/ BSTR* bcstr, /*[out, retval]*/ VARIANT_BOOL *succes);
	STDMETHOD(get_Count)(/*[out, retval]*/ ULONG* count);
	STDMETHOD(get_Name)(/*[in]*/ ULONG index, /*[out, retval]*/ BSTR *pVal);
};

#endif //__BEHOLDERRC_H_
