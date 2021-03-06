/*  odmasamp.h - This file contains definitions, prototypes, etc. for the
	 sample ODMA implementation.  */

#pragma once

#include <windows.h>
#include <stdio.h>
#include "odmacom.h"
//#include "odmasamp.rh"
#include "resource.h"

#define MAXDOCS			20	// Max. # of documents the sample app. supports
#define MAXCOMPONENTS	10	// Max. # of documents the sample app. supports
#define DOC_NAME_MAX	255

#define DMSNAME	"ODMA 2.0 Sample DMS"
#define DMSID		"ODMASAMP"
#define DMSINI		DMSID ".INI"


// Flags for Profile dialog window procedure
#define PROFILE_EDIT	1

#define NC(a,b) a##::##b

class Application {
	public:
	Application(LPUNKNOWN pUnkOuter, DWORD dwEnvData);
	~Application();
	HRESULT GetInterface(REFIID riid, LPVOID *ppvObj);

	private:
	//----------------------------------------------------------------
	// IUnknown implementation
	//----------------------------------------------------------------
	struct CUnknown : IUnknown 
	{
		explicit CUnknown(Application *pObject) { m_pObject = pObject; }

		//*** IUnknown ***
		STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
		STDMETHOD_(ULONG,AddRef) (VOID);
		STDMETHOD_(ULONG,Release) (VOID);

		private:
		Application *m_pObject;	// pointer to parent object
	};

	friend CUnknown;

	CUnknown m_Unknown;

	//----------------------------------------------------------------
	// IODMDocMan interface
	//----------------------------------------------------------------
	struct CODMDocMan : IODMDocMan 
	{
		explicit CODMDocMan(Application *pObject) { m_pObject = pObject; }
		~CODMDocMan() {}

		//*** IUnknown ***
		STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
		STDMETHOD_(ULONG,AddRef) (VOID);
		STDMETHOD_(ULONG,Release) (VOID);

		// *** IODMDocMan methods ***
		STDMETHOD_(ODMSTATUS, SelectDoc)(LPSTR lpszDocId, LPDWORD pdwFlags);
		STDMETHOD_(ODMSTATUS, OpenDoc)(DWORD flags, LPSTR lpszDocId,
			LPSTR lpszDocLocation);
		STDMETHOD_(ODMSTATUS, SaveDoc)(LPSTR lpszDocId, LPSTR lpszNewDocId);
		STDMETHOD_(ODMSTATUS, CloseDoc)(LPSTR lpszDocId, DWORD activeTime,
			DWORD pagesPrinted, LPVOID sessionData, WORD dataLen);
		STDMETHOD_(ODMSTATUS, NewDoc)(LPSTR lpszDocId, DWORD dwFlags,
			LPSTR lpszFormat, LPSTR lpszDocLocation);
		STDMETHOD_(ODMSTATUS, SaveAs)(LPSTR lpszDocId, LPSTR lpszNewDocId,
			LPSTR lpszFormat, ODMSAVEASCALLBACK pcbCallBack,
			LPVOID pInstanceData);
		STDMETHOD_(ODMSTATUS, Activate)(WORD action, LPSTR lpszDocId);
		STDMETHOD_(ODMSTATUS, GetDocInfo)(LPSTR lpszDocId, WORD item,
			LPSTR lpszData, WORD dataLen);
		STDMETHOD_(ODMSTATUS, SetDocInfo)(LPSTR lpszDocId, WORD item,
			LPSTR lpszData);
		STDMETHOD_(ODMSTATUS, GetDMSInfo) (LPSTR lpszDmsId, LPWORD pwVerNo,
			LPDWORD pdwExtensions);
		STDMETHOD_(ODMSTATUS, GetLeadMoniker)(LPSTR lpszDocId,
			LPMONIKER *ppMoniker);

		private:
		Application *m_pObject;					// pointer to parent object
	};

	friend CODMDocMan;

	CODMDocMan m_ODMDocMan;

	//----------------------------------------------------------------
	// IODMDocMan2 interface
	//----------------------------------------------------------------
	struct CODMDocMan2 : IODMDocMan2 
	{
		explicit CODMDocMan2(Application *pObject) { m_pObject = pObject; }
		~CODMDocMan2() {}

		//*** IUnknown ***
		STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
		STDMETHOD_(ULONG,AddRef) (VOID);
		STDMETHOD_(ULONG,Release) (VOID);

		// *** IODMDocMan2 methods ***
	STDMETHOD_( ODMSTATUS, CloseDocEx)(LPSTR lpszDocId, LPDWORD pdwFlags,
		DWORD activeTime, DWORD pagesPrinted, LPVOID sessionData, WORD dataLen);
	
	STDMETHOD_( ODMSTATUS, SaveAsEx)(LPSTR lpszDocId,	LPSTR lpszNewDocId,
		LPSTR lpszFormat, ODMSAVEASCALLBACK pcbCallBack,
		LPVOID pInstanceData, LPDWORD pdwFlags);

	STDMETHOD_( ODMSTATUS, SaveDocEx)(LPSTR lpszDocId, LPSTR lpszNewDocId, LPDWORD pdwFlags);
		
	STDMETHOD_( ODMSTATUS, SelectDocEx)(LPSTR lpszDocIds, LPWORD pwDocIdsLen,
		LPWORD pwDocCount, LPDWORD pdwFlags, LPSTR lpszFormatFilter);
		
	STDMETHOD_( ODMSTATUS, QueryCapability)( LPCSTR lpszDmsId, DWORD function,
		DWORD item,	DWORD flags );
		
	STDMETHOD_( ODMSTATUS, SetDocEvent)(LPSTR lpszDocId, DWORD flags, DWORD event,
		LPVOID lpData, DWORD dwDataLen, LPSTR lpszComment);
		
	STDMETHOD_( ODMSTATUS, GetAlternateContent)(LPSTR lpszDocId, LPDWORD pdwFlags,
		LPSTR lpszFormat, LPSTR lpszDocLocation);
		
	STDMETHOD_( ODMSTATUS, SetAlternateContent)(LPSTR lpszDocId, LPDWORD pdwFlags,
		LPSTR lpszFormat, LPSTR lpszDocLocation);
		
	STDMETHOD_( ODMSTATUS, GetDocRelation)(LPSTR lpszDocId,	LPDWORD pdwFlags, 
		LPSTR lpszLinkedId,	LPSTR lpszFormat, LPSTR lpszPreviousId );
		
	STDMETHOD_( ODMSTATUS, SetDocRelation)(LPSTR lpszDocId,	LPDWORD pdwFlags,
		LPSTR lpszLinkedId,	LPSTR lpszFormat, LPSTR lpszPreviousId );

		private:
		Application *m_pObject;					// pointer to parent object
	};

	friend CODMDocMan2;

	CODMDocMan2 m_ODMDocMan2;

	//----------------------------------------------------------------
	// IODMQuery implementation
	//----------------------------------------------------------------
	struct CODMQuery : IODMQuery 
	{
		explicit CODMQuery( Application *pObject ){ m_pObject = pObject; }
		~CODMQuery() {}

    	//*** IUnknown ***
		STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
		STDMETHOD_(ULONG,AddRef) (VOID);
    	STDMETHOD_(ULONG,Release) (VOID);

    	// *** IODMQuery methods ***
		STDMETHOD_(ODMSTATUS, QueryExecute) ( LPCSTR lpszSearchCriteria, LPSTR queryId );

		STDMETHOD_(ODMSTATUS, QueryGetResults) ( LPCSTR lpszQuery, LPSTR lpszDocId,
										LPSTR lpszDocName, WORD docNameLen, WORD *docCount );

		STDMETHOD_(ODMSTATUS, QueryClose)( LPCSTR queryId );

		private:
    	Application *m_pObject;					// pointer to parent object
	};

	friend CODMQuery;

	CODMQuery m_ODMQuery;

	private:
	// Internal data
	DWORD m_dwRefs;             // reference count
	LPUNKNOWN m_pUnkOuter;      // controlling IUnknown
	HWND m_clientWind;			// window handle from client

	char m_szQueryId[ODM_QUERYID_MAX];
	WORD m_nQueryDocListIndex;
	DWORD m_nQuery;
};  // Application


class Document {
	private:
	BOOL	bEdited; //BVG:
	char DocId[80];
	int SaveFlag;
	char Author[30];
	char Name[80];
	char DocType[30];
	int OpenCount;
	int DocAccessed;	/* This flag tracks whether or not the application has
							ever had a chance to access the document.  It is u
							used during SaveAs. */

	//BVG Components Properties
	int		iComponents;
	char	Format[MAXCOMPONENTS][ODM_FORMAT_MAX];
	char	DocLocation[MAXCOMPONENTS][ODM_FILENAME_MAX];

	friend BOOL CALLBACK _export ProfileProc(HWND hwndDlg, UINT message, WPARAM wParam,
		LPARAM lParam);

	public:
	ODMSTATUS GetComponent(LPSTR lpszFormat, LPSTR lpszDocLocation);
	ODMSTATUS DeleteComponent(LPSTR lpszFormat);
	ODMSTATUS SetComponent(LPSTR lpszFormat, LPSTR lpszDocLocation);
	ODMSTATUS AddComponent(LPSTR lpszFormat, LPSTR lpszDocLocation);
	Document();
	~Document() {}
	Document(LPSTR lpszFormat, LPSTR lpszDocLocation);
	explicit Document(Document *pOldDoc);
	explicit Document(LPSTR lpszDocId);
	char *GetId() { return DocId; }
	int GetOpenCount() const { return OpenCount; }
	ODMSTATUS Open(LPSTR lpszFileName);
	ODMSTATUS Save() { SaveFlag = 1; return 0; }
	ODMSTATUS Close(DWORD activeTime, DWORD pagesPrinted,
		LPVOID sessionData, WORD dataLen);
	ODMSTATUS EditAttributes(HWND hParent);
	ODMSTATUS ShowAttributes(HWND hParent);
	ODMSTATUS GetInfo(WORD item, LPSTR lpszData, WORD dataLen);
	ODMSTATUS SetInfo(WORD item, LPSTR lpszData);
	void SaveInfo();
	int HasBeenAccessed() const
	{ return DocAccessed; }

	//BVG:
	int HasBeenEdited() const
	{ return bEdited; } 
};

class DocumentList {
	private:
	Document *List[MAXDOCS];

	public:
	DocumentList();
	~DocumentList();
	void SaveList();
	Document *GetDocumentByIndex(int n);
	Document *GetDocumentById(LPSTR lpszDocId);
	int GetDocumentIndexById(LPSTR lpszDocId);
	ODMSTATUS NewDocument(LPSTR lpszFormat, LPSTR lpszDocLocation,
		Document **ppDoc, DWORD dwFlags, HWND hParent);
	ODMSTATUS CopyDocument(LPSTR lpszDocId, Document **ppDoc, HWND hParent);
	ODMSTATUS DeleteDocument(LPSTR lpszDocId);
};  // DocumentList

// Structure definitions
typedef struct {
	LPVOID pInstanceData;
	ODMSAVEASCALLBACK pcbCallBack;
	char Format[50];
} SaveAsData;

typedef struct {
	Document *pDocument;
	int Mode;
} ProDlgData;

// Globals
extern HINSTANCE hInst;
extern DocumentList DocList;

// Prototypes
BOOL CALLBACK _export SelectDocProc(HWND hwndDlg, UINT message, WPARAM wParam,
	LPARAM lParam);
BOOL CALLBACK _export SelectDocProcEx(HWND hwndDlg, UINT message, WPARAM wParam,
	LPARAM lParam);
BOOL CALLBACK _export SaveAsProc(HWND hwndDlg, UINT message, WPARAM wParam,
	LPARAM lParam);
BOOL CALLBACK _export ProfileProc(HWND hwndDlg, UINT message, WPARAM wParam,
	LPARAM lParam);
