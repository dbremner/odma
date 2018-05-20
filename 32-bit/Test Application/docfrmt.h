#if !defined(AFX_FRMDOCFORMAT_H__67D66894_6B1F_11D1_935C_006097A67292__INCLUDED_)
#define AFX_FRMDOCFORMAT_H__67D66894_6B1F_11D1_935C_006097A67292__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// docfmt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrmDOCFormat dialog

class CFrmDOCFormat : public CDialog
{
// Construction
public:
	CFrmDOCFormat(LPSTR szListFrm, CWnd* pParent = nullptr);

// Dialog Data
	//{{AFX_DATA(CFrmDOCFormat)
	enum { IDD = IDD_FORMATDOC };
	CListBox	m_FrmList;
	CString		m_FrmName;
	//}}AFX_DATA

	LPSTR m_szListFrm;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrmDOCFormat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementations
	// Generated message map functions
	//{{AFX_MSG(CFrmDOCFormat)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkFormatList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRMDOCFORMAT_H__67D66894_6B1F_11D1_935C_006097A67292__INCLUDED_)
