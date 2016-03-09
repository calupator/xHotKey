Imports System.Runtime.InteropServices


'<Serializable()> _
Public Class HotKey
    <DllImport("user32.dll")> _
    Public Shared Function SetForegroundWindow(ByVal hwnd As IntPtr) As <MarshalAs(UnmanagedType.Bool)> Boolean
    End Function

    '<NonSerialized()> _
    Private hwnd As IntPtr
    '<NonSerialized()> _
    Private isRegister As Boolean
    Private vKey As Keys
    Private modif As Modifiers
    Private id As Integer
    '<NonSerialized()> _
    'Shared prevID As Integer = 0
    Private exe As String
    Private args As String
    Private workDir As String
    Private winStyle As WindowState
    Private newInst As Boolean
    Private prior As ProcessPriorityClass

    Private Sub New()
        hwnd = Nothing
        isRegister = False
        vKey = Keys.None
        modif = Modifiers.None
        id = GetHashCode()
        'prevID = id
        exe = ""
        args = ""
        winStyle = ProcessWindowStyle.Normal
        workDir = ""
        newInst = False
        prior = ProcessPriorityClass.Normal
    End Sub

    Public Sub New(ByVal handle As IntPtr)
        hwnd = handle
        isRegister = False
        vKey = Keys.None
        modif = Modifiers.None
        id = GetHashCode()
        'prevID = id
        exe = ""
        args = ""
        winStyle = ProcessWindowStyle.Normal
        workDir = ""
        newInst = False
        prior = ProcessPriorityClass.Normal
    End Sub

    Public Sub SetHandle(ByVal handle As IntPtr)
        hwnd = handle
    End Sub

    Public Property WindowStyle() As ProcessWindowStyle
        Get
            Return winStyle
        End Get
        Set(ByVal value As ProcessWindowStyle)
            winStyle = value
        End Set
    End Property

    Public Property Priority() As ProcessPriorityClass
        Get
            Return prior
        End Get
        Set(ByVal value As ProcessPriorityClass)
            prior = value
        End Set
    End Property

    Public Property NewInstance() As Boolean
        Get
            Return newInst
        End Get
        Set(ByVal value As Boolean)
            newInst = value
        End Set
    End Property

    Public Property Argument() As String
        Get
            Return args
        End Get
        Set(ByVal value As String)
            args = value
        End Set
    End Property

    Public Property WorkingDir() As String
        Get
            Return workDir
        End Get
        Set(ByVal value As String)
            workDir = value
        End Set
    End Property

    Public Property Key() As Keys
        Get
            Return vKey
        End Get
        Set(ByVal value As Keys)
            vKey = value
        End Set
    End Property

    Public Property Modifier() As Modifiers
        Get
            Return modif
        End Get
        Set(ByVal value As Modifiers)
            modif = value
        End Set
    End Property


    Public Sub Register()
        isRegister = RegisterHotKey(hwnd, id, modif, vKey)
    End Sub

    'Public Shared ReadOnly Property GetPrevID() As Integer
    '    Get
    '        Return prevID
    '    End Get
    'End Property

    Public ReadOnly Property GetID() As Integer
        Get
            Return id
        End Get
    End Property

    Public Property Command() As String
        Get
            Return exe
        End Get
        Set(ByVal value As String)
            exe = value
        End Set
    End Property


    Public ReadOnly Property IsRegistered() As Boolean
        Get
            Return isRegister
        End Get
    End Property

    Public Sub Unregister()
        isRegister = UnregisterHotKey(hwnd, id)
    End Sub

    ' Dim t, g As Integer
    'Dim k As Integer = 2

    Public Sub Execute()
        'If k = 2 Then
        't = Environment.TickCount
        'k -= 1
        'Else
        'g = Environment.TickCount
        'If ((g - t) < 500) Then
        'k -= 1
        'If k = 0 Then
        'MessageBox.Show("тройной")
        'k = 2
        Dim _proc() As Process = Process.GetProcessesByName(exe.Remove(exe.LastIndexOf(".")))
        If _proc.Length > 0 And newInst = False Then
            SetForegroundWindow(_proc.First.MainWindowHandle)
        Else
            Dim proc As New Process
            With proc.StartInfo
                .FileName = exe
                .Arguments = args
                .CreateNoWindow = False
                .WorkingDirectory = workDir
                .UseShellExecute = False
            End With
            proc.Start()
            'proc.StartInfo.WindowStyle = winStyle
            proc.PriorityClass = prior
            SendMessage(proc.MainWindowHandle, &H112, winStyle, 0)
            SendMessage(proc.MainWindowHandle, &H112, winStyle, 0)
        End If
        'End If
        'End If
        'End If
        't = Environment.TickCount
    End Sub

    Protected Overrides Sub Finalize()
        Unregister()
        MyBase.Finalize()
    End Sub

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function SendMessage(ByVal hWnd As IntPtr, ByVal Msg As UInteger, ByVal wParam As IntPtr, ByVal lParam As IntPtr) As IntPtr
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function RegisterHotKey(ByVal hWnd As IntPtr, ByVal id As Integer, ByVal fsModifiers As UInteger, ByVal vk As Keys) As Integer
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function UnregisterHotKey(ByVal hWnd As IntPtr, ByVal id As Integer) As Integer
    End Function
End Class
