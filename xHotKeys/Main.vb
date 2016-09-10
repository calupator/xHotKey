Imports System.IO
Imports CoreAudioApi
Imports BEHOLDSERVICELib

Public Class Main
    Const FileSettings As String = "Settings.xml"
    Private device As MMDevice
    Private HotK As ExecuteKeys ' Инициализация Beholder
    Public Event HotKeys(ByVal ID As UInteger)

    Private Sub Form1_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        TrayIcon.Visible = False

        Settings.SaveHK(ExecuteKeys.hk)
    End Sub

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load

        HotK = New ExecuteKeys
        HotK.EventsRC.Run("notepad.exe")
        ' Dim count As UInteger = beholder.EventsRC.Count
        cbTuner.Items.Clear()
        For i = 0 To HotK.EventsRC.Count - 1
            cbTuner.Items.Add(HotK.EventsRC.Name(i))
        Next
        cbTuner.SelectedIndex = cbTuner.FindString("Behold")
        HotK.EventsRC.SelectCard(CULng(cbTuner.SelectedIndex))


        Settings.File(FileSettings)
        HotKey.SetHandle(Me.Handle)
        ExecuteKeys.hk = Settings.LoadHK(Me.Handle)

        For Each it As KeyValuePair(Of Integer, HotKey) In ExecuteKeys.hk
            it.Value.Register()
        Next
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

    <System.Security.Permissions.PermissionSetAttribute(System.Security.Permissions.SecurityAction.Demand, Name:="FullTrust")> _
    Protected Overrides Sub WndProc(ByRef m As Message)
        Dim WM_HOTKEY = &H312

        ' Listen for operating system messages
        Select Case (m.Msg)
            Case WM_HOTKEY
            'If ExecuteKeys.hk.ContainsKey(m.WParam.ToInt32()) Then
                RaiseEvent HotKeys(CUInt(m.WParam))
                'End If
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
        If HotK.EventsRC.SelectCard(cbTuner.SelectedIndex) Then
            Label1.Text = "Инициализация выполнена успешно!"
            Label1.ForeColor = Color.Green
        Else
            Label1.Text = "Ошибка инициализации!"
            Label1.ForeColor = Color.Red
        End If

    End Sub


    Public Sub remot(ByVal k As UInteger)
        MessageBox.Show("Код нажатой кнопки - " + Hex(k))
    End Sub

End Class
