// BeholderRC.cpp : Implementation of CBeholderRC
#include "stdafx.h"
#include "BeholdService.h"
#include "BeholderRC.h"

/////////////////////////////////////////////////////////////////////////////
// CBeholderRC


STDMETHODIMP CBeholderRC::get_Count(ULONG *pVal)
{
	*pVal = pGetCardCount();

	return S_OK;
}

STDMETHODIMP CBeholderRC::get_IsInit(VARIANT_BOOL *pVal)
{
	*pVal = init;

	return S_OK;
}

STDMETHODIMP CBeholderRC::get_Name(ULONG index, BSTR *pVal)
{
	*pVal = A2BSTR(pGetCardName(index));

	return S_OK;
}

STDMETHODIMP CBeholderRC::GetRemote(ULONG *code)
{
	if (hLib && init)
	{
		*code = pGetRemoteCode();
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
	if (hLib && init)
	{
		if (pGetRemoteCodeEx)
		{
			*code = pGetRemoteCodeEx();
			return S_OK;
		}
			// The BeholdTV software has old BeholdRC.dll. Emulate extended function
		*code = pGetRemoteCode();
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
						*succes = init;
						return S_OK;
					}
					--index;
				}
			}
		}
	}
	init = false;
	*succes = init;

	return S_OK;
}
