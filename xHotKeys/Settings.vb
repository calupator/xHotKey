
Imports System.Xml.XPath
Imports System.Xml

Public Class Settings
    Shared FilePath As String

    Private Sub New()
    End Sub

    Public Shared Sub File(ByVal file As String)
        FilePath = file
    End Sub

    Public Shared Function LoadHK(ByVal hwnd As IntPtr) As Dictionary(Of Integer, HotKey)
        Dim xmldoc As New XmlDocument()
        xmldoc.Load(FilePath)
        Dim xmlList As XmlNodeList = xmldoc.DocumentElement.ChildNodes

        Dim HKeys As New Dictionary(Of Integer, HotKey)
        For Each nodeOrder As XmlNode In xmlList
            'Dim Hkey As New HotKey(hwnd)
            Dim Hkey As New HotKey()
            With Hkey
                .Name = nodeOrder.Attributes("Name").Value
                .Key = nodeOrder.Attributes("Key").Value
                .Modifier = nodeOrder.Attributes("Modifier").Value
                .Sound = nodeOrder.Attributes("Sound").Value
                .Command = CInt(nodeOrder.Attributes("Command").Value)
                If .Command = 0 Then
                    .Path = nodeOrder.Attributes("Path").Value
                    .Argument = nodeOrder.Attributes("Argument").Value
                    .WorkingDir = nodeOrder.Attributes("WorkingDir").Value
                    .WindowStyle = CType(nodeOrder.Attributes("WindowStyle").Value, WindowState)
                    .Priority = nodeOrder.Attributes("Priority").Value
                    .NewInstance = nodeOrder.Attributes("NewInstance").Value
                End If
            End With
            Dim present As Boolean = False
            For Each it As KeyValuePair(Of Integer, HotKey) In HKeys
                If it.Value = Hkey Then
                    present = True
                    Exit For
                End If
            Next
            If Not present Then HKeys.Add(Hkey.GetID, Hkey)
        Next
        Return HKeys
    End Function

    Public Shared Sub SaveHK(ByVal HKeys As Dictionary(Of Integer, HotKey))
        Dim xDoc As New XmlTextWriter(FilePath, System.Text.Encoding.GetEncoding(1251))
        xDoc.WriteStartDocument()
        xDoc.Formatting = System.Xml.Formatting.Indented
        xDoc.Indentation = 2
        xDoc.WriteStartElement("HotKeys")
        For Each it As KeyValuePair(Of Integer, HotKey) In HKeys
            xDoc.WriteStartElement("HotKey")
            xDoc.WriteAttributeString("Name", it.Value.Name)
            xDoc.WriteAttributeString("Key", it.Value.Key)
            xDoc.WriteAttributeString("Modifier", it.Value.Modifier)
            xDoc.WriteAttributeString("Sound", it.Value.Sound)
            xDoc.WriteAttributeString("Command", it.Value.Command)
            If it.Value.Command = 0 Then
                xDoc.WriteAttributeString("Path", it.Value.Path)
                xDoc.WriteAttributeString("Argument", it.Value.Argument)
                xDoc.WriteAttributeString("WorkingDir", it.Value.WorkingDir)
                xDoc.WriteAttributeString("WindowStyle", it.Value.WindowStyle)
                xDoc.WriteAttributeString("Priority", it.Value.Priority)
                xDoc.WriteAttributeString("NewInstance", it.Value.NewInstance)
            End If
            xDoc.WriteEndElement()
        Next
        xDoc.WriteEndElement()
        xDoc.Flush()
        xDoc.Close()
    End Sub

End Class
