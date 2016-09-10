Public Class ExecuteKeys
    'WithEvents EventsMain As Main
    Public WithEvents EventsRC As New Beholder

    Public Shared hk As New Dictionary(Of Integer, HotKey)

    Public Sub Execute_Main(ByVal KeyID As UInteger) 'Handles EventsMain.HotKeys
        If (hk.ContainsKey(KeyID)) Then
            For Each it In hk
                ' Check that the ID is our key and we are registerd
                If it.Value.IsRegister AndAlso (KeyID = it.Value.GetID) Then
                    ' Fire the event and pass on the event if our handlers didn't handle it
                    it.Value.Execute()
                End If
            Next
        Else
            For Each it In hk
                If (it.Value.RemoteControl.ContainsKey(KeyID)) Then
                    For Each it2 In it.Value.RemoteControl

                        Main.remot(KeyID)

                        ' Check that the ID is our key and we are registerd
                        If it2.Key = KeyID Then
                            ' Fire the event and pass on the event if our handlers didn't handle it
                            it.Value.Execute()
                        End If

                    Next
                End If
            Next
        End If
    End Sub

    '  Public Sub Execute_Beholder(ByVal Key As UInteger) Handles EventsRC.RemoteKey
    '      For Each it In hk
    ' Check that the ID is our key and we are registerd
    '          If it.Value.IsRegister Or it.co Then
    ' Fire the event and pass on the event if our handlers didn't handle it
    '             it.Value.Execute()
    '         End If
    '     Next
    '
    '   End Sub

End Class
