// DMSQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSQuery dialog

class CFrmDMSQuery : public CDialog
{
// Construction
public:
	CFrmDMSQuery(CWnd* pParent = NULL);   // standard constructor
	~CFrmDMSQuery();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CFrmDMSQuery)
	enum { IDD = IDD_DMSQuery };
	CListBox	m_ListResult;
	CString	m_txtSearch;
	CString	m_txtWhere;
	UINT	m_wCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrmDMSQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_queryId[ODM_QUERYID_MAX];

	// Generated message map functions
	//{{AFX_MSG(CFrmDMSQuery)
	afx_msg void OnGo();
	afx_msg void OnExit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
