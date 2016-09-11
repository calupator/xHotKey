Imports System.IO
Imports CoreAudioApi
Imports BEHOLDSERVICELib

Public Class Main
    Const FileSettings As String = "Settings.xml"
    Private device As MMDevice ' Инициализация класса громкости
    Private HotK As ExecuteKeys ' Инициализация класса 

    Private Sub Form1_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        TrayIcon.Visible = False
        TimerGetRemote.Stop()
        Settings.SaveHK(ExecuteKeys.hk)
    End Sub

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load

        HotK = New ExecuteKeys
        'HotK.EventsRC.Run("notepad.exe")
        cbTuner.Items.Clear()
        For i = 0 To Beholder.Count - 1
            cbTuner.Items.Add(Beholder.Name(i))
        Next
        ' Проверка есть ли в списке устройств видеозахвата тюнер Behold,
        ' если есть - инициализация,
        ' нет - пропуск инициализации.
        If (cbTuner.FindString("Behold") > -1) Then
            ' Поиск слова 'Behold' в списке cbTuner и инициализация тюнера с соотв. индексом
            cbTuner.SelectedIndex = cbTuner.FindString("Behold")
            Beholder.SelectCard(CULng(cbTuner.SelectedIndex))
        End If

        Settings.File(FileSettings)
        HotKey.SetHandle(Me.Handle)
        ExecuteKeys.hk = Settings.LoadHK(Me.Handle)

        For Each it As KeyValuePair(Of UInteger, HotKey) In ExecuteKeys.hk
            it.Value.Register()
        Next
        TimerGetRemote.Enabled = True
        TimerGetRemote.Interval = 100
        TimerGetRemote.Start()

        Dim DevEnum As New MMDeviceEnumerator()
        device = DevEnum.GetDefaultAudioEndpoint(EDataFlow.eRender, ERole.eMultimedia)
        tbMaster.Value = CInt(Fix(device.AudioEndpointVolume.MasterVolumeLevelScalar * 100))
        AddHandler device.AudioEndpointVolume.OnVolumeNotification, New AudioEndpointVolumeNotificationDelegate(AddressOf AudioEndpointVolume_OnVolumeNotification)
    End Sub

    Private Sub AudioEndpointVolume_OnVolumeNotification(ByVal data As AudioVolumeNotificationData)
        If Me.InvokeRequired Then
            Dim Params(0) As Object
            Params(0) = data
            Me.Invoke(New AudioEndpointVolumeNotificationDelegate(AddressOf AudioEndpointVolume_OnVolumeNotification), Params)
        Else
            tbMaster.Value = CInt(Fix(data.MasterVolume * 100))
        End If
    End Sub

    <DebuggerHiddenAttribute()> _
    <System.Security.Permissions.PermissionSetAttribute(System.Security.Permissions.SecurityAction.Demand, Name:="FullTrust")> _
    Protected Overrides Sub WndProc(ByRef m As Message)
        Dim WM_HOTKEY = &H312

        ' Listen for operating system messages
        Select Case (m.Msg)
            Case WM_HOTKEY
                HotK.HotKeys(CUInt(m.WParam), Enums.EventType.HotKeys)
                remote(CUInt(m.WParam), Enums.EventType.HotKeys)
        End Select
        MyBase.WndProc(m)
    End Sub

    Private Sub tbMaster_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tbMaster.Scroll
        device.AudioEndpointVolume.MasterVolumeLevelScalar = (CSng(tbMaster.Value) / 100.0F)
    End Sub
    Public Sub New()
        ' Этот вызов необходим конструктору форм Windows.

        InitializeComponent()

        ' Добавьте все инициализирующие действия после вызова InitializeComponent().
        TrayIcon.Icon = My.Resources.appIcon
        TrayIcon.Text = Application.ProductName + Chr(32) + Application.ProductVersion
        TrayIcon.Visible = True
        Me.Text = TrayIcon.Text
        Me.Icon = My.Resources.appIcon
    End Sub

    Private Sub TrayIcon_MouseDoubleClick(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles TrayIcon.MouseDoubleClick
        Me.Visible = Not Me.Visible
    End Sub

    Private Sub cbTuner_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbTuner.SelectedIndexChanged
        Beholder.SelectCard(cbTuner.SelectedIndex)
        If Beholder.IsInit Then
            Label1.Text = "Инициализация выполнена успешно!"
            Label1.ForeColor = Color.Green
        Else
            Label1.Text = "Ошибка инициализации!"
            Label1.ForeColor = Color.Red
        End If

    End Sub

    Public Sub remote(ByVal k As UInteger, ByVal type As Enums.EventType)
        Select Case type
            Case Enums.EventType.HotKeys
                For Each it In ExecuteKeys.hk
                    ' Check that the ID is our key and we are registerd
                    If it.Value.IsRegister AndAlso (k = it.Value.GetID) Then
                        ' Fire the event and pass on the event if our handlers didn't handle it

                        Label2.Text = "Нажата горячая клавиша - " + it.Value.Name + " (" + it.Value.Path + ")"
                    End If
                Next

            Case Enums.EventType.RemoteControl
                For Each it In ExecuteKeys.hk
                    If (it.Value.RemoteControl.ContainsKey(k)) Then
                        For Each it2 In it.Value.RemoteControl
                            ' Check that the ID is our key and we are registerd
                            If it2.Key = k Then
                                ' Fire the event and pass on the event if our handlers didn't handle it
                                'it.Value.Execute()
                                Label2.Text = "Нажата кнопка - " + it2.Value.NameButton + " (" + Hex(k) + ")"
                            End If
                        Next
                    End If
                Next

        End Select
    End Sub

    Private Sub TimerGetKeys_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TimerGetRemote.Tick
        If (Beholder.IsInit) Then
            Dim key As UInteger = Beholder.GetRemoteEx
            If (key <> 0) Then
                HotK.HotKeys(key, Enums.EventType.RemoteControl)
                remote(key, Enums.EventType.RemoteControl)
            End If
        End If
    End Sub
End Class
