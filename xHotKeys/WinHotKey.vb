Imports System.Runtime.InteropServices
Imports System.Reflection
Imports System.ComponentModel

Public NotInheritable Class WinHotKey
    Inherits TextBox

    <DllImport("user32", SetLastError:=True)> _
    Public Overloads Shared Function SetWindowsHookEx(ByVal idHook As Integer, ByVal lpfn As WKCallBack, ByVal hMod As IntPtr, ByVal dwThreadId As Integer) As IntPtr
    End Function

    <DllImport("user32", SetLastError:=True)> _
    Public Shared Function UnhookWindowsHookEx(ByVal hook As IntPtr) As <MarshalAs(UnmanagedType.Bool)> Boolean
    End Function

    <DllImport("user32")> _
    Public Overloads Shared Function CallNextHookEx(ByVal hhk As IntPtr, ByVal nCode As Integer, ByVal wParam As IntPtr, ByRef lParam As KeyboardData) As IntPtr
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function SendMessage(ByVal hWnd As IntPtr, ByVal Msg As UInteger, ByVal wParam As IntPtr, ByVal lParam As IntPtr) As IntPtr
    End Function

    Dim vkName As New List(Of String)

    <MarshalAs(UnmanagedType.FunctionPtr)> _
    Private _keyboardProc As New WKCallBack(AddressOf KeyboardProc)
    'Holds the keyboard hook handle. Needed 
    'for RemoveHook and KeyboardProc methods.
    Private _hKeyboardHook As IntPtr
    Delegate Function WKCallBack(ByVal nCode As Integer, ByVal wParam As IntPtr, ByRef lParam As KeyboardData) As IntPtr

    Dim dwWhcData As WhcData

    Structure WhcData
        Dim vkCode As Integer
        Dim fModSet As Integer
        Dim fModRel As Integer
        Dim fIsPressed As Boolean

        Public Function IsNull() As Boolean
            If ((fIsPressed = 0) And (fModRel = 0) And (fModSet = 0) And (vkCode = 0)) Then
                Return True
            End If
            Return False
        End Function
    End Structure

    Private Sub InitvkName()
        With vkName
            .Add("Unused")
            .Add("@LMB")
            .Add("@RMB")
            .Add("Control-break")
            .Add("@MMB")
            .Add("@X1MB")
            .Add("@X2MB")
            .Add("Undefined")
            .Add("Backspace")
            .Add("Tab")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Clear")
            .Add("Enter")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Shift")
            .Add("Control")
            .Add("Alt")
            .Add("Pause")
            .Add("CapsLock")
            .Add("IME Kana mode")
            .Add("Unknown")
            .Add("IME Junja mode")
            .Add("IME final mode")
            .Add("IME Hanja mode")
            .Add("Unknown")
            .Add("Esc")
            .Add("IME convert")
            .Add("IME nonconvert")
            .Add("IME accept")
            .Add("IME mode change")
            .Add("Space")
            .Add("PageUp")
            .Add("PageDown")
            .Add("End")
            .Add("Home")
            .Add("Left")
            .Add("Up")
            .Add("Right")
            .Add("Down")
            .Add("Select")
            .Add("Print")
            .Add("Execute")
            .Add("PrintScreen")
            .Add("Ins")
            .Add("Delete")
            .Add("Help")
            .Add("0")
            .Add("1")
            .Add("2")
            .Add("3")
            .Add("4")
            .Add("5")
            .Add("6")
            .Add("7")
            .Add("8")
            .Add("9")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("A")
            .Add("B")
            .Add("C")
            .Add("D")
            .Add("E")
            .Add("F")
            .Add("G")
            .Add("H")
            .Add("I")
            .Add("J")
            .Add("K")
            .Add("L")
            .Add("M")
            .Add("N")
            .Add("O")
            .Add("P")
            .Add("Q")
            .Add("R")
            .Add("S")
            .Add("T")
            .Add("U")
            .Add("V")
            .Add("W")
            .Add("X")
            .Add("Y")
            .Add("Z")
            .Add("LWin")
            .Add("RWin")
            .Add("Apps")
            .Add("Unknown")
            .Add("Sleep")
            .Add("Num 0")
            .Add("Num 1")
            .Add("Num 2")
            .Add("Num 3")
            .Add("Num 4")
            .Add("Num 5")
            .Add("Num 6")
            .Add("Num 7")
            .Add("Num 8")
            .Add("Num 9")
            .Add("Num *")
            .Add("Num +")
            .Add("Separator")
            .Add("Num -")
            .Add("Num Del")
            .Add("Num /")
            .Add("F1")
            .Add("F2")
            .Add("F3")
            .Add("F4")
            .Add("F5")
            .Add("F6")
            .Add("F7")
            .Add("F8")
            .Add("F9")
            .Add("F10")
            .Add("F11")
            .Add("F12")
            .Add("F13")
            .Add("F14")
            .Add("F15")
            .Add("F16")
            .Add("F17")
            .Add("F18")
            .Add("F19")
            .Add("F20")
            .Add("F21")
            .Add("F22")
            .Add("F23")
            .Add("F24")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Num Lock")
            .Add("Scroll Lock")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("LShift")
            .Add("RShift")
            .Add("LCtrl")
            .Add("RCtrl")
            .Add("LAlt")
            .Add("RAlt")
            .Add("@Back")
            .Add("@Forw.")
            .Add("@Refresh")
            .Add("@Stop")
            .Add("@Find")
            .Add("@Fav.")
            .Add("@Browser")
            .Add("VolumeMute")
            .Add("VolumeDown")
            .Add("VolumeUp")
            .Add("@Next")
            .Add("@Prev.")
            .Add("@Stop")
            .Add("@Play")
            .Add("@EMail")
            .Add("@Media")
            .Add("@App1")
            .Add("@App2")
            .Add("Unknown")
            .Add("Unknown")
            .Add(":")
            .Add("=")
            .Add("<")
            .Add("-")
            .Add(">")
            .Add("/?")
            .Add("~")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("Unknown")
            .Add("[")
            .Add("\|")
            .Add("]")
            .Add("'""")
            .Add("OEM")
            .Add("Unknown")
            .Add("OEM")
            .Add("<> or \\|")
            .Add("OEM")
            .Add("OEM")
            .Add("IME Process key")
            .Add("OEM")
            .Add("VK_PACKET")
            .Add("Unknown")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("OEM")
            .Add("Attn")
            .Add("CrSel")
            .Add("ExSel")
            .Add("Erase EOF")
            .Add("Play")
            .Add("Zoom")
            .Add("Unknown")
            .Add("PA1")
            .Add("Clear")
            .Add("Unknown")
        End With
    End Sub

    Private Function KeyboardProc(ByVal nCode As Integer, ByVal wParam As IntPtr, ByRef lParam As KeyboardData) As IntPtr
        If (nCode = HC_ACTION) Then
            Dim keyCode As Keys = CType(lParam.vkCode, Keys)
            Select Case CInt(wParam)
                Case WM_KEYDOWN, WM_SYSKEYDOWN, WM_KEYUP, WM_SYSKEYUP
                    'SendMessage(Handle, WM_KEY, lParam.vkCode, (CInt(wParam) & 1))
                    Dim fMod As UInteger = 0
                    Dim fRedraw As Integer = 1
                    Select Case keyCode
                        Case Keys.LWin, Keys.RWin
                            fMod = Modifier.MOD_WIN
                        Case Keys.Control, Keys.LControlKey, Keys.RControlKey
                            fMod = Modifier.MOD_CONTROL
                        Case Keys.Menu, Keys.LMenu, Keys.RMenu
                            fMod = Modifier.MOD_ALT
                        Case Keys.Shift, Keys.LShiftKey, Keys.RShiftKey
                            fMod = Modifier.MOD_SHIFT
                    End Select

                    If fMod <> 0 Then ' modifier
                        If Not (CInt(wParam) And 1) Then ' press
                            If dwWhcData.fIsPressed = 0 AndAlso dwWhcData.vkCode <> 0 Then
                                dwWhcData.fModRel = 0
                                dwWhcData.fModSet = 0
                                dwWhcData.vkCode = 0
                            End If
                            dwWhcData.fModRel = dwWhcData.fModRel And Not (fMod <> 0)
                        ElseIf dwWhcData.fModSet And fMod <> 0 Then ' release
                            dwWhcData.fModRel = dwWhcData.fModRel Or fMod
                        End If
                        If dwWhcData.fIsPressed <> 0 OrElse dwWhcData.vkCode = 0 Then
                            If Not (CInt(wParam) And 1) Then ' press
                                If (dwWhcData.fModSet And fMod) = 0 Then
                                    dwWhcData.fModSet = dwWhcData.fModSet Or fMod
                                Else
                                    fRedraw = False
                                End If
                            Else
                                dwWhcData.fModSet = dwWhcData.fModSet And Not fMod
                            End If
                        End If
                    Else
                        If wParam = Keys.Delete AndAlso dwWhcData.fModSet = (Modifier.MOD_CONTROL Or Modifier.MOD_ALT) Then
                            dwWhcData.fModRel = 0
                            dwWhcData.fModSet = 0
                            dwWhcData.vkCode = 0
                            dwWhcData.fIsPressed = 0
                        ElseIf keyCode = dwWhcData.vkCode AndAlso (CInt(wParam) And 1) Then
                            dwWhcData.fIsPressed = 0
                            fRedraw = 0
                        Else
                            If (Not dwWhcData.fIsPressed And (Not (CInt(wParam) And 1))) Then
                                If dwWhcData.fModRel And dwWhcData.fModSet <> 0 Then
                                    dwWhcData.fModRel = 0
                                    dwWhcData.fModSet = 0
                                End If
                                dwWhcData.vkCode = keyCode
                                dwWhcData.fIsPressed = 1
                            End If
                        End If
                    End If
                    If (fRedraw = 1) Then
                        SetText()
                    End If
            End Select
        End If
        Return CallNextHookEx(_hKeyboardHook, nCode, wParam, lParam)
    End Function

    Private Sub SetText()
        Dim str As String = ""
        Text = ""
        If dwWhcData.fModSet And Modifier.MOD_WIN Then
            str = "Win + "
        End If
        If dwWhcData.fModSet And Modifier.MOD_CONTROL Then
            str += "Ctrl + "
        End If
        If dwWhcData.fModSet And Modifier.MOD_ALT Then
            str += "Alt + "
        End If
        If dwWhcData.fModSet And Modifier.MOD_SHIFT Then
            str += "Shift + "
        End If

        If dwWhcData.vkCode <> 0 Then
            str += vkName.Item(dwWhcData.vkCode)
        End If
        If str = "" Then
            str = "None"
        End If
        Text = str
    End Sub

    Public Sub RemoveHook()
        If _hKeyboardHook <> IntPtr.Zero Then
            If UnhookWindowsHookEx(_hKeyboardHook) Then
                _hKeyboardHook = IntPtr.Zero
            End If
        End If
    End Sub

    <DebuggerHiddenAttribute()> _
    Protected Overrides Sub WndProc(ByRef m As System.Windows.Forms.Message)
        Select Case m.Msg
            Case WM_CHAR, WM_SETCURSOR
                Return
            Case WM_SETTEXT

            Case WM_SETFOCUS
                InstallHook()
                If (dwWhcData.IsNull And Text <> "") Then
                    Text = "None"
                End If
            Case WM_KILLFOCUS
                RemoveHook()
            Case WM_CONTEXTMENU
                Menu()
        End Select
        MyBase.WndProc(m)
    End Sub

    Public Overloads Sub Clear()
        MyBase.Clear()
        Text = "None"
        dwWhcData = New WhcData
        Me.Focus()
    End Sub

    Public Sub InstallHook()
        If _hKeyboardHook = IntPtr.Zero Then
            Dim hinstDLL As IntPtr = Marshal.GetHINSTANCE( _
            [Assembly].GetExecutingAssembly().GetModules()(0))
            _hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, _keyboardProc, 0, 0)
            If _hKeyboardHook = IntPtr.Zero Then
            End If
        End If
    End Sub

    Const HC_ACTION As Integer = 0
    Const WH_KEYBOARD As Int32 = 2
    Const WH_KEYBOARD_LL As Int32 = 13
    Const WM_KEYDOWN As Int32 = &H100
    Const WM_KEYUP As Int32 = &H101
    Const WM_SYSKEYDOWN As Int32 = &H104
    Const WM_SYSKEYUP As Int32 = &H105
    Const WM_KEY As Int32 = &H105 + 55
    Const WM_CHAR As Int32 = &H102
    Const WM_SETFOCUS = 7
    Const WM_KILLFOCUS = 8
    Const WM_SETTEXT = &HC
    Const WM_CONTEXTMENU = &H7B
    Const WM_SETCURSOR = &H20

    Public Enum Modifier
        MOD_NONE = 0
        MOD_ALT = 1
        MOD_CONTROL = 2
        MOD_SHIFT = 4
        MOD_WIN = 8
    End Enum


    Structure KeyboardData
        Public vkCode As Integer
        Public scanCode As Integer
        Public flags As Integer
        Public time As Integer
        Public dwExtraInfo As IntPtr
    End Structure

    Protected Overrides Sub Finalize()
        MyBase.Finalize()
        RemoveHook()
    End Sub

    Public Structure WinHotKey
        Dim modifiers As Modifier
        Dim Key As Keys
    End Structure

    Public ReadOnly Property HotKey() As WinHotKey
        Get
            Dim wkc As New WinHotKey
            wkc.Key = dwWhcData.vkCode
            wkc.modifiers = dwWhcData.fModSet
            Return wkc
        End Get
    End Property

    Private Sub item_click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Dim Menu As MenuItem = CType(sender, MenuItem)
        Select Case Menu.Text
            Case "Win-key"
                'If dwWhcData.vkCode <> 0 Then
                dwWhcData.fModSet = dwWhcData.fModSet Xor Modifier.MOD_WIN
                dwWhcData.fModRel = dwWhcData.fModRel Or dwWhcData.fModSet And Modifier.MOD_WIN
                'End If
            Case "Ctrl-key"
                'If dwWhcData.vkCode <> 0 Then
                dwWhcData.fModSet = dwWhcData.fModSet Xor Modifier.MOD_CONTROL
                dwWhcData.fModRel = dwWhcData.fModRel Or dwWhcData.fModSet And Modifier.MOD_WIN
                'End If
            Case "Alt-key"
                'If dwWhcData.vkCode <> 0 Then
                dwWhcData.fModSet = dwWhcData.fModSet Xor Modifier.MOD_ALT
                dwWhcData.fModRel = dwWhcData.fModRel Or dwWhcData.fModSet And Modifier.MOD_WIN
                'End If
            Case "Shift-key"
                'If dwWhcData.vkCode <> 0 Then
                dwWhcData.fModSet = dwWhcData.fModSet Xor Modifier.MOD_SHIFT
                dwWhcData.fModRel = dwWhcData.fModRel Or dwWhcData.fModSet And Modifier.MOD_WIN
                'End If
            Case "Очистить"
                Clear()
                Return
            Case Else
                For key As Keys = Keys.None To vkName.Count - 1
                    'For key As Keys = Keys.None To Keys.OemClear
                    If Menu.Text = vkName.Item(key) Then
                        dwWhcData.vkCode = key
                        Exit For
                    End If
                Next
        End Select
        SetText()
    End Sub

    Private Sub Menu()
        ContextMenu = New ContextMenu
        Dim MenuItem, subMenu As New MenuItem
        ' ----------------- Обычные клавиши ------------------
        MenuItem = New MenuItem("Обычные клавиши")
        For i As Keys = Keys.Space To Keys.Down
            subMenu = New MenuItem(vkName.Item(i), AddressOf item_click)
            MenuItem.MenuItems.Add(subMenu)
        Next
        subMenu = New MenuItem(vkName.Item(Keys.PrintScreen), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Insert), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Delete), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Escape), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.CapsLock), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Pause), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Apps), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.NumPad0), AddressOf item_click)
        subMenu.BarBreak = True
        MenuItem.MenuItems.Add(subMenu)
        For i As Keys = Keys.NumPad1 To Keys.Divide
            If i <> Keys.Separator Then
                subMenu = New MenuItem(vkName.Item(i), AddressOf item_click)
                MenuItem.MenuItems.Add(subMenu)
            End If
        Next
        subMenu = New MenuItem(vkName.Item(Keys.Back), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.F1), AddressOf item_click)
        subMenu.BarBreak = True
        MenuItem.MenuItems.Add(subMenu)
        For i As Keys = Keys.F2 To Keys.F12
            subMenu = New MenuItem(vkName.Item(i), AddressOf item_click)
            MenuItem.MenuItems.Add(subMenu)
        Next
        subMenu = New MenuItem(vkName.Item(Keys.Tab), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Enter), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.NumLock), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem(vkName.Item(Keys.Scroll), AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        ContextMenu.MenuItems.Add(MenuItem)
        ' ----------------- Мультимедийные клавиши ------------------
        MenuItem = New MenuItem("Мультимедийные клавиши")
        For i As Keys = Keys.BrowserBack To Keys.LaunchApplication2
            If i = Keys.MediaNextTrack Then
                subMenu.BarBreak = True
            End If
            subMenu = New MenuItem(vkName.Item(i), AddressOf item_click)
            MenuItem.MenuItems.Add(subMenu)
        Next
        ContextMenu.MenuItems.Add(MenuItem)
        ' ----------------- Модификаторы ------------------
        MenuItem = New MenuItem("-")
        ContextMenu.MenuItems.Add(MenuItem)
        MenuItem = New MenuItem("Модификаторы")
        subMenu = New MenuItem("Win-key", AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem("Ctrl-key", AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem("Alt-key", AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        subMenu = New MenuItem("Shift-key", AddressOf item_click)
        MenuItem.MenuItems.Add(subMenu)
        ContextMenu.MenuItems.Add(MenuItem)

        MenuItem = New MenuItem("-")
        ContextMenu.MenuItems.Add(MenuItem)
        MenuItem = New MenuItem("Очистить", AddressOf item_click)
        ContextMenu.MenuItems.Add(MenuItem)
    End Sub
End Class
