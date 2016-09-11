Imports BEHOLDSERVICELib
Imports System.Threading

Public Class Beholder
    Protected Shared bh As IBeholderRC = New BeholderRC

    Private Shared index As Integer = 0

    Public Shared ReadOnly Property IsInit() As Boolean
        Get
            Return bh.IsInit
        End Get
    End Property

    Public Shared ReadOnly Property Count() As Integer
        Get
            Return CInt(bh.Count)
        End Get
    End Property

    Public Shared ReadOnly Property SelectedCard() As Integer
        Get
            Return index
        End Get
    End Property

    Public Shared ReadOnly Property Name(ByVal i As Integer) As String
        Get
            Return bh.Name(CUInt(i))
        End Get
    End Property

    Public Shared Function SelectCard(ByVal i As Integer) As Boolean
        If (bh.SelectCard(CUInt(i))) Then
            index = i
            Return True
        Else
            index = -1
            Return False
        End If
    End Function

    Public Shared Function Run(ByVal path As String) As Boolean
        Return bh.Run(path)
    End Function

    Public Shared Function GetRemote()
        Return bh.GetRemote
    End Function

    Public Shared Function GetRemoteEx()
        Return bh.GetRemoteEx
    End Function

    Structure ButtonRC
        Public NameRC As String
        Public NameButton As String
        Public RemoteID As UInteger
    End Structure

    Protected Overrides Sub Finalize()
        MyBase.Finalize()
    End Sub
End Class
