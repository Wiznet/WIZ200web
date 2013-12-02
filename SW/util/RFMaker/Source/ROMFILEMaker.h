// ROMFILEMaker.h : main header file for the ROMFILEMAKER application
//

#if !defined(AFX_ROMFILEMAKER_H__A2D2E104_6889_42B1_B27D_F9345868F923__INCLUDED_)
#define AFX_ROMFILEMAKER_H__A2D2E104_6889_42B1_B27D_F9345868F923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CROMFILEMakerApp:
// See ROMFILEMaker.cpp for the implementation of this class
//

class CROMFILEMakerApp : public CWinApp
{
public:
	CROMFILEMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROMFILEMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CROMFILEMakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROMFILEMAKER_H__A2D2E104_6889_42B1_B27D_F9345868F923__INCLUDED_)
