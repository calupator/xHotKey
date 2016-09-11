Imports System.Threading

Public Class ExecuteKeys

    Public Shared hk As New Dictionary(Of UInteger, HotKey)

    Public Sub HotKeys(ByVal KeyID As UInteger, ByVal type As Enums.EventType)
        If (hk.ContainsKey(KeyID)) Then ' Проверка на наличие HotKey с этим ID
            hk.Item(KeyID).Execute() ' Вызов команды с соответствующим ID
        Else
            For Each it In hk
                If (it.Value.RemoteControl.ContainsKey(KeyID)) Then
                    For Each it2 In it.Value.RemoteControl
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

End Class
