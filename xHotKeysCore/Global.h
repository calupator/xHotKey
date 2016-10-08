#pragma once

#define XHKCORE_API __declspec(dllexport)

namespace xHotKeyCore{

	enum Modifiers :int
	{
		None = 0,
		Alt = 1,
		Control = 2,
		Shift = 4,
		Windows = 8
	};

	enum WindowState :int
	{
		///<summary>Normalizes the window.</summary>
		Normal = 0,
		///<summary>Minimizes the window.</summary>
		Minimize,
		///<summary>Maximizes the window.</summary>
		Maximize
	};

	enum Command :int // ��� ��������� �������
	{
		Nothing,
		VolUp,
		VolDown,
		/// <summary>LockWorkStation</summary>
		/// <remarks></remarks>
		LockWorkStation,
		/// <summary>������ ������������</summary>
		/// <remarks></remarks>
		RebootSoft,
		/// <summary>������� ������������</summary>
		/// <remarks></remarks>
		RebootHard,
		/// <summary>������ ����������</summary>
		/// <remarks></remarks>
		ShutdownSoft,
		/// <summary>������� ����������</summary>
		/// <remarks></remarks>
		ShutdownHard
	};

	/*enum EventType :int // ��� ���������� �������
	{
		/// <summary>������� ���� HotKey</summary>
		/// <remarks></remarks>
		HotKeys,
		/// <summary>������� ���� RemoteControl</summary>
		/// <remarks></remarks>
		RemoteControl

	};*/

} // end namespace xHotKeyCore
