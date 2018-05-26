// TestView.h : interface of the CODMATestView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CODMATestCntrItem;

class CODMATestView :
	public CRichEditView
{
protected: // create from serialization only
	CODMATestView();
	DECLARE_DYNCREATE(CODMATestView)

// Attributes
public:
	CODMATestDoc* GetDocument();

// Implementation
public:
	virtual ~CODMATestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CODMATestView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CODMATestDoc* CODMATestView::GetDocument()
   { return (CODMATestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
