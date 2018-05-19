// CntrItem.h : interface of the CODMATestCntrItem class
//

class CODMATestDoc;
class CODMATestView;

class CODMATestCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CODMATestCntrItem)

// Constructors
public:
	CODMATestCntrItem(REOBJECT* preo = NULL, CODMATestDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CODMATestDoc* GetDocument()
		{ return (CODMATestDoc*)CRichEditCntrItem::GetDocument(); }
	CODMATestView* GetActiveView()
		{ return (CODMATestView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODMATestCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CODMATestCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
