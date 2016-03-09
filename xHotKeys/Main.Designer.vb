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
        CType(Me.tbMaster, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'tbMaster
        '
        Me.tbMaster.LargeChange = 20
        Me.tbMaster.Location = New System.Drawing.Point(120, 25)
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
        '
        'Main
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(284, 262)
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

End Class
