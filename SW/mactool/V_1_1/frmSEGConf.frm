VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmSEGConf 
   BorderStyle     =   1  '단일 고정
   Caption         =   "MAC TOOL - WIZ200Web"
   ClientHeight    =   6090
   ClientLeft      =   2535
   ClientTop       =   3240
   ClientWidth     =   10185
   BeginProperty Font 
      Name            =   "Courier New"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmSEGConf.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   406
   ScaleMode       =   3  '픽셀
   ScaleWidth      =   679
   Begin VB.Frame Frame2 
      Caption         =   "Setting MAC"
      Height          =   855
      Left            =   2880
      TabIndex        =   16
      Top             =   600
      Width           =   7095
      Begin VB.TextBox txtMAC 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         Height          =   360
         Left            =   1560
         MaxLength       =   17
         TabIndex        =   18
         Top             =   360
         Width           =   2760
      End
      Begin VB.CheckBox chkAutoInc 
         Appearance      =   0  '평면
         Caption         =   "Auto Increment"
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   4680
         TabIndex        =   17
         Top             =   360
         Value           =   1  '확인
         Width           =   2055
      End
      Begin VB.Label Label2 
         Caption         =   "Address"
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   360
         Width           =   975
      End
   End
   Begin MSWinsockLib.Winsock WinsockDirect 
      Left            =   11400
      Top             =   1200
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Timer TimerWait 
      Enabled         =   0   'False
      Left            =   11160
      Top             =   120
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  '아래 맞춤
      Height          =   330
      Left            =   0
      TabIndex        =   12
      Top             =   5760
      Width           =   10185
      _ExtentX        =   17965
      _ExtentY        =   582
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   2
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   15346
            Key             =   "Normal"
            Object.ToolTipText     =   "Normal"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Text            =   "BIXOLON"
            TextSave        =   "BIXOLON"
            Key             =   "CurrentTime"
            Object.ToolTipText     =   "CurrentTime"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlListView 
      Left            =   11280
      Top             =   3240
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   1
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":0E42
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog OpenLog 
      Left            =   11400
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.TextBox txtVersion 
      Alignment       =   2  '가운데 맞춤
      Appearance      =   0  '평면
      Enabled         =   0   'False
      Height          =   375
      Left            =   8640
      MaxLength       =   15
      TabIndex        =   10
      Top             =   3960
      Width           =   1080
   End
   Begin VB.Frame Frame1 
      Caption         =   "Network parameters"
      ForeColor       =   &H8000000D&
      Height          =   1575
      Left            =   2880
      TabIndex        =   6
      Top             =   1920
      Width           =   7095
      Begin VB.TextBox txtIP 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         Enabled         =   0   'False
         Height          =   360
         Left            =   1560
         MaxLength       =   15
         TabIndex        =   3
         Top             =   480
         Width           =   2040
      End
      Begin VB.TextBox txtSubnet 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         Enabled         =   0   'False
         Height          =   360
         Left            =   1560
         MaxLength       =   15
         TabIndex        =   4
         Top             =   960
         Width           =   2040
      End
      Begin VB.TextBox txtGW 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         Enabled         =   0   'False
         Height          =   360
         Left            =   4680
         MaxLength       =   15
         TabIndex        =   5
         Top             =   480
         Width           =   2040
      End
      Begin VB.Label Label1 
         Caption         =   "IP Address"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   480
         Width           =   1335
      End
      Begin VB.Label Label3 
         Caption         =   "Subnet Mask"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label4 
         Caption         =   "Gateway"
         Height          =   255
         Left            =   3720
         TabIndex        =   7
         Top             =   480
         Width           =   975
      End
   End
   Begin VB.Frame frameBar 
      BorderStyle     =   0  '없음
      Height          =   975
      Left            =   240
      TabIndex        =   0
      Top             =   4680
      Width           =   9735
      Begin VB.PictureBox frameProgress 
         Appearance      =   0  '평면
         BackColor       =   &H00FFFFFF&
         ForeColor       =   &H80000008&
         Height          =   495
         Left            =   7080
         ScaleHeight     =   465
         ScaleWidth      =   2505
         TabIndex        =   13
         Top             =   240
         Width           =   2535
         Begin MSComctlLib.ProgressBar ProgressFile 
            Height          =   255
            Left            =   120
            TabIndex        =   14
            ToolTipText     =   "Transfer File Progress Bar"
            Top             =   120
            Width           =   2295
            _ExtentX        =   4048
            _ExtentY        =   450
            _Version        =   393216
            Appearance      =   0
            Scrolling       =   1
         End
      End
      Begin MSComctlLib.Toolbar Toolbar1 
         Height          =   765
         Left            =   3600
         TabIndex        =   1
         Top             =   120
         Width           =   2775
         _ExtentX        =   4895
         _ExtentY        =   1349
         ButtonWidth     =   1561
         ButtonHeight    =   1349
         AllowCustomize  =   0   'False
         Style           =   1
         ImageList       =   "imlToolbarIcons"
         _Version        =   393216
         BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
            NumButtons      =   3
            BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Caption         =   "Search   "
               Key             =   "SearchBoard"
               Object.ToolTipText     =   "Search Board"
               ImageIndex      =   1
            EndProperty
            BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Caption         =   "Setting"
               Key             =   "SettingBoard"
               Object.ToolTipText     =   "Setting Board Information"
               ImageIndex      =   2
            EndProperty
            BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Caption         =   "Exit"
               Key             =   "Exit"
               Object.ToolTipText     =   "Exit"
               ImageIndex      =   4
            EndProperty
         EndProperty
      End
      Begin MSComCtl2.Animation Animation1 
         Height          =   375
         Left            =   0
         TabIndex        =   15
         Top             =   240
         Visible         =   0   'False
         Width           =   2535
         _ExtentX        =   4471
         _ExtentY        =   661
         _Version        =   393216
         Center          =   -1  'True
         FullWidth       =   169
         FullHeight      =   25
      End
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   11400
      Top             =   2400
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":171C
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":1FF6
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":28D0
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":31AA
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSWinsockLib.Winsock WinsockUDP 
      Left            =   11520
      Top             =   1800
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      Protocol        =   1
   End
   Begin MSComctlLib.ListView ListBoards 
      Height          =   3975
      Left            =   240
      TabIndex        =   2
      Top             =   360
      Width           =   2535
      _ExtentX        =   4471
      _ExtentY        =   7011
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      FlatScrollBar   =   -1  'True
      FullRowSelect   =   -1  'True
      _Version        =   393217
      SmallIcons      =   "imlListView"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   0
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin MSWinsockLib.Winsock winsockUP 
      Left            =   11400
      Top             =   360
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label5 
      Alignment       =   2  '가운데 맞춤
      Caption         =   "Firmware Version"
      Height          =   255
      Left            =   6360
      TabIndex        =   11
      Top             =   4080
      Width           =   2055
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File(&F)"
      Begin VB.Menu mnuExit 
         Caption         =   "Exit(&X)"
      End
   End
   Begin VB.Menu mnuAction 
      Caption         =   "Action(&A)"
      Begin VB.Menu mnuSearchBoard 
         Caption         =   "Search Board(&S)"
      End
      Begin VB.Menu mnuSettingBoard 
         Caption         =   "Setting(&T)"
      End
   End
End
Attribute VB_Name = "frmSEGConf"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Const CONFIG_RPORT = 48713
Const CONFIG_LPORT = 48714

Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal length As Long)
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

' Board configuration data type
Private Type typeBoardInfo
    op(0 To 3) As Byte
    ver(0 To 1) As Byte
    mac(0 To 5) As Byte
    ip(0 To 3) As Byte
    subnet(0 To 3) As Byte
    gw(0 To 3) As Byte
    dhcp As Byte
    myMac(0 To 5) As Byte
End Type

' Tool's mode
Private Enum typeToolMode
    None = 0
    Searching = 1
    Setting = 2
End Enum
Dim ToolMode As typeToolMode

' Total count of Boards
Dim intBoardNum As Integer
' Collection of Board's configuration data.
Dim colBoards As New Collection

' Selected Board's infomation
Dim BoardKey As String
Dim BoardInfo As typeBoardInfo
Dim bSelect As Boolean

' Selected Firmware file for uploading
Dim strUploadFile As String


'new field: myMac - save the old mac address
Private myMac(0 To 5) As Byte

Sub MessageBox(msg As String)
        
    Call MsgBox(msg, vbInformation Or vbMsgBoxSetForeground, "Information")
    
End Sub
Public Function Exists(col, index) As Boolean
On Error GoTo ExistsTryNonObject
    Dim o As Object
 
    Set o = col(index)
    Exists = True
    Exit Function
 
ExistsTryNonObject:
    Exists = ExistsNonObject(col, index)
End Function
Private Function ExistsNonObject(col, index) As Boolean
On Error GoTo ExistsNonObjectErrorHandler
    Dim v As Variant
 
    v = col(index)
    ExistsNonObject = True
    Exit Function
 
ExistsNonObjectErrorHandler:
    ExistsNonObject = False
End Function

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : BoardAdd
' Parameter : newStr() is string of board's configuration data
'
' Add Board with receiving new board's configuration data
' save total count of boards to "intBoardNum" variable.
' save configuration data to "colBoards" collection
'
''''''''''''''''''''''''''''''''''''''''''''''''
Sub BoardAdd(newStr() As Byte)
'On Error GoTo e_go

    Dim mac As String
    Dim i As Integer
    
    ' making mac address string key
    ' ex) 00:44:34:EA:3A:F0
    mac = ""
    For i = 6 To 11
        If Len(Hex(newStr(i))) = 1 Then
            mac = mac & "0" & Hex(newStr(i)) & ":"
        Else
            mac = mac & Hex(newStr(i)) & ":"
        End If
    Next i
    
    mac = Left(mac, Len(mac) - 1)
    If colBoards.Count > 0 Then
        If Exists(colBoards, mac) Then
            Exit Sub
        End If
        
    End If
    
    ' Add Board entity by using mac .
   
    colBoards.Add Item:=newStr, Key:=mac
    
    
    
    ' add list view
    frmSEGConf.ListBoards.ListItems.Add intBoardNum, mac, mac
    frmSEGConf.ListBoards.ListItems.Item(intBoardNum).SmallIcon = 1
            
    ' Automatically select the first row of ListView
    If intBoardNum = 1 Then
        ListBoards_ItemClick ListBoards.ListItems(1)
        ListBoards.ListItems(1).Selected = True
        'frmSEGConf.ListBoards.SetFocus
    End If
    
    intBoardNum = intBoardNum + 1
e_go:
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : BoardUpdate
' Parameter : newStr() is string of board's configuration data
'
' Update Board's configuration data with receiving data
' delete previous data
' add new board's data
'
''''''''''''''''''''''''''''''''''''''''''''''''
Sub BoardUpdate(newStr() As Byte)
On Error GoTo U_ERROR

    Dim newInfo() As Byte
    ReDim newInfo(0 To Len(BoardInfo) - 1) As Byte
    Dim tmpStrA() As String
    Dim tmpStr As String
    Dim tmplong As Long
    Dim tmpByte As Byte
    Dim i As Integer
    Dim j As Integer
    Dim mac As String
    
    ' Verify message
    If newStr(6) = BoardInfo.mac(0) And _
        newStr(7) = BoardInfo.mac(1) And _
        newStr(8) = BoardInfo.mac(2) And _
        newStr(9) = BoardInfo.mac(3) And _
        newStr(10) = BoardInfo.mac(4) And _
        newStr(11) = BoardInfo.mac(5) Then
        
        ' Update the item
        colBoards.Remove BoardKey
        CopyMemory newInfo(0), BoardInfo, Len(BoardInfo)
        colBoards.Add newInfo, BoardKey
        ToolMode = None
        
        Sleep (2000)
        Call MessageBox("Complete setting the MAC  ")
        
        Call mnuSearchBoard_Click
        
        'store mac to file
        Open "mac.txt" For Append As #1
        Print #1, txtMAC.Text & Chr(9) & Date & Chr(9) & Time
        Close #1
        
        'if checked chkAutoInc then increase MAC address in txtMAC
        If chkAutoInc.Value = 1 Then
            tmpStrA = Split(txtMAC.Text, ":")
            tmpStr = "&H" & tmpStrA(3) & tmpStrA(4) & tmpStrA(5)
            tmplong = CLng(tmpStr)
            
            If tmplong >= &HFFFFFF Then
                Call MessageBox("Exceed MAC")
                tmplong = -1
            End If
            
            tmplong = tmplong + 1
            
            tmpStr = Hex(tmplong)
            
            j = 6 - Len(tmpStr)
            
            For i = 1 To j
                tmpStr = "0" & tmpStr
            Next i
            
            tmpStrA(3) = Left(tmpStr, 2)
            tmpStrA(4) = Mid(tmpStr, 3, 2)
            tmpStrA(5) = Right(tmpStr, 2)
            
            For i = 0 To 5
                mac = mac & tmpStrA(i) & ":"
            Next i
            
            mac = Left(mac, 17)
            
            txtMAC.Text = mac
            
        End If
    End If

U_ERROR:
    Erase newInfo
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : BoardRemove
' Parameter : None
'
' Delete all Board's data from "colBoards" collection
' Board's ListBox clears
' "intBoardNum" variable sets '0'
'
''''''''''''''''''''''''''''''''''''''''''''''''
Sub BoardRemove()

    Dim num As Integer
    
    ' Set false the flag, board select
    bSelect = False
    
    ' Delete All Board information
    For num = 1 To ListBoards.ListItems.Count

        colBoards.Remove ListBoards.ListItems(num).Key

    Next num
    
    'Clear listbox
    ListBoards.ListItems.Clear
  
    'Clear board's count
    intBoardNum = 1
    
End Sub



''''''''''''''''''''''''''''''''''''''''''''''''
' Name : Form_Load
' Parameter : None
'
' Initialize control, variable, position
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()
    Me.Caption = Me.Caption & " Ver" & App.Major & "." & App.Minor
    Dim colX As ColumnHeader
    Dim intX As Integer
    Dim tmpfromfile As String
    Dim filelength As Long
    Dim tmpfilelength As Long
    
    Dim tmpStrA() As String
    Dim tmpStr As String
    Dim tmplong As Long
    Dim i As Integer
    Dim j As Integer
    
    Set colX = ListBoards.ColumnHeaders.Add()
    colX.Text = "Board list"
    colX.Width = ListBoards.Width
    
    WinsockUDP.RemoteHost = "255.255.255.255"
    'WinsockUDP.RemotePort = 48723
    'WinsockUDP.LocalPort = 48724
    
    WinsockUDP.RemotePort = CONFIG_RPORT
    WinsockUDP.LocalPort = CONFIG_LPORT
    WinsockUDP.Bind
    
    bSelect = False
    
    TimerWait.Enabled = False
    Animation1.Open ("progress.avi")
    frameProgress.Visible = False
    
    ToolMode = None
    
    If Dir("mac.txt") <> "" Then
        Open "mac.txt" For Input As #1
        filelength = FileLen("mac.txt")
        Do While (tmpfilelength < filelength)
            Line Input #1, tmpfromfile
            tmpfilelength = Seek(1)
        Loop
        'Line Input #1, macfromfile
    Else
        Open "mac.txt" For Output As #1
    End If
    Close #1

    tmpfromfile = Left(tmpfromfile, 17)
            
            tmpStrA = Split(tmpfromfile, ":")
            tmpStr = "&H" & tmpStrA(3) & tmpStrA(4) & tmpStrA(5)
            tmplong = CLng(tmpStr)
            
            If tmplong >= &HFFFFFF Then
                Call MessageBox("Exceed MAC")
                tmplong = -1
            End If
            
            tmplong = tmplong + 1
            
            tmpStr = Hex(tmplong)
            
            j = 6 - Len(tmpStr)
            
            For i = 1 To j
                tmpStr = "0" & tmpStr
            Next i
            
            tmpStrA(3) = Left(tmpStr, 2)
            tmpStrA(4) = Mid(tmpStr, 3, 2)
            tmpStrA(5) = Right(tmpStr, 2)
            
            tmpfromfile = ""
            For i = 0 To 5
                tmpfromfile = tmpfromfile & tmpStrA(i) & ":"
            Next i
            
    txtMAC.Text = Left(tmpfromfile, 17)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub



''''''''''''''''''''''''''''''''''''''''''''''''
' Name : mnuSearchBoard_Click
' Parameter : None
'
' Search available Boards.
' Send "FIND" message
' Waiting Board's reply
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuSearchBoard_Click()
    
    Dim sendD() As Byte
    
    Animation1.Visible = True
    ' First, delete all board's information
    Call BoardRemove

    ToolMode = Searching
    ' Send FIND message
    ReDim sendD(0 To 3) As Byte
    sendD(0) = Asc("F")
    sendD(1) = Asc("I")
    sendD(2) = Asc("N")
    sendD(3) = Asc("D")
    WinsockUDP.RemoteHost = "255.255.255.255"
    WinsockUDP.RemotePort = CONFIG_RPORT
    WinsockUDP.SendData sendD
    Erase sendD

    
    Call StartTimer("Searching now ... ", 500)
    

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : mnuSettingBoard_Click
' Parameter : None
'
' Update the selected Board's configuration data.
' Make message with new configuration data.
' Send "SETT" message
' Waiting Board's reply
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuSettingBoard_Click()
On Error GoTo s_ERROR

    Dim sendD() As Byte
    Dim tmpStr() As String
    Dim ii As Integer
    
    ' If exist selected board ,
    If bSelect Then
                
        For ii = 0 To 3
            'BoardInfo.ip(ii) = 0        ' IP address : 0.0.0.0  means MAC setting
        Next ii
        
        tmpStr = Split(txtMAC.Text, ":")
        If UBound(tmpStr) <> 5 Then
            Call MessageBox("Invalid MAC.")
            txtMAC.SetFocus
            Exit Sub
        End If
        For ii = 0 To 5
            If tmpStr(ii) = "" Or (Val("&H" & tmpStr(ii)) > 255) Or (Val("&H" & tmpStr(ii)) < 0) Then
                Call MessageBox("Invalid MAC.")
                txtMAC.SetFocus
                Exit Sub
            End If
            BoardInfo.mac(ii) = CByte("&H" & tmpStr(ii))
            'old mac
            BoardInfo.myMac(ii) = myMac(ii)

        Next ii
        
        
        tmpStr = Split(txtSubnet.Text, ".")
        If UBound(tmpStr) <> 3 Then
            Call MessageBox("Invalid Subnet Mask.")
            txtSubnet.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpStr(ii) = "" Or CInt(tmpStr(ii)) > 255 Or CInt(tmpStr(ii)) < 0 Then
                Call MessageBox("Invalid Subnet Mask.")
                txtSubnet.SetFocus
                Exit Sub
            End If
            BoardInfo.subnet(ii) = CByte(tmpStr(ii))
        Next ii
    
        tmpStr = Split(txtGW.Text, ".")
        If UBound(tmpStr) <> 3 Then
            Call MessageBox("Invalid Gateway Address.")
            txtGW.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpStr(ii) = "" Or CInt(tmpStr(ii)) > 255 Or CInt(tmpStr(ii)) < 0 Then
                Call MessageBox("Invalid Gateway Address.")
                txtGW.SetFocus
                Exit Sub
            End If
            BoardInfo.gw(ii) = CByte(tmpStr(ii))
        Next ii
    
        ToolMode = Setting
                
        ' Sending SETT message
        ReDim sendD(1 To Len(BoardInfo)) As Byte
        BoardInfo.op(0) = Asc("S")
        BoardInfo.op(1) = Asc("E")
        BoardInfo.op(2) = Asc("T")
        BoardInfo.op(3) = Asc("M")
        'BoardInfo.op(3) = Asc("T")
        
        BoardInfo.dhcp = 0
        
        CopyMemory sendD(1), BoardInfo, Len(BoardInfo)
        
        WinsockUDP.RemoteHost = "255.255.255.255"
        WinsockUDP.RemotePort = CONFIG_RPORT
        WinsockUDP.SendData sendD
        Erase sendD
        
        Call StartTimer("Setting now ... ", 500)
    
        
    End If
    Exit Sub
    
s_ERROR:
    Call MessageBox("Invalid parameter's value.")
    
End Sub



Private Sub mnuExit_Click()
    Form_Unload 0
End Sub


Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
    On Error Resume Next
    Select Case Button.Key
        Case "SearchBoard"
            Call mnuSearchBoard_Click
        Case "SettingBoard"
            Call mnuSettingBoard_Click
        Case "Exit"
            Call mnuExit_Click
    End Select
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : ListBoards_ItemClick
' Parameter : Item is string of selected board's key.
'
' Save key string to "BoardKey" variable
' Save configuration data to "BoardInfo" variable.
' Show configuration data of selected Board.
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub ListBoards_ItemClick(ByVal Item As MSComctlLib.ListItem)
Dim dd() As Byte
    Dim i As Integer
    
    bSelect = True
    dd = colBoards.Item(Item.Key)

    
    BoardKey = Item.Key
    CopyMemory BoardInfo, dd(0), Len(BoardInfo)
    
    txtVersion.Text = BoardInfo.ver(0) & "." & BoardInfo.ver(1)
    'If BoardInfo.debugoff = 0 Then
    '    chkDebug.Value = 1
    'Else
    '    chkDebug.Value = 0
    'End If
        
    txtIP.Text = BoardInfo.ip(0) & "." & BoardInfo.ip(1) & "." & BoardInfo.ip(2) & "." & BoardInfo.ip(3)
    txtSubnet.Text = BoardInfo.subnet(0) & "." & BoardInfo.subnet(1) & "." & BoardInfo.subnet(2) & "." & BoardInfo.subnet(3)
    txtGW.Text = BoardInfo.gw(0) & "." & BoardInfo.gw(1) & "." & BoardInfo.gw(2) & "." & BoardInfo.gw(3)

    'new myMac field
    For i = 0 To 5
        myMac(i) = BoardInfo.mac(i)
    Next i
    Erase dd
    
End Sub


''''''''''''''''''''''''''''''''''''''''''''''''
' Name : WinsockUDP_DataArrival
' Parameter : bytesTotal is count of receiving data from "WinsockUDP" control
'
' Receive configuration message.
' "IMIN" message => BoardAdd
' "SETC" message => BoardUpdate
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub WinsockUDP_DataArrival(ByVal bytesTotal As Long)


    Dim getboard(23) As Byte
    
    ReDim getd(0 To bytesTotal - 1) As Byte
    
    WinsockUDP.GetData getd, vbByte, bytesTotal
    
    CopyMemory getboard(0), getd(0), 24
        
    If (getboard(0) = Asc("f")) And (getboard(1) = Asc("i")) And (getboard(2) = Asc("n")) And (getboard(3) = Asc("d")) Then
        If ToolMode = Searching Then
            Call BoardAdd(getboard)

        End If
        
    ElseIf (getboard(0) = Asc("s")) And (getboard(1) = Asc("e")) And (getboard(2) = Asc("t")) And (getboard(3) = Asc("t")) Then
        If ToolMode = Setting Then
            'Call StopTimer
            Call BoardUpdate(getboard)

        End If

    End If
    
    Erase getd

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : winsockUP_Connect
' Parameter : None
'
' Ready to uploading firmware
' Open File Open Dialog box for selecting new firmware file.
' Open selected file
' Send all contents of firmware to board
' Wait socket close event from board
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub winsockUP_Connect()
On Error GoTo UP_ERROR

    Dim hSend, BSize, LF&
    Dim sendD() As Byte
    Dim FileSize As Long
'    Dim LastTimeout As Long
'    LastTimeout = 25000 ' Booting delay Time
    
    Call StopTimer
    Me.Enabled = False
    
    hSend = FreeFile
    Open strUploadFile For Binary Access Read As hSend
    
    frameProgress.Visible = True
    FileSize = FileLen(strUploadFile)
    ProgressFile.Max = FileSize
    ProgressFile.Min = 0
    ProgressFile.Value = 0
    
    ReDim sendD(0 To 3) As Byte
    sendD(3) = (FileSize And &HFF000000) / &H1000000
    sendD(2) = (FileSize And &HFF0000) / &H10000
    sendD(1) = (FileSize And &HFF00) / &H100
    sendD(0) = (FileSize And &HFF)
    Sleep (400)                 'booting delay
    winsockUP.SendData sendD
    DoEvents
    Sleep (200)
    Erase sendD
    
    FileSize = 0
    ' read block data as send buf size.
    BSize = 1024
    If winsockUP.State = sckConnected Then
        LF& = LOF(hSend)
        Do Until LF& = Loc(hSend)
            ' until reached EOF
            If LF& - Loc(hSend) < BSize Then
                BSize = LF& - Loc(hSend)
            End If
            ' read data block
            ReDim sendD(0 To BSize - 1) As Byte
            Get hSend, , sendD
            Sleep (400)
            winsockUP.SendData sendD
            DoEvents
            Erase sendD
            DoEvents
            FileSize = FileSize + BSize
            ProgressFile.Value = FileSize
        Loop
    End If
    
    Dim nBar As Integer
    nBar = 0
        
    Call MessageBox("Successfully upload firmware.")
    frameProgress.Visible = False
    Close hSend
    Exit Sub
    
UP_ERROR:
    Close hSend
    frameProgress.Visible = False
    ProgressFile.Value = 0
    ToolMode = None
    Call MessageBox("Firmware uploading error!!" & vbCrLf & vbCrLf & "Retry firmware uploading.")
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''
' Name : winsockUP_Close
' Parameter : None
'
' Complete uploading firmware
' Close uploading socket connection.
' Wait for 10 seconds for board's initialization
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub winsockUP_Close()
    winsockUP.Close
    ToolMode = None
    
    ProgressFile.Value = 0
    Me.Enabled = True
'    Call StartTimer("Waiting board's start-up ... ", 10000)
End Sub

Private Sub winsockUP_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    Call StopTimer
    winsockUP.Close
    ToolMode = None
    Call MessageBox("Firmware uploading error!!" & vbCrLf & vbCrLf & "Retry firmware uploading.")
End Sub

Sub StartTimer(msg As String, intval As Integer)
    TimerWait.Interval = intval
    TimerWait.Enabled = True
    Me.Enabled = False
    StatusBar1.Panels("Normal").Text = "Status : " & msg
    Animation1.Visible = True
    Animation1.Play
End Sub

Sub StopTimer()
    Me.Enabled = True
    TimerWait.Enabled = False
    StatusBar1.Panels("Normal").Text = "Status : Normal"
    Animation1.Play 0, 0, 0
'    Animation1.Stop
    Animation1.Visible = False
End Sub

Private Sub TimerWait_Timer()
    
    Call StopTimer
    
    If ToolMode = Searching Then
        If intBoardNum = 0 Then
            Call MessageBox("No searching result  ")
        End If
    ElseIf ToolMode = Setting Then
        Call MessageBox("Fail to set the board  ")
    End If
    
    ToolMode = None

End Sub


''''''''''''''''''''''''''''''''''''''''''''''''
' Name : TEXT Box filtering
' Parameter : None
'
' Filtering textbox's data
' ex) Port text box support only number
'
''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub txtVersion_KeyPress(KeyAscii As Integer)
    
        KeyAscii = 0

End Sub



Private Sub txtIP_KeyPress(KeyAscii As Integer)
    
    If (KeyAscii = 8) Or (KeyAscii = 46) Or (KeyAscii >= 48 And KeyAscii <= 57) Then
    ' backspace or . or 0~9
    Else
    ' else ignore
        KeyAscii = 0
    End If

End Sub

Private Sub txtDirectIP_KeyPress(KeyAscii As Integer)
    
    If (KeyAscii = 8) Or (KeyAscii = 46) Or (KeyAscii >= 48 And KeyAscii <= 57) Then
    ' backspace or . or 0~9
    Else
    ' else ignore
        KeyAscii = 0
    End If

End Sub


Private Sub txtPort_KeyPress(KeyAscii As Integer)
    
    If (KeyAscii = 8) Or (KeyAscii >= 48 And KeyAscii <= 57) Then
    ' backspace or 0~9
    Else
    ' else ignore
        KeyAscii = 0
    End If

End Sub

