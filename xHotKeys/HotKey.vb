Imports System.Runtime.InteropServices
Imports CoreAudioApi


Public Class HotKey
    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Public Shared Function SetForegroundWindow(ByVal hwnd As IntPtr) As <MarshalAs(UnmanagedType.Bool)> Boolean
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function SendMessage(ByVal hWnd As IntPtr, ByVal Msg As UInteger, ByVal wParam As IntPtr, ByVal lParam As IntPtr) As IntPtr
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function RegisterHotKey(ByVal hWnd As IntPtr, ByVal id As Integer, ByVal fsModifiers As UInteger, ByVal vk As Keys) As Integer
    End Function

    <DllImport("user32.dll", SetLastError:=True, CharSet:=CharSet.Auto)> _
    Private Shared Function UnregisterHotKey(ByVal hWnd As IntPtr, ByVal id As Integer) As Integer
    End Function

    Public Shared device As MMDevice

    Private Shared hwnd As IntPtr ' Handle окна 'Main'
    Private _name As String ' Название команды
    Private _exe As String ' Файл запуска
    Private _args As String ' Аргумент командной строки
    Private _workDir As String ' Рабочая папка
    Private _sound As String ' Звуковой файл
    Private _modif As Enums.Modifiers ' Модификаторы горячих клавиш
    Protected _vKey As Keys ' Код клавиши
    Private _winStyle As Enums.WindowState ' Статус окна свернуто, развернуто
    Private _priority As ProcessPriorityClass ' Приорирет процесса
    Private _cmd As Enums.Command ' Системная команда
    Private _isRegister As Boolean ' Флаг регистрации HotKey
    Private _id As Integer ' Идентификатор HotKey
    Private _newInst As Boolean ' Флаг, запускать новый или активировать имеющийся процесс
    Public RemoteControl As Dictionary(Of UInteger, Beholder.ButtonRC) ' Список кнопок пультов (код кнопки, имяПульта/имяКнопки/IDПульта)

    Public Sub New()
        'hwnd = Nothing
        _name = ""
        _exe = ""
        _args = ""
        _workDir = ""
        _sound = ""
        _modif = Enums.Modifiers.None
        _vKey = Keys.None
        _winStyle = Enums.WindowState.Normal
        _priority = ProcessPriorityClass.Normal
        _cmd = Enums.Command.None
        _isRegister = False
        _id = GetHashCode()
        _newInst = False
        Dim DevEnum As New MMDeviceEnumerator()
        device = DevEnum.GetDefaultAudioEndpoint(EDataFlow.eRender, ERole.eMultimedia)
        RemoteControl = New Dictionary(Of UInteger, Beholder.ButtonRC)
    End Sub

    Public Shared Operator =(ByVal lhk As HotKey, ByVal rhk As HotKey) As Boolean
        If (lhk._modif = rhk._modif) And (lhk._vKey = rhk._vKey) Then
            Return True
        End If
        Return False
    End Operator

    Public Shared Operator <>(ByVal lhk As HotKey, ByVal rhk As HotKey) As Boolean
        If (lhk._modif <> rhk._modif) And (lhk._vKey <> rhk._vKey) Then
            Return True
        End If
        Return False
    End Operator

    Private Sub New(ByVal handle As IntPtr)
        hwnd = handle
        _name = ""
        _exe = ""
        _args = ""
        _workDir = ""
        _sound = ""
        _modif = Enums.Modifiers.None
        _vKey = Keys.None
        _winStyle = Enums.WindowState.Normal
        _priority = ProcessPriorityClass.Normal
        _cmd = Enums.Command.None
        _isRegister = False
        _id = GetHashCode()
        _newInst = False
    End Sub

    Public Shared Sub SetHandle(ByVal handle As IntPtr)
        hwnd = handle
    End Sub

    Public Property Name() As String
        Get
            Return _name
        End Get
        Set(ByVal value As String)
            _name = value
        End Set
    End Property

    Public Property Path() As String
        Get
            Return _exe
        End Get
        Set(ByVal value As String)
            _exe = value
        End Set
    End Property

    Public Property Argument() As String
        Get
            Return _args
        End Get
        Set(ByVal value As String)
            _args = value
        End Set
    End Property

    Public Property WorkingDir() As String
        Get
            Return _workDir
        End Get
        Set(ByVal value As String)
            _workDir = value
        End Set
    End Property

    Public Property Sound() As String
        Get
            Return _sound
        End Get
        Set(ByVal value As String)
            _sound = value
        End Set
    End Property

    Public Property Modifier() As Enums.Modifiers
        Get
            Return _modif
        End Get
        Set(ByVal value As Enums.Modifiers)
            _modif = value
        End Set
    End Property

    Public Property Key() As Keys
        Get
            Return _vKey
        End Get
        Set(ByVal value As Keys)
            _vKey = value
        End Set
    End Property

    Public Property WindowStyle() As Enums.WindowState
        Get
            Return _winStyle
        End Get
        Set(ByVal value As Enums.WindowState)
            _winStyle = value
        End Set
    End Property

    Public Property Priority() As ProcessPriorityClass
        Get
            Return _priority
        End Get
        Set(ByVal value As ProcessPriorityClass)
            _priority = value
        End Set
    End Property

    Public Property Command() As Enums.Command
        Get
            Return _cmd
        End Get
        Set(ByVal value As Enums.Command)
            _cmd = value
        End Set
    End Property

    Public ReadOnly Property IsRegister() As Boolean
        Get
            Return _isRegister
        End Get
    End Property

    Public ReadOnly Property GetID() As Integer
        Get
            Return _id
        End Get
    End Property

    Public Property NewInstance() As Boolean
        Get
            Return _newInst
        End Get
        Set(ByVal value As Boolean)
            _newInst = value
        End Set
    End Property

    Public Sub Register()
        _isRegister = RegisterHotKey(hwnd, _id, _modif, _vKey)
    End Sub

    Public Sub Unregister()
        _isRegister = UnregisterHotKey(hwnd, _id)
    End Sub

    'Dim t, g As Integer
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
        If _cmd <> 0 Then
            ShellCommand()
            Exit Sub
        End If
        Dim _proc() As Process = Process.GetProcessesByName(_exe.Remove(_exe.LastIndexOf(".")))
        If _proc.Length > 0 And _newInst = False Then
            SetForegroundWindow(_proc.First.MainWindowHandle)
        Else
            Dim proc As New Process
            With proc.StartInfo
                .FileName = _exe
                .Arguments = _args
                .CreateNoWindow = False
                .WorkingDirectory = _workDir
                .UseShellExecute = False
            End With
            proc.Start()
            'proc.StartInfo.WindowStyle = winStyle
            proc.PriorityClass = _priority
            Select Case _winStyle
                Case Enums.WindowState.Normal
                    SendMessage(proc.MainWindowHandle, &H112, &HF120, 0)
                Case Enums.WindowState.Minimize
                    SendMessage(proc.MainWindowHandle, &H112, &HF020, 0)
                Case Enums.WindowState.Maximize
                    SendMessage(proc.MainWindowHandle, &H112, &HF030, 0)
            End Select
        End If
        'End If
        'End If
        'End If
        't = Environment.TickCount
    End Sub

    Private Sub ShellCommand()
        Select Case _cmd
            Case Enums.Command.VolUp
                Dim lvl As Single = device.AudioEndpointVolume.MasterVolumeLevelScalar
                lvl += 5 / 100.0F
                If lvl > 1 Then
                    device.AudioEndpointVolume.MasterVolumeLevelScalar = 1
                Else
                    device.AudioEndpointVolume.MasterVolumeLevelScalar = lvl
                End If
            Case Enums.Command.VolDown
                Dim lvl As Single = device.AudioEndpointVolume.MasterVolumeLevelScalar
                lvl -= 5 / 100.0F
                If lvl < 0 Then
                    device.AudioEndpointVolume.MasterVolumeLevelScalar = 0
                Else
                    device.AudioEndpointVolume.MasterVolumeLevelScalar = lvl
                End If
            Case Enums.Command.LockWorkStation
                Reboot.Lock()
        End Select
    End Sub

    Protected Overrides Sub Finalize()
        Unregister()
        MyBase.Finalize()
    End Sub

    Public Overrides Function ToString() As String
        Dim str As String = ""
        If _modif And Enums.Modifiers.Windows Then
            str = "Win + "
        End If
        If _modif And Enums.Modifiers.Control Then
            str += "Ctrl + "
        End If
        If _modif And Enums.Modifiers.Alt Then
            str += "Alt + "
        End If
        If _modif And Enums.Modifiers.Shift Then
            str += "Shift + "
        End If

        If _vKey <> 0 Then
            str += _vKey.ToString
        End If
        If str = "" Then
            str = "None"
        End If
        Return str
    End Function

End Class