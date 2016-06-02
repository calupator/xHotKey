<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Main
    Inherits System.Windows.Forms.Form

    'Форма переопределяет dispose для очистки списка компонентов.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Является обязательной для конструктора форм Windows Forms
    Private components As System.ComponentModel.IContainer

    'Примечание: следующая процедура является обязательной для конструктора форм Windows Forms
    'Для ее изменения используйте конструктор форм Windows Form.  
    'Не изменяйте ее в редакторе исходного кода.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Main))
        Me.tbMaster = New System.Windows.Forms.TrackBar
        Me.TrayIcon = New System.Windows.Forms.NotifyIcon(Me.components)
        Me.txtHotKey = New xHotKeys.WinHotKey
        Me.ComboBox1 = New System.Windows.Forms.ComboBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.TextBox2 = New System.Windows.Forms.TextBox
        Me.Button1 = New System.Windows.Forms.Button
        CType(Me.tbMaster, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'tbMaster
        '
        Me.tbMaster.LargeChange = 20
        Me.tbMaster.Location = New System.Drawing.Point(433, 12)
        Me.tbMaster.Maximum = 100
        Me.tbMaster.Name = "tbMaster"
        Me.tbMaster.Orientation = System.Windows.Forms.Orientation.Vertical
        Me.tbMaster.Size = New System.Drawing.Size(45, 225)
        Me.tbMaster.SmallChange = 5
        Me.tbMaster.TabIndex = 2
        Me.tbMaster.TickFrequency = 10
        Me.tbMaster.TickStyle = System.Windows.Forms.TickStyle.Both
        '
        'TrayIcon
        '
        Me.TrayIcon.Text = "NotifyIcon1"
        Me.TrayIcon.Visible = True

        'txtHotKey
        '
        Me.txtHotKey.Location = New System.Drawing.Point(266, 289)
        Me.txtHotKey.Name = "txtHotKey"
        Me.txtHotKey.Size = New System.Drawing.Size(185, 20)
        Me.txtHotKey.TabIndex = 3
        Me.txtHotKey.Text = "Ctrl + R"
        '
        Me.ComboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBox1.FormattingEnabled = True
        Me.ComboBox1.Location = New System.Drawing.Point(51, 208)
        Me.ComboBox1.Name = "ComboBox1"
        Me.ComboBox1.Size = New System.Drawing.Size(195, 21)
        Me.ComboBox1.TabIndex = 4
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(252, 211)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(39, 13)
        Me.Label1.TabIndex = 5
        Me.Label1.Text = "Label1"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(24, 27)
        Me.TextBox2.Multiline = True
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox2.Size = New System.Drawing.Size(242, 134)
        Me.TextBox2.TabIndex = 6
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(49, 271)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(124, 30)
        Me.Button1.TabIndex = 7
        Me.Button1.Text = "Button1"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Main
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(490, 361)
        Me.Controls.Add(Me.txtHotKey)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.TextBox2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.ComboBox1)
        Me.Controls.Add(Me.tbMaster)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "Main"
        Me.Text = "xHotKeys"
        CType(Me.tbMaster, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents tbMaster As System.Windows.Forms.TrackBar
    Friend WithEvents TrayIcon As System.Windows.Forms.NotifyIcon
    Friend WithEvents ComboBox1 As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
#If DEBUG Then
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents txtHotKey As xHotKeys.WinHotKey
    Friend WithEvents Button1 As System.Windows.Forms.Button
#Else
    Friend WithEvents TextBox1 As WinHotKey
#End If

End Class
