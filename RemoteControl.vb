Imports System.Threading
Imports System.IO.Pipes
Imports System.IO

Public Class RemoteControl
    Dim pipeClient As New Process
    Dim thInfo As Thread
    Dim thGetKey As Thread
    Dim namePipe As String = "NewPipe"
    Dim Closing As Boolean = 0
    Dim pipeServer As NamedPipeServerStream
    Dim srInfo As StreamReader
    Dim srGetKey As StreamReader
    Dim swInfo As StreamWriter
    Private Count As Integer

    Public Event RemotKey(ByVal key As Integer)

    Public Sub New(ByVal SurrProc As String)
        pipeClient.StartInfo.FileName = AppDomain.CurrentDomain.SetupInformation.ApplicationBase & SurrProc
        pipeClient.StartInfo.UseShellExecute = False

        thInfo = New Thread(New ThreadStart(AddressOf thInfoMethod))
        thGetKey = New Thread(New ThreadStart(AddressOf thGetKeyMethod))

        thInfo.Start()
        thGetKey.Start()
        pipeServer = New NamedPipeServerStream(namePipe, PipeDirection.InOut)

    End Sub

    Public Function GetCount() As Integer
        If Not pipeServer.IsConnected() Then
            Return Nothing
        End If
        swInfo.WriteLine("GetCardCount")

        Return CType(srInfo.ReadLine, Integer)
    End Function

    Public Function CardName(ByVal index As Integer) As String
        If pipeServer.IsConnected() Then
        Else
            Return Nothing
        End If
        swInfo.WriteLine("GetCardName")
        swInfo.WriteLine(index.ToString)
        Return srInfo.ReadLine()
    End Function

    Public Function SelectCard(ByVal index As Integer) As Boolean
        swInfo.WriteLine("SelectCard")
        swInfo.WriteLine(index.ToString)
        If CType(srInfo.ReadLine(), Integer) Then
            Return True
        End If
        Return False
    End Function

    Public Sub [Stop]()
        Closing = True
    End Sub

    Private Sub thGetKeyMethod()
        Dim pipeRecive As New NamedPipeServerStream(namePipe & "1", PipeDirection.In)
        pipeRecive.WaitForConnection()
        srGetKey = New StreamReader(pipeRecive)
        While (Not Closing)
            Dim key As Integer = CType(srGetKey.ReadLine, Integer)
            If (key <> 0) Then RaiseEvent RemotKey(key)
        End While
        pipeRecive.Disconnect()
        srGetKey.Close()
    End Sub

    Private Sub thInfoMethod()
        pipeClient.StartInfo.Arguments = namePipe
        pipeClient.Start()

        ' Wait for a client to connect
        pipeServer.WaitForConnection()
        Try
            ' Read the request from the client. Once the client has
            ' written to the pipe, its security token will be available.
            srInfo = New StreamReader(pipeServer)
            swInfo = New StreamWriter(pipeServer)
            swInfo.AutoFlush = True

            While (Not Closing)
                Thread.Sleep(1000)
            End While
            swInfo.WriteLine("exit")
            pipeServer.Disconnect()
            srInfo.Close()
            'swInfo.Close()
        Catch ex As Exception
            Dim h As New String("")
        End Try
        pipeServer.Close()
    End Sub

End Class
