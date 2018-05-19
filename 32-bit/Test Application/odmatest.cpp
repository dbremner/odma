// odmatest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ODMATest.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "TestDoc.h"
#include "TestView.h"
#include "DMSOpt.h"
#include "DMSQuery.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODMATestApp

BEGIN_MESSAGE_MAP(CODMATestApp, CWinApp)
	//{{AFX_MSG_MAP(CODMATestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_TOOLS_QUERY, OnToolsQuery)
	ON_COMMAND(ID_TOOLS_DMSINFO, OnToolsDmsInfo)
	ON_COMMAND(ID_FILE_OPEN_EX, OnFileOpenEx)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODMATestApp construction

CODMATestApp::CODMATestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CODMATestApp object

CODMATestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CODMATestApp initialization

BOOL CODMATestApp::InitInstance()
{             
#ifdef _TIME_BOMB
	// Testing time experient
	if (TimeBomb(1998, 3))
		return FALSE;
#endif		

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_ODMTYPE,
		RUNTIME_CLASS(CODMATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CODMATestView));

	pDocTemplate->SetContainerInfo(IDR_RTFTYPE_CNTR_IP);

	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();

	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Initialized dms by connection manager
	OnRegisterApp();

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CODMATestApp::ExitInstance()
{
	OnUnRegisterApp();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CODMATestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// VB-Event registration
// (calls to AfxRegisterVBEvent will be placed here by ClassWizard)

//{{AFX_VBX_REGISTER_MAP()
//}}AFX_VBX_REGISTER_MAP

/////////////////////////////////////////////////////////////////////////////
// CODMATestApp commands

void CODMATestApp::OnRegisterApp()
{
	const char *lpszAppId = AfxGetAppName();

	OnUnRegisterApp();

	ODMSTATUS odm = ODMRegisterApp(&CODMATestDoc::odmHandle, ODM_API_VERSION,
		(LPSTR) lpszAppId, (WORD)AfxGetMainWnd()->m_hWnd, NULL);
	switch(odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_NODMS:
		break;
	case ODM_E_CANTINIT:
		break;
	case ODM_E_VERSION:
		break;
	default:
		break;
	}
}

void CODMATestApp::OnUnRegisterApp()
{
   if (CODMATestDoc::odmHandle)
	   ODMUnRegisterApp(CODMATestDoc::odmHandle);

   CODMATestDoc::odmHandle = NULL;
}

void CODMATestApp::OnFileOpen() 
{
	char Title[ODM_TITLETEXT_MAX];
	
	if(!CODMATestDoc::OnSelectDoc(Title))
		return;

	if(!*Title)
	{
		CWinApp::OnFileOpen();
		return;
	}

	CDocument* pDocument = OpenDocumentFile(Title);
	if(pDocument)
		ASSERT(pDocument->IsKindOf(RUNTIME_CLASS(CODMATestDoc)));
}

void CODMATestApp::OnFileOpenEx() 
{
	char Title[ODM_TITLETEXT_MAX];
	
	WORD wDocCount = 5; // Default max selected document

	CString strDocIdList;
	LPTSTR lpszDocIdList = strDocIdList.GetBufferSetLength(ODM_DOCID_MAX*wDocCount);

	if(!CODMATestDoc::OnSelectDocEx(lpszDocIdList, &wDocCount))
		return;
	
	if(!*lpszDocIdList)
	{
		CWinApp::OnFileOpen();
		return;
	}

	LPSTR lpPosDoc = lpszDocIdList;
	while(*lpPosDoc) 
	{
		strcpy(CODMATestDoc::DocId, lpPosDoc);
		strcpy(CODMATestDoc::Format, ODM_FORMAT_TEXT);
		CODMATestDoc::GetTitle(Title, CODMATestDoc::DocId, CODMATestDoc::Format);

		CDocument* pDocument = AfxGetApp()->OpenDocumentFile(Title);
		if(pDocument)
			ASSERT(pDocument->IsKindOf(RUNTIME_CLASS(CODMATestDoc)));
		lpPosDoc = strchr(lpPosDoc, NULL) + 1;
	}

	strDocIdList.ReleaseBuffer();
}

void CODMATestApp::OnToolsDmsInfo() 
{
	CFrmDMSOptions frmDMSOptions(m_pMainWnd);
	frmDMSOptions.DoModal();
	return;	
}

void CODMATestApp::OnToolsQuery() 
{
	CFrmDMSQuery frmDMSQuery(m_pMainWnd);
	frmDMSQuery.DoModal();
	return;	
}


/*************************************************************
Function for check time for use.
ODMA 2.0 1997 Ivan
*************************************************************/

BOOL TimeBomb(WORD wYear, WORD wMonth)
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	
	if(tm.wYear <= wYear && (tm.wYear != wYear || tm.wMonth < wMonth))
			return FALSE;
	MessageBox(NULL, "This version of the ODMA Test Application is expired",
	"ODMA Test Application", MB_ICONSTOP | MB_TASKMODAL);
	return TRUE;
}

