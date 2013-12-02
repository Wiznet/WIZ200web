#if !defined(AFX_ROMFILEMAKERDLG_H__D4003606_D7CB_414A_97DD_EEBD3F06A015__INCLUDED_)
#define AFX_ROMFILEMAKERDLG_H__D4003606_D7CB_414A_97DD_EEBD3F06A015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ROMFileMakerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CROMFileMakerDlg dialog

class CROMFileMakerDlg : public CDialog
{
// Construction
public:

	CROMFileMakerDlg(CWnd* pParent = NULL);	// standard constructor

	void InsertColumn();
	void AddItem(CString name);


// Dialog Data
	//{{AFX_DATA(CROMFileMakerDlg)
	enum { IDD = IDD_ROMFILEMAKER_DIALOG };
	CProgressCtrl	m_ctlProgress;
	CListCtrl	m_ctlFileList;
	CString	m_szTypePath;
	CString	m_szFileName;
	BOOL	m_bCheck1;
	BOOL	m_bCheck2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROMFileMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CROMFileMakerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddfile();
	afx_msg void OnMakeimg();
	afx_msg void OnDestroy();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROMFILEMAKERDLG_H__D4003606_D7CB_414A_97DD_EEBD3F06A015__INCLUDED_)
