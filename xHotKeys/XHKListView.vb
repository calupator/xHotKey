Public Class XHKListView
    Inherits ListView

    Dim lock As Boolean
    Dim subitem As Integer


    Private Sub listView_MouseDown(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseDown
        If e.Clicks > 1 Then
            Dim tbox As New TextBox()
            Me.Controls.Add(tbox)

            tbox.Width = Me.Columns(subitem).Width
            Dim item As ListViewItem = Me.GetItemAt(0, e.Y)
            If item IsNot Nothing Then
                Dim x_cord As Integer = 0
                If subitem <> 0 Then
                    For i As Integer = 0 To subitem - 1
                        x_cord += Me.Columns(i).Width
                    Next i
                End If
                tbox.Left = x_cord
                tbox.Top = item.Position.Y
                tbox.Text = item.SubItems(subitem).Text
                AddHandler tbox.Leave, AddressOf DisposeTextBox
                AddHandler tbox.KeyPress, AddressOf TextBoxKeyPress
                Me.Controls.Add(tbox)
                lock = True
                tbox.Focus()
                tbox.Select(0, tbox.Text.Length)

            End If
        End If
    End Sub

    Private Sub DisposeTextBox(ByVal sender As Object, ByVal e As EventArgs)
        Dim tb = (TryCast(sender, TextBox))
        Dim item = Me.GetItemAt(0, tb.Top + 1)
        If item IsNot Nothing Then
            item.SubItems(subitem).Text = tb.Text
        End If
        tb.Dispose()
        lock = False
    End Sub

    Private Sub TextBoxKeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
        If e.KeyChar = Chr(13) Then
            DisposeTextBox((TryCast(sender, TextBox)), Nothing)
        End If
        If e.KeyChar = Chr(27) Then
            TryCast(sender, TextBox).Dispose()
        End If
    End Sub

    Private Sub ListView_MouseMove(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Me.MouseMove
        Dim ff As ListView = sender
        Dim d As Integer = 0
        For i = 0 To ff.Columns.Count - 1

            d += ff.Columns.Item(i).Width
            If e.X < d Then
                Dim fff As ListViewItem = ff.GetItemAt(e.X, e.Y)
                If (Not lock) Then
                    subitem = i
                    Exit For
                End If
            End If
        Next

    End Sub

    Public ReadOnly Property SelectedSubItem() As Integer
        Get
            Return subitem
        End Get
    End Property
End Class
