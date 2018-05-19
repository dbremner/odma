// CntrItem.cpp : implementation of the CODMATestCntrItem class
//

#include "stdafx.h"
#include "ODMATest.h"

#include "TestDoc.h"
#include "TestView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODMATestCntrItem implementation

IMPLEMENT_SERIAL(CODMATestCntrItem, CRichEditCntrItem, 0)

CODMATestCntrItem::CODMATestCntrItem(REOBJECT* preo, CODMATestDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CODMATestCntrItem::~CODMATestCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CODMATestCntrItem diagnostics

#ifdef _DEBUG
void CODMATestCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CODMATestCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
