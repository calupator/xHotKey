﻿Imports BEHOLDSERVICELib
Imports System.Threading

Public Class Beholder
    Protected bh As IBeholderRC
    Protected ThreadGetKey As Thread
    Public Event RemoteKey(ByVal Key As UInteger)


    Public Sub New()
        bh = New BeholderRC
        ' ThreadGetKey = New Thread(New ThreadStart(AddressOf thGetKeyMethod))
        'ThreadGetKey.Start()
    End Sub

    Dim t, g As Integer
    Dim k As Integer = 2

    Public Sub Execute()
        If k = 2 Then
            t = Environment.TickCount
            k -= 1
        Else
            g = Environment.TickCount
            If ((g - t) < 500) Then
                k -= 1
                If k = 0 Then
                    MessageBox.Show("тройной")
                    k = 2
                End If
            End If
        End If
        t = Environment.TickCount
    End Sub

    Public ReadOnly Property Count() As Integer
        Get
            Return CInt(bh.Count)
        End Get
    End Property

    Public ReadOnly Property Name(ByVal i As Integer) As String
        Get
            Return bh.Name(CUInt(i))
        End Get
    End Property

    Public Function SelectCard(ByVal i As Integer) As Boolean
        Return bh.SelectCard(CUInt(i))
    End Function

    Public Function Run(ByVal path As String) As Boolean
        Return bh.Run(path)
    End Function

    Private Sub thGetKeyMethod()
        While (Not bh.isInit)
            Dim key As UInteger = bh.GetRemoteEx
            If (key <> 0) Then RaiseEvent RemoteKey(key)
        End While
    End Sub

    Structure ButtonRC
        Public NameRC As String
        Public Name As String
        Public RemoteID As UInteger
    End Structure
End Class
