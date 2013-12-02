VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmSEGConf 
   BorderStyle     =   1  '단일 고정
   Caption         =   "WIZ200WEB-Configuration Tool v1.0"
   ClientHeight    =   5070
   ClientLeft      =   2535
   ClientTop       =   3240
   ClientWidth     =   7155
   BeginProperty Font 
      Name            =   "Fixedsys"
      Size            =   12
      Charset         =   129
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmSEGConf.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   338
   ScaleMode       =   3  '픽셀
   ScaleWidth      =   477
   Begin VB.Frame Frame2 
      Height          =   855
      Left            =   3120
      TabIndex        =   16
      Top             =   2640
      Width           =   3855
      Begin VB.CommandButton Command1 
         Appearance      =   0  '평면
         Caption         =   "Web Page Upload"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   1080
         TabIndex        =   18
         Top             =   240
         Width           =   2655
      End
      Begin VB.PictureBox Picture1 
         BorderStyle     =   0  '없음
         Height          =   495
         Left            =   120
         Picture         =   "frmSEGConf.frx":0E42
         ScaleHeight     =   495
         ScaleWidth      =   495
         TabIndex        =   17
         Top             =   240
         Width           =   495
      End
   End
   Begin VB.CheckBox chkDHCP 
      Caption         =   "Using DHCP"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   360
      TabIndex        =   15
      Top             =   3480
      Width           =   1575
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
      Top             =   4740
      Width           =   7155
      _ExtentX        =   12621
      _ExtentY        =   582
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   2
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   10001
            Text            =   "Normal"
            TextSave        =   "Normal"
            Key             =   "Normal"
            Object.ToolTipText     =   "Normal"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Text            =   "WIZ200WEB"
            TextSave        =   "WIZ200WEB"
            Key             =   "CurrentTime"
            Object.ToolTipText     =   "CurrentTime"
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSComctlLib.ImageList imlListView 
      Left            =   0
      Top             =   0
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
            Picture         =   "frmSEGConf.frx":1B0C
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
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   1200
      MaxLength       =   15
      TabIndex        =   10
      Top             =   120
      Width           =   1080
   End
   Begin VB.Frame Frame1 
      Caption         =   "Network Setting"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000D&
      Height          =   2055
      Left            =   3120
      TabIndex        =   6
      Top             =   480
      Width           =   3855
      Begin VB.TextBox txtIP 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   1680
         MaxLength       =   15
         TabIndex        =   3
         Top             =   480
         Width           =   2040
      End
      Begin VB.TextBox txtSubnet 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   1680
         MaxLength       =   15
         TabIndex        =   4
         Top             =   960
         Width           =   2040
      End
      Begin VB.TextBox txtGW 
         Alignment       =   2  '가운데 맞춤
         Appearance      =   0  '평면
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   1680
         MaxLength       =   15
         TabIndex        =   5
         Top             =   1440
         Width           =   2040
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "IP Address"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   135
         TabIndex        =   9
         Top             =   480
         Width           =   1200
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "Subnet Mask"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   135
         TabIndex        =   8
         Top             =   960
         Width           =   1320
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Gateway"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   135
         TabIndex        =   7
         Top             =   1440
         Width           =   840
      End
   End
   Begin VB.Frame frameBar 
      BorderStyle     =   0  '없음
      Height          =   855
      Left            =   120
      TabIndex        =   0
      Top             =   3720
      Width           =   9735
      Begin VB.PictureBox frameProgress 
         Appearance      =   0  '평면
         BackColor       =   &H00FFFFFF&
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   495
         Left            =   120
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
         Left            =   3120
         TabIndex        =   1
         Top             =   0
         Width           =   3615
         _ExtentX        =   6376
         _ExtentY        =   1349
         ButtonWidth     =   1561
         ButtonHeight    =   1349
         AllowCustomize  =   0   'False
         Style           =   1
         ImageList       =   "imlToolbarIcons"
         _Version        =   393216
         BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
            NumButtons      =   4
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
               Caption         =   "Upload"
               Key             =   "Upload"
               Object.ToolTipText     =   "Upload Firmware"
               ImageIndex      =   3
            EndProperty
            BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
               Caption         =   "Exit"
               Key             =   "Exit"
               Object.ToolTipText     =   "Exit"
               ImageIndex      =   4
            EndProperty
         EndProperty
      End
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   600
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   5
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":23E6
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":2CC0
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":359A
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":3E74
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSEGConf.frx":474E
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
      Height          =   2775
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   2535
      _ExtentX        =   4471
      _ExtentY        =   4895
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
      Caption         =   "F/W Ver."
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   11
      Top             =   240
      Width           =   975
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
      Begin VB.Menu munSplit 
         Caption         =   "-"
      End
      Begin VB.Menu mnuUpload 
         Caption         =   "Firmware Upload(&U)"
      End
   End
End
Attribute VB_Name = "frmSEGConf"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Const CONFIG_RPORT = 48713
Const CONFIG_LPORT = 48714
Const CONFIG_UPORT = 48715

Const BUFFER_SIZE = 25
Dim m_UpMode As Integer


Private Type typeBoardInfo
    op(0 To 3) As Byte
    ver(0 To 1) As Byte
    mac(0 To 5) As Byte
    ip(0 To 3) As Byte
    subnet(0 To 3) As Byte
    gw(0 To 3) As Byte
    ' DHCP
    dhcp As Byte
End Type

Private Enum typeToolMode
    None = 0
    Searching = 1
    Setting = 2
    Uploading = 3
End Enum
Dim ToolMode As typeToolMode

Dim intBoardNum As Integer
' Collection of Board's configuration data.
Dim colBoards As New Collection

Dim BoardKey As String
Dim BoardInfo As typeBoardInfo
Dim bSelect As Boolean

' Selected Firmware file for uploading
Dim strUploadFile As String


Sub MessageBox(msg As String)
        
    Call MsgBox(msg, vbInformation Or vbMsgBoxSetForeground, "Information")
    
End Sub

Sub BoardAdd(newStr() As Byte)
On Error GoTo e_go
    DoEvents
    
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
    
    ' Add Board entity by using mac .
    colBoards.Add newStr, mac
    ' add list view
    frmSEGConf.ListBoards.ListItems.Add intBoardNum, mac, mac
    frmSEGConf.ListBoards.ListItems.Item(intBoardNum).SmallIcon = 1
            
    ' Automatically select the first row of ListView
    If intBoardNum = 1 Then
        Call frmSEGConf.ListBoards_FirstRowSelect
        'frmSEGConf.ListBoards.SetFocus
    End If
    
    intBoardNum = intBoardNum + 1

e_go:
End Sub

Sub BoardUpdate(newStr() As Byte)
On Error GoTo U_ERROR

    Dim newInfo() As Byte
    ReDim newInfo(0 To Len(BoardInfo) - 1) As Byte
    
    ' Verify message
    If newStr(6) = BoardInfo.mac(0) And _
        newStr(7) = BoardInfo.mac(1) And _
        newStr(8) = BoardInfo.mac(2) And _
        newStr(9) = BoardInfo.mac(3) And _
        newStr(10) = BoardInfo.mac(4) And _
        newStr(11) = BoardInfo.mac(5) Then
        
        ' Updatae the item
        colBoards.Remove BoardKey
        CopyMemory newInfo(0), BoardInfo, Len(BoardInfo)
        colBoards.Add newInfo, BoardKey
        ToolMode = None
        
        Sleep (500)
        Call MessageBox("Complete setting the board  ")
    End If

U_ERROR:
    Erase newInfo
    
End Sub

Sub BoardRemove()
    
    Dim num As Integer
    
    ' Set false the flag, board select
    bSelect = False
    
    ' Delete All Board information
    If intBoardNum > 1 Then
    For num = 1 To intBoardNum - 1
        colBoards.Remove frmSEGConf.ListBoards.ListItems(num).Key
    Next num
    End If
    
    frmSEGConf.ListBoards.ListItems.Clear
    
    'Clear board's count
    intBoardNum = 1
    
End Sub

Private Sub Command1_Click()
    On Error Resume Next
    
    Dim Ret As Integer      ' Return value
    Dim sendD() As Byte
    Dim tmpstr() As String
    Dim ii As Integer
    
   ' bSelect = True
    
    If bSelect Then
        
        tmpstr = Split(txtIP.Text, ".")
        If UBound(tmpstr) <> 3 Then
            Call MessageBox("Invalid IP Address.")
            txtIP.SetFocus
            Exit Sub
        End If
        
        For ii = 0 To 3
            If tmpstr(ii) = "" Or CInt(tmpstr(ii)) > 255 Or CInt(tmpstr(ii)) < 0 Then
                Call MessageBox("Invalid IP Address.")
                txtIP.SetFocus
                Exit Sub
            End If
        Next ii
        
        ' Select firmware's file
        OpenLog.DialogTitle = "File Select"
        OpenLog.Filter = "Rom File (*.rom)|*.rom|All File (*.*)|*.*"
        Do
            OpenLog.CancelError = True
            OpenLog.FileName = ""
            OpenLog.ShowOpen
            If Err = cdlCancel Then
                Exit Sub
            End If
            
            strUploadFile = OpenLog.FileName
            ' if file not exist, return.
            Ret = Len(Dir$(strUploadFile))
            If Err Then
               Call MessageBox(Error$)
               Exit Sub
            End If
            If Ret Then
               Exit Do
            Else
               Call MessageBox("No existing " + strUploadFile)
            End If
        Loop
        
        ToolMode = Uploading
        m_UpMode = 1
        
        ' Inform board uploading Rom File Image
        ' Send RFUS message
        ReDim sendD(0 To 3) As Byte
        sendD(0) = Asc("R")
        sendD(1) = Asc("F")
        sendD(2) = Asc("U")
        sendD(3) = Asc("P")
        
        WinsockUDP.RemoteHost = "255.255.255.255"
        WinsockUDP.RemotePort = CONFIG_RPORT
        WinsockUDP.SendData sendD
        Sleep (100)
        Erase sendD
                
        ' Establish control socket for firmware uploading
        winsockUP.RemoteHost = txtIP.Text
        winsockUP.RemotePort = CONFIG_UPORT
        winsockUP.Connect   'Call WinsockUP_Connect
        DoEvents
        
    End If
End Sub

Private Sub Form_Load()
Me.Caption = "WIZ200WEB-Configuration Tool Ver" & App.Major & "." & App.Minor
    Dim colX As ColumnHeader
    Dim intX As Integer
    Set colX = ListBoards.ColumnHeaders.Add()
    colX.Text = "Board list"
    colX.Width = ListBoards.Width
    On Error GoTo ER
    WinsockUDP.RemoteHost = "255.255.255.255"
    WinsockUDP.RemotePort = CONFIG_RPORT
    WinsockUDP.LocalPort = CONFIG_LPORT
    WinsockUDP.Bind
    
    bSelect = False
    
    TimerWait.Enabled = False
    frameProgress.Visible = False
    
    ToolMode = None
    m_UpMode = 0
    
    Exit Sub
    
ER:
    MessageBox (Err.Description)
    
    End
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

Private Sub mnuSearchBoard_Click()
    
    Dim sendD() As Byte
    
'    Animation1.Visible = True
    ' First, delete all board's information
    Call BoardRemove
    DoEvents
    
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

Private Sub mnuSettingBoard_Click()
On Error GoTo s_ERROR

    Dim sendD() As Byte
    Dim tmpstr() As String
    Dim ii As Integer
    Dim tmpBytes() As Byte
    
    ' If exist selected board ,
    If bSelect Then
                
        tmpstr = Split(txtIP.Text, ".")
        If UBound(tmpstr) <> 3 Then
            Call MessageBox("Invalid IP Address.")
            txtIP.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpstr(ii) = "" Or CInt(tmpstr(ii)) > 255 Or CInt(tmpstr(ii)) < 0 Then
                Call MessageBox("Invalid IP Address.")
                txtIP.SetFocus
                Exit Sub
            End If
            BoardInfo.ip(ii) = CByte(tmpstr(ii))
        Next ii
        
        tmpstr = Split(txtSubnet.Text, ".")
        If UBound(tmpstr) <> 3 Then
            Call MessageBox("Invalid Subnet Mask.")
            txtSubnet.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpstr(ii) = "" Or CInt(tmpstr(ii)) > 255 Or CInt(tmpstr(ii)) < 0 Then
                Call MessageBox("Invalid Subnet Mask.")
                txtSubnet.SetFocus
                Exit Sub
            End If
            BoardInfo.subnet(ii) = CByte(tmpstr(ii))
        Next ii
    
        tmpstr = Split(txtGW.Text, ".")
        If UBound(tmpstr) <> 3 Then
            Call MessageBox("Invalid Gateway Address.")
            txtGW.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpstr(ii) = "" Or CInt(tmpstr(ii)) > 255 Or CInt(tmpstr(ii)) < 0 Then
                Call MessageBox("Invalid Gateway Address.")
                txtGW.SetFocus
                Exit Sub
            End If
            BoardInfo.gw(ii) = CByte(tmpstr(ii))
        Next ii
    
        ToolMode = Setting
        
        ' DHCP
        If chkDHCP.Value = 1 Then
            BoardInfo.dhcp = 1
        Else
            BoardInfo.dhcp = 0
        End If
                    

        
        ' Sending SETT message
        ReDim sendD(0 To Len(BoardInfo)) As Byte
        BoardInfo.op(0) = Asc("S")
        BoardInfo.op(1) = Asc("E")
        BoardInfo.op(2) = Asc("T")
        BoardInfo.op(3) = Asc("T")
        CopyMemory sendD(0), BoardInfo, Len(BoardInfo)
        
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

Private Sub mnuUpload_Click()
    'On Error Resume Next
    
    Dim Ret As Integer      ' Return value
    Dim sendD() As Byte
    Dim tmpstr() As String
    Dim ii As Integer
    
    If bSelect Then
        
        tmpstr = Split(txtIP.Text, ".")
        If UBound(tmpstr) <> 3 Then
            Call MessageBox("Invalid IP Address.")
            txtIP.SetFocus
            Exit Sub
        End If
        For ii = 0 To 3
            If tmpstr(ii) = "" Or CInt(tmpstr(ii)) > 255 Or CInt(tmpstr(ii)) < 0 Then
                Call MessageBox("Invalid IP Address.")
                txtIP.SetFocus
                Exit Sub
            End If
        Next ii
        
        ' Select firmware's file
        OpenLog.DialogTitle = "File Select"
        OpenLog.Filter = "Bin File (*.bin)|*.bin|All File (*.*)|*.*"
        Do
            OpenLog.CancelError = True
            OpenLog.FileName = ""
            On Error GoTo ER
            
            OpenLog.ShowOpen
ER:
            If Err = cdlCancel Then
                Exit Sub
            End If
            
            strUploadFile = OpenLog.FileName
            ' if file not exist, return.
            Ret = Len(Dir$(strUploadFile))
            If Err Then
               Call MessageBox(Error$)
               Exit Sub
            End If
            If Ret Then
               Exit Do
            Else
               Call MessageBox("No existing " + strUploadFile)
            End If
        Loop
        
        ToolMode = Uploading
        m_UpMode = 0
        
        ' Inform board uploading
        ' Send FWUP message
        ReDim sendD(0 To 3) As Byte
        sendD(0) = Asc("F")
        sendD(1) = Asc("W")
        sendD(2) = Asc("U")
        sendD(3) = Asc("P")
        
        WinsockUDP.RemoteHost = Trim(txtIP.Text) '"255.255.255.255"
        WinsockUDP.RemotePort = CONFIG_RPORT
        WinsockUDP.SendData sendD
        Sleep (100)
        Erase sendD
                
        ' Establish control socket for firmware uploading
        winsockUP.RemoteHost = txtIP.Text
        winsockUP.RemotePort = CONFIG_UPORT
        winsockUP.Connect   'Call WinsockUP_Connect
        DoEvents
        
    End If

End Sub
    
Private Sub mnuExit_Click()
    Form_Unload 0
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
    'On Error Resume Next
    Select Case Button.Key
        Case "SearchBoard"
            Call mnuSearchBoard_Click
        Case "SettingBoard"
            Call mnuSettingBoard_Click
        Case "Upload"
            Call mnuUpload_Click
        Case "Exit"
            Call mnuExit_Click
    End Select
End Sub
Public Sub ListBoards_FirstRowSelect()
    ListBoards_ItemClick ListBoards.ListItems(1)
    ListBoards.ListItems(1).Selected = True
End Sub

Private Sub ListBoards_ItemClick(ByVal Item As MSComctlLib.ListItem)
Dim dd() As Byte
    Dim i As Integer
    
    bSelect = True
    dd = colBoards.Item(Item.Key)
    BoardKey = Item.Key
    CopyMemory BoardInfo, dd(0), Len(BoardInfo)
    
    txtVersion.Text = BoardInfo.ver(0) & "." & BoardInfo.ver(1)
        
    txtIP.Text = BoardInfo.ip(0) & "." & BoardInfo.ip(1) & "." & BoardInfo.ip(2) & "." & BoardInfo.ip(3)
    txtSubnet.Text = BoardInfo.subnet(0) & "." & BoardInfo.subnet(1) & "." & BoardInfo.subnet(2) & "." & BoardInfo.subnet(3)
    txtGW.Text = BoardInfo.gw(0) & "." & BoardInfo.gw(1) & "." & BoardInfo.gw(2) & "." & BoardInfo.gw(3)
    'txDevice.Text = BoardInfo.devno
    
    
    ' DHCP
    If BoardInfo.dhcp Then
        chkDHCP.Value = 1
    Else
        chkDHCP.Value = 0
    End If
        
    ' ID
    'txtID.Text = StrConv(BoardInfo.id, vbUnicode)
    
    ' Password
    'txtPW.Text = StrConv(BoardInfo.pw, vbUnicode)
       
    Erase dd
    
End Sub

Private Sub txtID_Change()

End Sub

Private Sub WinsockUDP_DataArrival(ByVal bytesTotal As Long)
    Dim getboard(BUFFER_SIZE) As Byte
    DoEvents
    
    ReDim getd(0 To bytesTotal - 1) As Byte
    
    WinsockUDP.GetData getd, vbByte, bytesTotal
    
    CopyMemory getboard(0), getd(0), BUFFER_SIZE + 1
        
    If (getboard(0) = Asc("f")) And (getboard(1) = Asc("i")) And (getboard(2) = Asc("n")) And (getboard(3) = Asc("d")) Then
        If ToolMode = Searching Then
            Call BoardAdd(getboard)
            'ToolMode = None
        End If
        
    ElseIf (getboard(0) = Asc("s")) And (getboard(1) = Asc("e")) And (getboard(2) = Asc("t")) And (getboard(3) = Asc("t")) Then
        If ToolMode = Setting Then
            'Call StopTimer
            Call BoardUpdate(getboard)
            'ToolMode = None
        End If
    End If
    
    Erase getd
    
End Sub

Private Sub WinsockUDP_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
Debug.Print Number

End Sub

Private Sub winsockUP_Connect()
On Error GoTo UP_ERROR


    Dim hSend, BSize, LF&
    Dim sendD() As Byte
    Dim FileSize As Long
    'Dim LastTimeout As Long
    
    'LastTimeout = 25000 ' Booting delay Time
    
    Call StopTimer
    Me.Enabled = False
    
    hSend = FreeFile
    Open strUploadFile For Binary Access Read As hSend
    
    frameProgress.Visible = True
    FileSize = FileLen(strUploadFile)
    ProgressFile.Max = FileSize ' + LastTimeout
    ProgressFile.Min = 0
    ProgressFile.Value = 0
    
    ReDim sendD(0 To 3) As Byte
    
    If m_UpMode = 0 Then
        sendD(0) = 0
        sendD(1) = (FileSize And 16711680) / &H10000
        sendD(2) = (FileSize And 65280) / &H100
        sendD(3) = (FileSize And 255)
        winsockUP.SendData sendD
        DoEvents
        Sleep (200)
        Erase sendD
    
        FileSize = 0
        ' read block data as send buf size.
        BSize = 256
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
                Sleep (220)                 ' AVR 16MHz
                winsockUP.SendData sendD
                DoEvents
                Erase sendD
                DoEvents
                FileSize = FileSize + BSize
                ProgressFile.Value = FileSize
            Loop
        End If
    ElseIf m_UpMode = 1 Then
        sendD(3) = (FileSize And &HFF000000) / &H1000000
        sendD(2) = (FileSize And 16711680) / &H10000
        sendD(1) = (FileSize And 65280) / &H100
        sendD(0) = (FileSize And 255)
        winsockUP.SendData sendD
        DoEvents
        Sleep (200)
        Erase sendD
        
        FileSize = 0
        ' read block data as send buf size.
        BSize = 1460
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
                Sleep (110)                 ' Serial Flash
                winsockUP.SendData sendD
                DoEvents
                Erase sendD
                DoEvents
                FileSize = FileSize + BSize
                ProgressFile.Value = FileSize
            Loop
        End If
    End If
    
    Dim nBar As Integer
    nBar = 0
    DoEvents
    Sleep (1000)
    If m_UpMode = 0 Then
        Call MessageBox("Upload firmware successfully.")
    ElseIf m_UpMode = 1 Then
        Call MessageBox("Upload webpage successfully.")
    End If
    
    frameProgress.Visible = False
    Me.Enabled = True
    winsockUP.Close
    Close hSend
    If m_UpMode = 0 Then
        Call mnuSearchBoard_Click
    End If
    
    Exit Sub
    
UP_ERROR:
    
    Close hSend
    frameProgress.Visible = False
    ProgressFile.Value = 0
    ToolMode = None
    If m_UpMode = 0 Then
        Call MessageBox("Uploading firmware error occurs!!" & vbCrLf & vbCrLf & "Please retry it again.")
    ElseIf m_UpMode = 1 Then
        Call MessageBox("Uploading firmware error occurs!!" & vbCrLf & vbCrLf & "Please retry it again.")
    End If
    
    
    winsockUP.Close
End Sub


Private Sub winsockUP_Close()
    winsockUP.Close
    ToolMode = None
    
    ProgressFile.Value = 0
    Me.Enabled = True
End Sub

Private Sub winsockUP_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    Call StopTimer
    winsockUP.Close
    
    Me.Enabled = True
    
    ToolMode = None
    Call MessageBox("Firmware uploading error!!" & vbCrLf & vbCrLf & "Retry firmware uploading.")
End Sub

Sub StartTimer(msg As String, intval As Integer)
    TimerWait.Interval = intval
    TimerWait.Enabled = True
    Me.Enabled = False
    StatusBar1.Panels("Normal").Text = "Status : " & msg
End Sub

Sub StopTimer()
    Me.Enabled = True
    TimerWait.Enabled = False
    StatusBar1.Panels("Normal").Text = "Status : Normal"
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

