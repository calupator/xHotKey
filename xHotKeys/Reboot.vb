Imports System.Runtime.InteropServices

Friend Class Reboot
    'импортируем API функцию InitiateSystemShutdown
    <DllImport("advapi32.dll", EntryPoint:="InitiateSystemShutdownEx")> _
    Shared Function InitiateSystemShutdown(ByVal lpMachineName As String, ByVal lpMessage As String, ByVal dwTimeout As Integer, ByVal bForceAppsClosed As Boolean, ByVal bRebootAfterShutdown As Boolean) As Integer
    End Function
    'импортируем API функцию AdjustTokenPrivileges
    <DllImport("advapi32.dll", ExactSpelling:=True, SetLastError:=True)> _
    Friend Shared Function AdjustTokenPrivileges(ByVal htok As IntPtr, ByVal disall As Boolean, ByRef newst As TokPriv1Luid, ByVal len As Integer, ByVal prev As IntPtr, ByVal relen As IntPtr) As Boolean
    End Function
    'импортируем API функцию GetCurrentProcess
    <DllImport("kernel32.dll", ExactSpelling:=True)> _
    Friend Shared Function GetCurrentProcess() As IntPtr
    End Function
    'импортируем API функцию OpenProcessToken
    <DllImport("advapi32.dll", ExactSpelling:=True, SetLastError:=True)> _
    Friend Shared Function OpenProcessToken(ByVal h As IntPtr, ByVal acc As Integer, ByRef phtok As IntPtr) As Boolean
    End Function
    'импортируем API функцию LookupPrivilegeValue
    <DllImport("advapi32.dll", SetLastError:=True)> _
    Friend Shared Function LookupPrivilegeValue(ByVal host As String, ByVal name As String, ByRef pluid As Long) As Boolean
    End Function
    'импортируем API функцию LockWorkStation
    <DllImport("user32.dll", EntryPoint:="LockWorkStation")> _
    Shared Function LockWorkStation() As Boolean
    End Function

    'объявляем структуру TokPriv1Luid для работы с привилегиями
    <StructLayout(LayoutKind.Sequential, Pack:=1)> _
    Friend Structure TokPriv1Luid
        Public Count As Integer
        Public Luid As Long
        Public Attr As Integer
    End Structure

    'объявляем необходимые, для API функций, константые значения, согласно MSDN
    Friend Const SE_PRIVILEGE_ENABLED As Integer = &H2
    Friend Const TOKEN_QUERY As Integer = &H8
    Friend Const TOKEN_ADJUST_PRIVILEGES As Integer = &H20
    Friend Const SE_SHUTDOWN_NAME As String = "SeShutdownPrivilege"

    'функция SetPriv для повышения привилегий процесса
    Private Shared Sub SetPriv()
        Dim tkp As TokPriv1Luid 'экземпляр структуры TokPriv1Luid
        Dim htok As IntPtr = IntPtr.Zero
        'открываем "интерфейс" доступа для своего процесса
        If OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES Or TOKEN_QUERY, htok) Then
            'заполняем поля структуры
            tkp.Count = 1
            tkp.Attr = SE_PRIVILEGE_ENABLED
            tkp.Luid = 0
            'получаем системный идентификатор необходимой нам привилегии
            LookupPrivilegeValue(Nothing, SE_SHUTDOWN_NAME, tkp.Luid)
            'повышем привилигеию своему процессу
            AdjustTokenPrivileges(htok, False, tkp, 0, IntPtr.Zero, IntPtr.Zero)
        End If
    End Sub

    'публичный метод для перезагрузки/выключения машины
    Public Shared Function halt(ByVal RSh As Boolean, ByVal Force As Boolean) As Integer
        SetPriv() 'получаем привилегия
        'вызываем функцию InitiateSystemShutdown, передавая ей необходимые параметры
        Return InitiateSystemShutdown(Nothing, Nothing, 0, Force, RSh)
    End Function

    'публичный метод для блокировки операционной системы
    Public Shared Function Lock() As Integer
        If LockWorkStation() Then
            Return 1
        Else
            Return 0
        End If
    End Function
End Class