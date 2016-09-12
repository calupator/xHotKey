Public Class EditXHK

    Private Sub EditXHK_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Dim lst As ListView.SelectedListViewItemCollection = CType(Owner, SettingsForm).ListView1.SelectedItems
        With lst.Item(0).SubItems
            txtName.Text = .Item(0).Text
            txtHotKey.Text = .Item(1).Text
            txtPath.Text = .Item(2).Text
            txtWorkDir.Text = .Item(3).Text
        End With
    End Sub


    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btCancel.Click
        Close()
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btOK.Click
        CType(Owner, SettingsForm).lst.Add(txtName.Text)
        CType(Owner, SettingsForm).lst.Add(txtHotKey.Text)
        CType(Owner, SettingsForm).lst.Add(txtPath.Text)
        CType(Owner, SettingsForm).lst.Add(txtWorkDir.Text)
        Close()
    End Sub

    Private Sub RadioButton1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton1.CheckedChanged
        txtPath.Enabled = True
        txtWorkDir.Enabled = True

    End Sub

    Private Sub RadioButton2_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RadioButton2.CheckedChanged
        txtPath.Enabled = False
        txtWorkDir.Enabled = False
    End Sub
End Class