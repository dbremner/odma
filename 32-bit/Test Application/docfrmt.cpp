// DOCFmt.cpp : implementation file
//

#include "stdafx.h"
#include "odmatest.h"
#include "docfrmt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrmDOCFormat dialog


CFrmDOCFormat::CFrmDOCFormat(LPSTR szListFrm, CWnd* pParent /*=NULL*/)
	: CDialog(CFrmDOCFormat::IDD, pParent)
{
	m_szListFrm = szListFrm;
	//{{AFX_DATA_INIT(CFrmDOCFormat)
	m_FrmName = "";
	//}}AFX_DATA_INIT
}

void CFrmDOCFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrmDOCFormat)
	DDX_Control(pDX, IDC_FORMATLIST, m_FrmList);
	DDX_LBString(pDX, IDC_FORMATLIST, m_FrmName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFrmDOCFormat, CDialog)
	//{{AFX_MSG_MAP(CFrmDOCFormat)
	ON_LBN_DBLCLK(IDC_FORMATLIST, OnDblclkFormatList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFrmDOCFormat message handlers

BOOL CFrmDOCFormat::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(!m_szListFrm ||!*m_szListFrm)
		return FALSE;

	int Count = 0;
	
	char lpFormat[ODM_FORMAT_MAX];
	LPSTR lpPosFrm = m_szListFrm;

	do
	{
		if(*lpPosFrm != ',' && *lpPosFrm) 
			lpFormat[Count++] = *lpPosFrm;
		else
		{
			lpFormat[Count] = NULL;
			m_FrmList.AddString(lpFormat);
			Count = 0;
		}
	} 
	while(*lpPosFrm++);

	UpdateData(FALSE);
	
	return TRUE;
}

void CFrmDOCFormat::OnDblclkFormatList() 
{
	OnOK();
}
