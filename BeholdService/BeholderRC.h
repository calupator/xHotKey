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
	GETREMOTECODEEX* m_pGetRemoteCodeEx;
	GETREMOTECODE*   m_pGetRemoteCode;
	GETCARDCOUNT*    m_pGetCardCount;
	OPENCARD*        m_pOpenCard;
	UNINIT*          m_pUnInit;
	GETCARDNAME*     m_pGetCardName;
	HMODULE          m_hLib;
	bool             m_init;

public:
	CBeholderRC()
	{
		m_init = false;
		m_hLib = LoadLibrary("BeholdRC.dll");
		if (m_hLib)
		{
			m_pGetCardCount    = (GETCARDCOUNT*)    GetProcAddress(m_hLib, "GetCardCount");
			m_pOpenCard        = (OPENCARD*)        GetProcAddress(m_hLib, "OpenCard");
			m_pGetRemoteCode   = (GETREMOTECODE*)   GetProcAddress(m_hLib, "GetRemoteCode");
			m_pGetRemoteCodeEx = (GETREMOTECODEEX*) GetProcAddress(m_hLib, "GetRemoteCodeEx");
			m_pUnInit          = (UNINIT*)          GetProcAddress(m_hLib, "UnInit");
			m_pGetCardName     = (GETCARDNAME*)     GetProcAddress(m_hLib, "GetCardName");
			if (!m_pGetCardCount || !m_pOpenCard || !m_pGetRemoteCode || !m_pUnInit || !m_pGetCardName)
			{	// GetRemoteCodeEx may be absent in library. Don't check for it.
				FreeLibrary(m_hLib);
				m_hLib = NULL;
			}
		}
	}

	virtual ~CBeholderRC(void)
	{
		UnInit();
	}



DECLARE_REGISTRY_RESOURCEID(IDR_BEHOLDERRC)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBeholderRC)
	COM_INTERFACE_ENTRY(IBeholderRC)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IBeholderRC
public:
	STDMETHOD(SelectCard)(/*[in]*/ ULONG index, /*[out, retval]*/ VARIANT_BOOL* succes);
	STDMETHOD(Run)(/*[in]*/ BSTR* bcstr, /*[out, retval]*/ VARIANT_BOOL *succes);
	STDMETHOD(GetRemoteEx)(/*[out, retval]*/ ULONG* code);
	STDMETHOD(GetRemote)(/*[out, retval]*/ ULONG* code);
	STDMETHOD(get_Name)(/*[in]*/ ULONG index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_IsInit)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ ULONG *pVal);
	STDMETHOD(UnInit)(void);
};

#endif //__BEHOLDERRC_H_
