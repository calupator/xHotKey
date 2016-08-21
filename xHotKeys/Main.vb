Imports System.IO
Imports CoreAudioApi

Public Class Main
    Dim hk As New Dictionary(Of Integer, HotKey)
    Const FileSettings As String = "Settings.xml"
    Private device As MMDevice
    WithEvents remote As RemoteControl
    Delegate Sub InvokeDelegate(ByVal key As Integer)

    Private Sub Form1_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        TrayIcon.Visible = False
        remote.Stop()

        Settings.SaveHK(hk)
    End Sub

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load

        remote = New RemoteControl("Remote.exe")
        'remote = New RemoteControl("remote.surrogate")

        Settings.File(FileSettings)
        HotKey.SetHandle(Me.Handle)
        hk = Settings.LoadHK(Me.Handle)

        For Each it As KeyValuePair(Of Integer, HotKey) In hk
            it.Value.Register()
        Next
        Dim DevEnum As New MMDeviceEnumerator()
        device = DevEnum.GetDefaultAudioEndpoint(EDataFlow.eRender, ERole.eMultimedia)
        tbMaster.Value = CInt(Fix(device.AudioEndpointVolume.MasterVolumeLevelScalar * 100))
        AddHandler device.AudioEndpointVolume.OnVolumeNotification, New AudioEndpointVolumeNotificationDelegate(AddressOf AudioEndpointVolume_OnVolumeNotification)
    End Sub

    Private Sub remotekey(ByVal key As Integer) Handles remote.RemotKey
        TextBox2.BeginInvoke(New InvokeDelegate(AddressOf InvokeMethod), key)
    End Sub 'Invoke_Click

    Public Sub InvokeMethod(ByVal key As Integer)
        TextBox2.Text += "Код нажатой кнопки: " & Hex(key) & Environment.NewLine
        TextBox2.Select(TextBox2.TextLength, 0)
        TextBox2.ScrollToCaret()
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
                If hk.ContainsKey(m.WParam.ToInt32()) Then
                    For Each it In hk
                        ' Check that the ID is our key and we are registerd
                        If it.Value.IsRegister AndAlso (m.WParam.ToInt32() = it.Value.GetID) Then
                            ' Fire the event and pass on the event if our handlers didn't handle it
                            it.Value.Execute()
                        End If
                    Next
                End If
        End Select
        MyBase.WndProc(m)
    End Sub

    Private Sub tbMaster_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tbMaster.Scroll
        device.AudioEndpointVolume.MasterVolumeLevelScalar = (CSng(tbMaster.Value) / 100.0F)
    End Sub

    Public Sub New()

        ' Этот вызов необходим конструктору форм Windows.
        InitializeComponent()
#If DEBUG Then
        TextBox1 = New WinHotKey
#End If
        ' Добавьте все инициализирующие действия после вызова InitializeComponent().
        TrayIcon.Icon = My.Resources.appIcon
        TrayIcon.Text = Application.ProductName + " " + Application.ProductVersion
        TrayIcon.Visible = True
        Me.Text = TrayIcon.Text
        Me.Icon = My.Resources.appIcon
    End Sub

    Private Sub TrayIcon_MouseDoubleClick(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs)
        Me.Visible = Not Me.Visible
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        ComboBox1.Items.Clear()
        For i = 0 To remote.GetCount - 1
            ComboBox1.Items.Add(remote.CardName(i))
        Next

    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox1.SelectedIndexChanged
        Dim rr As ComboBox = CType(sender, ComboBox)
        If remote.SelectCard(rr.SelectedIndex) Then

            Label1.Text = "OK"
            Label1.ForeColor = Color.Lime
        Else
            Label1.Text = "Ошибка!"
            Label1.ForeColor = Color.Red
        End If
    End Sub
End Class
