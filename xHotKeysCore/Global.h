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

	enum Command :int // ¬ид системной команды
	{
		Nothing,
		VolUp,
		VolDown,
		/// <summary>LockWorkStation</summary>
		/// <remarks></remarks>
		LockWorkStation,
		/// <summary>ћ€гка€ перезагрузка</summary>
		/// <remarks></remarks>
		RebootSoft,
		/// <summary>∆естка€ перезагрузка</summary>
		/// <remarks></remarks>
		RebootHard,
		/// <summary>ћ€гкое выключение</summary>
		/// <remarks></remarks>
		ShutdownSoft,
		/// <summary>∆есткое выключение</summary>
		/// <remarks></remarks>
		ShutdownHard
	};

	/*enum EventType :int // “ип вызвавшего событи€
	{
		/// <summary>—обытие типа HotKey</summary>
		/// <remarks></remarks>
		HotKeys,
		/// <summary>—обытие типа RemoteControl</summary>
		/// <remarks></remarks>
		RemoteControl

	};*/

} // end namespace xHotKeyCore
