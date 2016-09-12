Public Class SettingsForm

    Public lst As New List(Of Object)


    Private Sub SplitContainer1_SplitterMoved(ByVal sender As System.Object, ByVal e As System.Windows.Forms.SplitterEventArgs) Handles SplitContainer1.SplitterMoved
        If SplitContainer1.SplitterDistance > 250 Then
            SplitContainer1.SplitterDistance = 250

        End If
    End Sub


    Private Sub SettingsForm_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        ListView1.Items.Clear()
        For Each hk In ExecuteKeys.hk
            Dim Ilst As New ListViewItem(hk.Value.Name)
            Ilst.SubItems.Add(hk.Value.ToString())
            Ilst.SubItems.Add(hk.Value.Path)
            Ilst.SubItems.Add(hk.Value.WorkingDir)
            ListView1.Items.Add(Ilst)
        Next
    End Sub

    Private Sub ListView1_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles ListView1.DoubleClick
        Dim frm As EditXHK = New EditXHK

        frm.ShowDialog(Me)

    End Sub


    Private Sub SettingsForm_Activated(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Activated
        Dim Item As ListViewItem = New ListViewItem(lst(0).ToString)
        Item.SubItems.Add(lst(1))
        Item.SubItems.Add(lst(2))
        Item.SubItems.Add(lst(3))
        Item.SubItems.Add(lst(4))
        ListView1.Items.Add(Item)

    End Sub
End Class