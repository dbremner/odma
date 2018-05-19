// ODMATest.h : main header file for the ODMATEST application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

	#include "Resource32.h"       // main symbols
	#define ODMA_KEY	"ODMA32"

#include "odma.h"       // main symbols

#define ODM_QUERY_MAX			1024		// Max length of a query including
													// the terminating NULL character.
#define ODM_NAME_MAX			64		// Max length of a name document including
													// the terminating NULL character.
#define ODM_TITLETEXT_MAX      128	// Max length of a title document including
													// the terminating NULL character.
#define ODM_FORMATS			ODM_FORMAT_TEXT "," ODM_FORMAT_RTF//"Text,Rich text format"
/////////////////////////////////////////////////////////////////////////////
// CODMATestApp:
// See ODMATest.cpp for the implementation of this class
//

BOOL TimeBomb(WORD wYear, WORD wMonth);

class CODMATestApp : public CWinApp
{
public:
	CODMATestApp();
	void OnRegisterApp();
	void OnUnRegisterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODMATestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CODMATestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnToolsQuery();
	afx_msg void OnToolsDmsInfo();
	afx_msg void OnFileOpenEx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
