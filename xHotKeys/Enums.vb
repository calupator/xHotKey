
Public Enum Modifiers
    None = 0
    Alt = 1
    Control = 2
    Shift = 4
    Windows = 8
End Enum

Enum WindowState
    '''<summary>Minimizes the window.</summary>
    Minimize = &HF020 ' SC_MINIMIZE

    '''<summary>Maximizes the window.</summary>
    Maximize = &HF030 ' SC_MAXIMIZE

    '''<summary>Restores the window to its normal position and size.</summary>
    Restore = &HF120 ' SC_RESTORE
    Normal = &HF120 ' SC_RESTORE
End Enum