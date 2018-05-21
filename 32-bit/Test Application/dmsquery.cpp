// DMSQuery.cpp : implementation file
//

#include "stdafx.h"
#include "ODMATest.h"
#include "TestDoc.h"
#include "DMSQuery.h"
#include <strsafe.h>

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSQuery dialog


CFrmDMSQuery::CFrmDMSQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CFrmDMSQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrmDMSQuery)
	m_txtSearch = _T("");
	m_txtWhere = _T("");
	m_wCount = 0;
	//}}AFX_DATA_INIT
	*m_queryId = NULL;
}


CFrmDMSQuery::~CFrmDMSQuery()
{
	if(*m_queryId)
		ODMSTATUS odm = ODMQueryClose(CODMATestDoc::odmHandle, m_queryId);
}

void CFrmDMSQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrmDMSQuery)
	DDX_Control(pDX, IDC_LISTRESULT, m_ListResult);
	DDX_Text(pDX, IDC_SEARCH, m_txtSearch);
	DDX_Text(pDX, IDC_WHERE, m_txtWhere);
	DDX_Text(pDX, IDC_DOCCOUNT, m_wCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrmDMSQuery, CDialog)
	//{{AFX_MSG_MAP(CFrmDMSQuery)
	ON_BN_CLICKED(IDGO, OnGo)
	ON_BN_CLICKED(IDEXIT, OnExit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSQuery message handlers

void CFrmDMSQuery::OnGo() 
{
	UpdateData(TRUE);

	m_wCount = 10;
	ODMSTATUS odm;
	
	if(*m_queryId)
		odm = ODMQueryClose(CODMATestDoc::odmHandle, m_queryId);

	CString strDMSList;
	LPTSTR lpszDMSList = strDMSList.GetBufferSetLength(ODM_DMSID_MAX);

	odm = ODMGetDMS(AfxGetAppName(), lpszDMSList);
	lpszDMSList[strlen(lpszDMSList)+1] = '\0';	
//	if (!odm) return;

	CString strQuery;
	LPTSTR lpszQuery = strQuery.GetBufferSetLength(ODM_QUERY_MAX);
	
	const size_t query_len = ODM_QUERY_MAX;

	StringCchCopy(lpszQuery, query_len, "SELECT ODM_DOCID, ODM_NAME");
	if(!m_txtWhere.IsEmpty())
		strcat_s(lpszQuery, query_len, " where ");
	strcat_s(lpszQuery, query_len, m_txtWhere);
	if(!m_txtSearch.IsEmpty())
		strcat_s(lpszQuery, query_len, " search ");
	strcat_s(lpszQuery, query_len, m_txtSearch);
	
	DWORD dwFlags = ODM_SPECIFIC;
	odm = ODMQueryExecute(CODMATestDoc::odmHandle, lpszQuery,
		dwFlags, lpszDMSList, m_queryId );
//	if (!odm) return;

	strDMSList.ReleaseBuffer();
	strQuery.ReleaseBuffer();
	
	CString strDocId, strDocName;
	LPTSTR lpszDocId = strDocId.GetBufferSetLength(ODM_DOCID_MAX*m_wCount);
	LPTSTR lpszDocName = strDocName.GetBufferSetLength(ODM_NAME_MAX*m_wCount);
	
	odm = ODMQueryGetResults(CODMATestDoc::odmHandle, m_queryId,
		lpszDocId, lpszDocName, ODM_NAME_MAX, (WORD*)&m_wCount);
  
	m_ListResult.ResetContent();

	for(UINT i = 0; i<m_wCount; i++)
	{
		char buffer[255];
		sprintf_s(buffer,"%s   %s", &lpszDocName[ODM_NAME_MAX*i], &lpszDocId[ODM_DOCID_MAX*i]);
		m_ListResult.AddString(buffer);
	}

	strDocId.ReleaseBuffer();
	strDocName.ReleaseBuffer();
	
	UpdateData(FALSE);
}

void CFrmDMSQuery::OnExit() 
{
	EndDialog(0);	
}

		  

BOOL CFrmDMSQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE; 
}

