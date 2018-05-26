// DMSOpt.cpp : implementation file
//

#include "stdafx.h"
#include "ODMATest.h"
#include "TestDoc.h"
#include "DMSOpt.h"
#include <assert.h>
#include <strsafe.h>

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSOptions dialog


CFrmDMSOptions::CFrmDMSOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CFrmDMSOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrmDMSOptions)
	m_DmsCount = 0;
	m_GetDms = _T("");
	m_SetDms = _T("");
	m_Default = 0;
	m_Query = FALSE;
	m_Version = _T("");
	m_WorkFlow = FALSE;
	m_UseEx = FALSE;
	m_Alter = FALSE;
	//}}AFX_DATA_INIT
}


void CFrmDMSOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrmDMSOptions)
	DDX_Control(pDX, IDC_LISTFUNCTION, m_ListFunction);
	DDX_Control(pDX, IDC_LISTDMS, m_ListDms);
	DDX_Text(pDX, IDC_txtDmsCount, m_DmsCount);
	DDX_Text(pDX, IDC_txtGetDms, m_GetDms);
	DDX_Text(pDX, IDC_txtSetDms, m_SetDms);
	DDX_Check(pDX, IDC_QUERY, m_Query);
	DDX_Text(pDX, IDC_VERSION, m_Version);
	DDX_Check(pDX, IDC_WORKFLOW, m_WorkFlow);
	DDX_Check(pDX, IDC_USEEX, m_UseEx);
	DDX_Check(pDX, IDC_ALTERNATE, m_Alter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrmDMSOptions, CDialog)
	//{{AFX_MSG_MAP(CFrmDMSOptions)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_BN_CLICKED(IDC_REREGISTER, OnReRegister)
	ON_LBN_SELCHANGE(IDC_LISTDMS, OnSelchangeListdms)
	ON_BN_CLICKED(IDC_USEEX, OnUseEx)
	ON_BN_CLICKED(IDC_ALTERNATE, OnAlternate)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_BN_CLICKED(IDC_WORKFLOW, OnWorkflow)
	ON_BN_CLICKED(IDC_REGISTRYDEFAULT, OnRegistryDefault)
	ON_BN_CLICKED(IDC_SESSIONDEFAULT, OnSessionDefault)
	ON_BN_CLICKED(IDC_QueryCapability, OnQueryCapability)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrmDMSOptions message handlers

BOOL CFrmDMSOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	m_Handle = (DWORD)CODMATestDoc::odmHandle;
	m_UseEx = CODMATestDoc::m_bUseEx;
	m_Alter = CODMATestDoc::m_bAlter;
	
	OnGetDmsInfo();
	OnGetDmsList();
	
	return TRUE; 
}

void CFrmDMSOptions::OnGetDmsInfo() 
{
	const char *lpszAppId = AfxGetAppName();
	
	LPSTR lpszDms = m_GetDms.GetBuffer(ODM_DMSID_MAX);


	const ODMSTATUS odm = ODMGetDMS(lpszAppId, lpszDms);
	if(!odm)
	{
		WORD wVerNo = 0;
		DWORD dwExtensions = 0;
	
		if(CODMATestDoc::odmHandle)
		{
			ODMGetDMSInfo(CODMATestDoc::odmHandle, lpszDms, &wVerNo, &dwExtensions);
		}

		m_Version.Format("%4.2f", wVerNo/100.0);
		m_Query = (BOOL) dwExtensions & ODM_EXT_QUERY;
		m_WorkFlow = (BOOL) dwExtensions & ODM_EXT_WORKFLOW;
	}
	else
		m_GetDms = _T("No DMS for App");
	
	m_GetDms.ReleaseBuffer();
	UpdateData(FALSE);
}

void CFrmDMSOptions::OnGetDmsCount()
{
	m_DmsCount = ODMGetDMSCount();
	
	UpdateData(FALSE);
}

void CFrmDMSOptions::OnGetDmsList()
{
	OnGetDmsCount();
	
	CString strDmsList;
	const auto result = ODM_DMSID_MAX*m_DmsCount + 1;
	LPSTR lpszDmsList = strDmsList.GetBuffer(result);
	assert(result < 65535);
	ODMSTATUS odm = ODMGetDMSList(lpszDmsList, static_cast<WORD>(result));
	char *szDms = lpszDmsList;
	
	m_ListDms.ResetContent();
 
	while(*szDms) 
	{
		m_ListDms.AddString(szDms);
		szDms = strchr(szDms, 0) + 1;
	}
	
	strDmsList.ReleaseBuffer();
	UpdateData(FALSE);
}


void CFrmDMSOptions::OnSessionDefault() 
{
	const char *lpszAppId = AfxGetAppName();
	const char *DMSName = m_SetDms;
	ODMSetDMS(lpszAppId, DMSName);
}


void CFrmDMSOptions::OnRegistryDefault() 
{
	OnSessionDefault();

	const char *lpszAppId = AfxGetAppName();

	const size_t len = ODM_APPID_MAX + 1 + _countof(ODMA_KEY);
	char DMSKey[len];
	StringCchCopyN(DMSKey, _countof(DMSKey), lpszAppId, ODM_APPID_MAX);
	StringCchCat(DMSKey, _countof(DMSKey), "\\" );
	StringCchCat(DMSKey, _countof(DMSKey), ODMA_KEY);

	const DWORD set_dms_length = m_SetDms.GetLength() + 1; //account for null terminator
	RegSetValue(HKEY_CLASSES_ROOT, DMSKey, REG_SZ, m_SetDms, set_dms_length);
}


void CFrmDMSOptions::OnReRegister() 
{
	OnSessionDefault();

	dynamic_cast<CODMATestApp *>(AfxGetApp())->OnRegisterApp();

	OnGetDmsInfo();
}

void CFrmDMSOptions::OnSelchangeListdms() 
{
	m_ListDms.GetText(m_ListDms.GetCurSel(), m_SetDms); 
	UpdateData(FALSE);
	
}

void CFrmDMSOptions::OnUseEx() 
{
	UpdateData(TRUE);
	CODMATestDoc::m_bUseEx = m_UseEx;
}

void CFrmDMSOptions::OnAlternate() 
{
	UpdateData(TRUE);
	CODMATestDoc::m_bAlter = m_Alter;
}

void CFrmDMSOptions::OnQuery() 
{
	UpdateData(FALSE);
}

void CFrmDMSOptions::OnWorkflow() 
{
	UpdateData(FALSE);
}

void CFrmDMSOptions::OnExit() 
{
	EndDialog(0);	
}


void CFrmDMSOptions::OnQueryCapability() 
{
	LPSTR ItemList[ODM_CAPABILITY] = 
	{
		"",
		"ODMActivate",
		"ODMCloseDoc",
		"ODMCloseDocEx",
		"ODMGetAlternateContext",
		"ODMGetDMSInfo",
		"ODMGetDocInfo",
		"ODMGetDocRelation",
		"ODMGetLeadMoniker",
		"ODMNewDoc",
		"ODMOpenDoc",
		"ODMQueryClose",
		"ODMQueryExecute",
		"ODMQueryGetResalt",
		"ODMSaveAs",
		"ODMSaveAsEx",
		"ODMSaveDoc",
		"ODMSaveDocEx",
		"ODMSelectDoc",
		"ODMSelectDocEx",
		"ODMSetAlternateContent",
		"ODMSetDocEvent",
		"ODMSetDocInfo",
		"ODMSetDocRelation"
	};
	
	m_ListFunction.ResetContent( );
	for(int ii = 1; ii < ODM_CAPABILITY; ii++)
		if(!ODMQueryCapability(CODMATestDoc::odmHandle, m_GetDms,	ii, 0, ODM_SILENT))
		{
			m_ListFunction.AddString(ItemList[ii]);
		}
}
