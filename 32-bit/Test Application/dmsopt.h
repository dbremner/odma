// DMSOpt.h : header file
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSOptions dialog

#define ODM_CAPABILITY 24

class CFrmDMSOptions : public CDialog
{
// Construction
public:
	CFrmDMSOptions(CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrmDMSOptions)
	enum { IDD = IDD_DMSOptions };
	CListBox	m_ListFunction;
	CListBox	m_ListDms;
	UINT	m_DmsCount;
	CString	m_GetDms;
	CString	m_SetDms;
	int		m_Default;
	BOOL	m_Query;
	CString	m_Version;
	BOOL	m_WorkFlow;
	BOOL	m_UseEx;
	BOOL	m_Alter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrmDMSOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnGetDmsCount();
	void OnGetDmsList();
	void OnGetDmsInfo();

	// Generated message map functions
	//{{AFX_MSG(CFrmDMSOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnReRegister();
	afx_msg void OnSelchangeListdms();
	afx_msg void OnUseEx();
	afx_msg void OnAlternate();
	afx_msg void OnQuery();
	afx_msg void OnWorkflow();
	afx_msg void OnRegistryDefault();
	afx_msg void OnSessionDefault();
	afx_msg void OnQueryCapability();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
