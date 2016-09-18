// BeholderRC.cpp : Implementation of CBeholderRC
#include "stdafx.h"
#include "BeholdService.h"
#include "BeholderRC.h"

/////////////////////////////////////////////////////////////////////////////
// CBeholderRC


STDMETHODIMP CBeholderRC::get_Count(ULONG *pVal)
{
	*pVal = m_pGetCardCount();

	return S_OK;
}

STDMETHODIMP CBeholderRC::get_IsInit(VARIANT_BOOL *pVal)
{
	*pVal = m_init;

	return S_OK;
}

STDMETHODIMP CBeholderRC::get_Name(ULONG index, BSTR *pVal)
{
	*pVal = A2BSTR(m_pGetCardName(index));

	return S_OK;
}

STDMETHODIMP CBeholderRC::GetRemote(ULONG *code)
{
	if (m_hLib && m_init)
	{
		*code = m_pGetRemoteCode();
		if (*code < 255)
		{
			*code;
			return S_OK;
		}
	}
	*code = -1;

	return S_OK;
}

STDMETHODIMP CBeholderRC::GetRemoteEx(ULONG *code)
{
	if (m_hLib && m_init)
	{
		if (m_pGetRemoteCodeEx)
		{
			*code = m_pGetRemoteCodeEx();
			return S_OK;
		}
			// The BeholdTV software has old BeholdRC.dll. Emulate extended function
		*code = m_pGetRemoteCode();
		if (*code < 255)
		{
			// Combine full NEC-standard code
			*code = 0x866B0000 | (*code<<8) | (~*code&0xFF);
			return S_OK;
		}
	}

	return S_OK;
}

STDMETHODIMP CBeholderRC::Run(BSTR *bcstr, VARIANT_BOOL *succes)
{
	char chars[255];	
	wcstombs((CHAR*)&chars, /*(OLECHAR*)*/*bcstr, sizeof(chars));
	WinExec(chars, SW_SHOW);
	*succes = true;

	return S_OK;
}

STDMETHODIMP CBeholderRC::SelectCard(ULONG index, VARIANT_BOOL *succes)
{
	ULONG  i, cnt;
	*succes = false;
	if (index >= 0 && m_hLib)
	{
		cnt = m_pGetCardCount();
		if (cnt > index)
		{
			for (i = 0; i < cnt; ++i)
			{
				if (m_pOpenCard(i))
				{
					if (index == 0)
					{
						m_init = true;
						*succes = m_init;
						return S_OK;
					}
					--index;
				}
			}
		}
	}
	m_init = false;
	*succes = m_init;

	return S_OK;
}

STDMETHODIMP CBeholderRC::UnInit(void)
{
	if (m_pUnInit)
	{
		m_pUnInit();
	}
	FreeLibrary(m_hLib);
	m_hLib = NULL;

	return S_OK;
}
