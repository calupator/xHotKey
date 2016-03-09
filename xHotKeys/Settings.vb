
Imports System.Xml.XPath
Imports System.Xml

Public Class Settings
    Shared FilePath As String

    Private Sub New()
    End Sub

    Public Shared Sub File(ByVal file As String)
        FilePath = file
    End Sub

    Public Shared Function LoadHK(ByVal hwnd As IntPtr) As Dictionary(Of HotKey, Integer)
        Dim xmldoc As New XmlDocument()
        xmldoc.Load(FilePath)
        Dim xmlList As XmlNodeList = xmldoc.DocumentElement.ChildNodes

        Dim HKeys As New Dictionary(Of HotKey, Integer)
        For Each nodeOrder As XmlNode In xmlList
            Dim Hkey As New HotKey(hwnd)
            With Hkey
                .Key = nodeOrder.Attributes("Key").Value
                .Command = nodeOrder.Attributes("Command").Value
                .Modifier = nodeOrder.Attributes("Modifier").Value
                .Argument = nodeOrder.Attributes("Argument").Value
                .WorkingDir = nodeOrder.Attributes("WorkingDir").Value
                .WindowStyle = nodeOrder.Attributes("WindowStyle").Value
                .NewInstance = nodeOrder.Attributes("NewInstance").Value
                .Priority = nodeOrder.Attributes("Priority").Value
            End With
            HKeys.Add(Hkey, Hkey.GetID)
        Next
        Return HKeys
    End Function

    Public Shared Sub SaveHK(ByVal HKeys As Dictionary(Of HotKey, Integer))
        Dim xDoc As New XmlTextWriter(FilePath, System.Text.Encoding.GetEncoding(1251))
        xDoc.WriteStartDocument()
        xDoc.Formatting = System.Xml.Formatting.Indented
        xDoc.Indentation = 2
        xDoc.WriteStartElement("HotKeys")
        For Each it As KeyValuePair(Of HotKey, Integer) In HKeys
            xDoc.WriteStartElement("HotKey")
            xDoc.WriteAttributeString("Key", it.Key.Key)
            xDoc.WriteAttributeString("Modifier", it.Key.Modifier)
            xDoc.WriteAttributeString("Command", it.Key.Command)
            xDoc.WriteAttributeString("Argument", it.Key.Argument)
            xDoc.WriteAttributeString("WorkingDir", it.Key.WorkingDir)
            xDoc.WriteAttributeString("WindowStyle", it.Key.WindowStyle)
            xDoc.WriteAttributeString("NewInstance", it.Key.NewInstance)
            xDoc.WriteAttributeString("Priority", it.Key.Priority)
            xDoc.WriteEndElement()

        Next
        xDoc.WriteEndElement()
        xDoc.Flush()
        xDoc.Close()

    End Sub

End Class
