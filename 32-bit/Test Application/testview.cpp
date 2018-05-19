// TestView.cpp : implementation of the CODMATestView class
//

#include "stdafx.h"
#include "ODMATest.h"

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODMATestView
IMPLEMENT_DYNCREATE(CODMATestView, CRichEditView)

BEGIN_MESSAGE_MAP(CODMATestView, CRichEditView)
	//{{AFX_MSG_MAP(CODMATestView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODMATestView construction/destruction

CODMATestView::CODMATestView()
{
	// TODO: add construction code here
}

CODMATestView::~CODMATestView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CODMATestView diagnostics

#ifdef _DEBUG
void CODMATestView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CODMATestView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CODMATestDoc* CODMATestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODMATestDoc)));
	return static_cast<CODMATestDoc*>(m_pDocument);
}
#endif //_DEBUG

