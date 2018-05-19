// TestDoc.h : interface of the CODMATestDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CODMATestDoc :
#ifdef WIN32
	public CRichEditDoc
#else
	public CDocument
#endif
{
protected: // create from serialization only
	CODMATestDoc();
	DECLARE_DYNCREATE(CODMATestDoc);

public:
	virtual ~CODMATestDoc();


// Attributes
public:
	static ODMHANDLE odmHandle;
	static BOOL m_bUseEx;
	static BOOL m_bAlter;
	static BOOL m_bAppSel;
	static char DocId[ODM_DOCID_MAX];
	static char Format[ODM_FORMAT_MAX];

protected:
	char m_DocId[ODM_DOCID_MAX];
	char m_FileName[ODM_FILENAME_MAX];
	char m_Format[ODM_FORMAT_MAX];
	char m_TitleText[128];


// Operations static
public:
	static BOOL OnSelectDoc(LPSTR lpszTitle);
	static BOOL OnSelectDocEx(LPSTR lpszDocIds, LPWORD wDocCount);
	static BOOL OnSelectType(LPCSTR DocId, LPSTR lpszFormat, LPSTR lpszListFrm = NULL);
	static void GetDocInfo(WORD wItem, LPSTR lpszData, WORD dataLen, LPCSTR DocId);
	static void GetTitle(LPSTR lpszTitle, LPCSTR DocId, LPCSTR lpszFormat);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODMATestDoc)
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Overloaded function
protected:

#ifdef WIN32
	virtual BOOL DoFileSave();
#else
	virtual BOOL SaveModified();
#endif

// Operations with DMS
public:
	virtual BOOL DMSNewDoc(LPSTR DocId);
	virtual BOOL DMSOpenDoc(LPSTR FileName);
	virtual BOOL DMSOpenAlter(LPSTR FileName);
	virtual BOOL DMSSaveAsDoc();
	virtual BOOL DMSSaveDoc();
	virtual BOOL DMSSaveAlter();
	virtual void DMSCloseDoc(LPSTR DocId = NULL);

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CODMATestDoc)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// For using tow format document
protected:
#ifdef WIN32
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
#else
	BOOL m_bRTF;
#endif
};

typedef  CODMATestDoc* LPODMATestDoc;

/////////////////////////////////////////////////////////////////////////////
