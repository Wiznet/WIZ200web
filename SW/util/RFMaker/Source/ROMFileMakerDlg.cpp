// ROMFileMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "romfilemaker.h"
#include "ROMFileMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char * HeadFile=
"#ifndef _ROMFS_H_\r\n"
"#define _ROMFS_H_\r\n"
"\r\n"
"#include \"%s\"\r\n"
"\r\n"
"typedef struct _ROMFILE ROMFILE;\r\n"
"\r\n"
"struct _ROMFILE\r\n"
"{\r\n"
"\tROMFILE *romfs_next;	/* Link to next ROMFILE structure. */\r\n"
"\tu_char  *romfs_name;	/* Filename */\r\n"
"\tu_int    romfs_size;	/* File size. */\r\n"
"\tcode_area *romfs_data;	/* File contents. */\r\n"
"};\r\n"
"\r\n"
"extern ROMFILE* romfs_list;\r\n"
"\r\n"
"\r\n"
"u_char search_file(u_char * name, code_area ** buf, u_int * len);	// Search a file from ROM FILE\r\n"
"\r\n"
"#endif /* _ROMFS_H_ */\r\n";


const char *RomHead =
"/*\r\n"
" * This file is automatically created by ROM File Maker\r\n"
" */\r\n"
"#include <string.h>\r\n"
"#include \"romfs.h\"\r\n\r\n";

const char *RomTail =
"ROMFILE* romfs_list = &file%dentry;\r\n"
"\r\n"
"\r\n"
"\r\n"
"/*\r\n"
"Description  : Search a file from ROM FILE\r\n"
"Argument     : name - file name\r\n"
"               buf - file contents to be return\r\n"
"               len - file length to be return\r\n"
"Return Value : \r\n"
"Note         : \r\n"
"*/\r\n"
"u_char search_file(u_char * name, code_area ** buf, u_int * len)\r\n"
"{\r\n"
"\tint i;\r\n"
"\tROMFILE *romfs;\r\n"
"\r\n"
"\ti = 0;\r\n"
"\r\n"
"\tfor (romfs = romfs_list; romfs; romfs = romfs->romfs_next)\r\n"
"\t{\r\n"
"\t\tif (!strcmp(name, romfs->romfs_name))\r\n"
"\t\t{\r\n"
"\t\t\t*len = romfs->romfs_size;\r\n"
"\t\t\t*buf = romfs->romfs_data;\r\n"
"\t\t\treturn ++i;\r\n"
"\t\t}\r\n"
"\t}\r\n"
"\r\n"
"\treturn 0;\r\n"
"}\r\n";


const char *FileHead =
"/*\r\n"
" * File %d : %s\r\n"
" */\r\n"
"code_area file%ddata[] = {\r\n";

const char *FileTail =
"};\r\n"
"static ROMFILE file%dentry = { &file%dentry, \"%s\", %d, (code_area *)file%ddata };\r\n\r\n";

const char *FileTail1 =
"};\r\n"
"static ROMFILE file%dentry = { 0, \"%s\", %d, (code_area *)file%ddata };\r\n\r\n";


#define ROM_FNAMELEN    20 

typedef struct          /* Filename block structure */
{
    unsigned int len;               /* Length of file in bytes */
    unsigned int start;             /* Start address of file data in ROM */
    unsigned short check;             /* TCP checksum of file */
    unsigned char flags;            /* Embedded Gateway Interface (EGI) flags */
    char name[ROM_FNAMELEN];		/* Lower-case filename with extension */
} ROM_FNAME;

#define FILE_HEAD_SIZE			(ROM_FNAMELEN +11)

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROMFileMakerDlg dialog

CROMFileMakerDlg::CROMFileMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CROMFileMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CROMFileMakerDlg)
	m_szFileName = _T("");
	m_szFileName = _T("wizweb.rom");
	m_bCheck1 = FALSE;
	m_bCheck2 = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CROMFileMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CROMFileMakerDlg)
	DDX_Control(pDX, IDC_PRGSDOWN, m_ctlProgress);
	DDX_Control(pDX, IDC_LSTFILE, m_ctlFileList);
	DDX_Text(pDX, IDC_TYPEPATH_EDIT, m_szTypePath);
	DDX_Text(pDX, IDC_TYPEPATH_EDIT2, m_szFileName);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	DDX_Check(pDX, IDC_CHECK2, m_bCheck2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CROMFileMakerDlg, CDialog)
	//{{AFX_MSG_MAP(CROMFileMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDFILE, OnAddfile)
	ON_BN_CLICKED(IDC_MAKEIMG, OnMakeimg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROMFileMakerDlg message handlers

BOOL CROMFileMakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_szTypePath = "../mcu/types.h";
	UpdateData(FALSE);
	InsertColumn();
	m_ctlProgress.SetPos(0);	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CROMFileMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CROMFileMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CROMFileMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CROMFileMakerDlg::OnAddfile() 
{
	POSITION p;
	CString str,CurDir("");

	CFileDialog Dlg(TRUE,NULL,(LPSTR)(LPCTSTR)CurDir);
	Dlg.m_ofn.Flags= OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_ENABLEHOOK;


	if (Dlg.DoModal() == IDOK)
	{
		p = Dlg.GetStartPosition();
		while (p != NULL) {

			str = Dlg.GetNextPathName(p);
			AddItem(str);
		}
	}
}

void CROMFileMakerDlg::InsertColumn()
{
	CRect rect;
	m_ctlFileList.GetClientRect(&rect);

	LV_COLUMN lvcolumn;

	lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_CENTER;

	lvcolumn.iSubItem = 0;
	lvcolumn.cx = rect.Width();
	lvcolumn.pszText = "Selected Files";
	m_ctlFileList.InsertColumn(0, &lvcolumn);
}

void CROMFileMakerDlg::OnMakeimg() 
{
	ULONG len, l;
	CString name, str;
	int i, file_cnt;
	CFile iFile, oFile;
	BYTE * buffer;
	unsigned int address;
	int temp;

	double prog;
	ROM_FNAME rom_file;

	file_cnt = m_ctlFileList.GetItemCount();

	if (file_cnt == 0)
	{
		AfxMessageBox("Add any file...");
		return;
	}

	UpdateData();

	if(m_bCheck2 == TRUE)
	{
		oFile.Open(m_szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

		address = file_cnt*(FILE_HEAD_SIZE) + 2;

		//헤더 기록
		for (i = 0; i < file_cnt; i++) 
		{
			name = m_ctlFileList.GetItemText(i, 0);
			temp = name.ReverseFind('\\');
			if(temp>0)str = name.Mid(temp+1);
			
			
			strcpy(rom_file.name, strlwr((LPSTR)(LPCTSTR)str));
			
			iFile.Open(name, CFile::modeRead | CFile::typeBinary);


			rom_file.start = address;
			rom_file.len = iFile.GetLength();

			address += rom_file.len;

			/*
			if(i==0)
			{
				rom_file.start = address;
				rom_file.len = iFile.GetLength();

				address += rom_file.len;
			}
			else
			{
				rom_file.start = address;
				address += rom_file.len;
				
				rom_file.len = iFile.GetLength();
			}

  */
			

			rom_file.check = i;
			rom_file.flags = 0;
			
			temp = (sizeof(rom_file)-1);
			if(temp<0)temp=0;
			oFile.Write((unsigned char *)&rom_file, temp);

			iFile.Close();
		}

		//헤더 종료 인덱스 기록
		unsigned char head_buf[2] = {0xFF, 0xFF};	
		oFile.Write(head_buf, sizeof(head_buf));

		//파일 기록
		for (i = 0; i < file_cnt; i++) 
		{
			name = m_ctlFileList.GetItemText(i, 0);
			iFile.Open(name, CFile::modeRead | CFile::typeBinary);

			len = iFile.GetLength();
			buffer = (BYTE *)malloc(len);

			iFile.Read((void *)buffer, len);
			oFile.Write(buffer, len);

			iFile.Close();
			free(buffer);

			prog = ((double)i / (double)(file_cnt)) * 100.0;
			m_ctlProgress.SetPos((int)prog);
		}
	}
	else
	{
		oFile.Open("romfs.h", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		str.Format(HeadFile,m_szTypePath);
		oFile.Write(str,str.GetLength());
		oFile.Close();

		oFile.Open("romfs.c", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

		str.Format("%s", RomHead);
		oFile.Write(str, str.GetLength());

		for (i = 0; i < file_cnt; i++) 
		{
			name = m_ctlFileList.GetItemText(i, 0);

			str.Format(FileHead, i, name, i);
			oFile.Write(str, str.GetLength());

			iFile.Open(name, CFile::modeRead | CFile::typeBinary);
			len = iFile.GetLength();
			buffer = (BYTE *)malloc(len);

			iFile.Read((void *)buffer, len);

			for (l = 0; l < len; l++)
			{
				str.Format("0x%.2x,", buffer[l]);
				oFile.Write(str, str.GetLength());
				if ((l % 16) == 15) 
				{
					str.Format("%s", "\r\n");
					oFile.Write(str, str.GetLength());
				}
		
			}

			str.Format("%s", "\n");
			oFile.Write(str, str.GetLength());

			if (i == 0) {
				str.Format(FileTail1, i, iFile.GetFileName(), len, i);
				oFile.Write(str, str.GetLength());
			} else {
				str.Format(FileTail, i, i-1, iFile.GetFileName(), len, i);
				oFile.Write(str, str.GetLength());
			}

			iFile.Close();
			free(buffer);

			prog = ((double)i / (double)(file_cnt)) * 100.0;
			m_ctlProgress.SetPos((int)prog);
		
		}
	}

	m_ctlProgress.SetPos(100);
	oFile.Close();

	str.Format("Complete");
	AfxMessageBox( str, MB_ICONEXCLAMATION );

	return;


}

void CROMFileMakerDlg::AddItem(CString name) 
{
	CString str;
	LV_ITEM lvitem;
	lvitem.iItem = m_ctlFileList.GetItemCount();
	lvitem.mask = LVIF_TEXT;
	lvitem.iSubItem = 0;
	lvitem.pszText = (LPSTR)(LPCTSTR)name;

	m_ctlFileList.InsertItem(&lvitem);
}


void CROMFileMakerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}


void CROMFileMakerDlg::OnCheck1() 
{
	m_bCheck1 = TRUE;
	m_bCheck2 = FALSE;
	UpdateData(FALSE);
}

void CROMFileMakerDlg::OnCheck2() 
{
	m_bCheck1 = FALSE;
	m_bCheck2 = TRUE;	
	UpdateData(FALSE);
}
