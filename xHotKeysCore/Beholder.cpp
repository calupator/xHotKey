#include "stdafx.h"
#include "Beholder.h"

namespace xHotKeyCore{

bool Beholder::IsInit(void)
{
	return m_Tuner->IsInit;
}

unsigned long Beholder::GetCount(void)
{
	return m_Tuner->Count;
}

unsigned long Beholder::GetSelectedCard(void)
{
	return m_lIndex;
}

wchar_t* Beholder::GetName(unsigned long i)
{
	return m_Tuner->Name[i];
}

bool Beholder::SelectCard(unsigned long i)
{
	if (m_Tuner->SelectCard(i))
	{
		m_lIndex = i;
		return true;
	}
	else
	{
		m_lIndex = -1;
		return false;
	}
}

bool Beholder::Run(wchar_t* path)
{
	return m_Tuner->Run(&path);
}

unsigned long Beholder::GetRemote(void)
{
	return m_Tuner->GetRemote();
}

unsigned long Beholder::GetRemoteEx(void)
{
	return m_Tuner->GetRemoteEx();
}

} // end namespace xHotKeyCore