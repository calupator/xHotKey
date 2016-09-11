Namespace Enums

    Public Enum Modifiers
        None = 0
        Alt = 1
        Control = 2
        Shift = 4
        Windows = 8
    End Enum

    Public Enum WindowState
        '''<summary>Normalizes the window.</summary>
        Normal = 0
        '''<summary>Minimizes the window.</summary>
        Minimize
        '''<summary>Maximizes the window.</summary>
        Maximize
    End Enum

    Public Enum Command ' Вид системной команды
        None
        VolUp
        VolDown
    End Enum

    Public Enum EventType As Integer ' Тип вызвавшего события
        ''' <summary>Событие типа HotKey</summary>
        ''' <remarks></remarks>
        HotKeys
        ''' <summary>Событие типа RemoteControl</summary>
        ''' <remarks></remarks>
        RemoteControl
    End Enum

End Namespace