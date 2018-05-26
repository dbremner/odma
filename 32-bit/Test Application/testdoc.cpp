// TestDoc.cpp : implementation of the CODMATestDoc class
//

#include "stdafx.h"
#include "odmatest.h"

#include "CntrItem.h"
#include "TestDoc.h"
#include "DOCFrmt.h"
#include <strsafe.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ODMHANDLE CODMATestDoc::odmHandle = nullptr;
BOOL CODMATestDoc::m_bUseEx = FALSE;
BOOL CODMATestDoc::m_bAlter = FALSE;
BOOL CODMATestDoc::m_bAppSel = FALSE;
char CODMATestDoc::DocId[] = "";
char CODMATestDoc::Format[] = "";

/////////////////////////////////////////////////////////////////////////////
// CODMATestDoc

IMPLEMENT_DYNCREATE(CODMATestDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CODMATestDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CODMATestDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CODMATestDoc construction/destruction

CODMATestDoc::CODMATestDoc()
	: m_DocId{},
	m_FileName{},
	m_Format{},
	m_TitleText{}
{
}

CODMATestDoc::~CODMATestDoc()
{
}

CRichEditCntrItem* CODMATestDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CODMATestCntrItem(preo, const_cast<CODMATestDoc*>(this));
}

/////////////////////////////////////////////////////////////////////////////
// CODMATestDoc commands

BOOL CODMATestDoc::OnSelectDoc(LPSTR lpszTitle)
{
	m_bAppSel = FALSE;

	if (!odmHandle)
		return FALSE;
  
	DWORD dwFlag = 0;

	const ODMSTATUS odm = ODMSelectDoc(odmHandle, DocId, &dwFlag);
	switch(odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_CANCEL:
		return FALSE;
	case ODM_E_OTHERAPP:
		return FALSE;
	case ODM_E_APPSELECT:
		m_bAppSel = TRUE;
		strcpy(lpszTitle, "");
		return TRUE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		return FALSE;
	default:
		return FALSE;
	}

	if(OnSelectType(DocId, Format))
	{
		GetTitle(lpszTitle, DocId, Format);
		return TRUE;
	}

	return FALSE;
}

BOOL CODMATestDoc::OnSelectDocEx(LPSTR lpszDocIds, LPWORD wDocCount)
{
	m_bAppSel = FALSE;

	if (!odmHandle)
	{
		return FALSE;
	}

	DWORD dwFlags = 0;
	
	WORD wDocIdsLen = ODM_DOCID_MAX * (*wDocCount);
	const ODMSTATUS odm = ODMSelectDocEx(odmHandle, lpszDocIds,	&wDocIdsLen,
			wDocCount, &dwFlags, nullptr);
	switch(odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_CANCEL:
		return FALSE;
	case ODM_E_OTHERAPP:
		return FALSE;
	case ODM_E_APPSELECT:
		m_bAppSel = TRUE;
		StringCchCopy(lpszDocIds, wDocIdsLen, "");
		return TRUE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		return FALSE;
	default:
		return FALSE;
	}
	return TRUE;
}



BOOL CODMATestDoc::OnSelectType(LPCSTR docId, LPSTR lpszFormat, LPSTR lpszListFrm)
{
	StringCchCopy(lpszFormat, ODM_FORMAT_MAX, ODM_FORMAT_TEXT);

	if(!m_bAlter)
	{
		return TRUE;
	}

	CString strFrmList;
	const WORD dataLen = ODM_FORMAT_MAX*5;
	LPSTR lpszList = strFrmList.GetBuffer(dataLen);

	if(!lpszListFrm)
	{
		*lpszList = NULL;

		CODMATestDoc::GetDocInfo(ODM_ALTERNATE_RENDERINGS, lpszList, dataLen, docId);
	}
	else
	{
		StringCchCopy(lpszList, dataLen, lpszListFrm);
	}
	
	if(*lpszList)
	{
		CFrmDOCFormat frmDOCFormat(lpszList);
		const int iRet = frmDOCFormat.DoModal();

		if(iRet == IDOK)
		{
			StringCchCopy(lpszFormat, ODM_FORMAT_MAX, frmDOCFormat.m_FrmName);
			return TRUE;
		}
		StringCchCopy(lpszFormat, ODM_FORMAT_MAX, "");
		return FALSE;
	}
	
	return TRUE;
}


void CODMATestDoc::GetDocInfo(WORD wItem, LPSTR lpszData, WORD dataLen, LPCSTR docId)
{
	// ODM_AUTHOR - Author of the document.
	// ODM_NAME - Name of the document.  This is a descriptive name for the document, not the filename.
	// ODM_TYPE - Type of the document.  This is typically an indication of the format or content of the document, i.e. correspondence, memo, contract, etc.
	// ODM_TITLETEXT - Suggested text to display in the document window's title bar.  This may include one or more fields from the document's profile and possibly other information as well.
	// ODM_CONTENTFORMAT - The format string indicating the format of the document's content.
	// ODM_DMS_DEFINED - The lpszData parameter contains a DMS-specific indication of the data to be returned. Note that an application must know which DMS it is talking to and must understand the data.
	// ODM_ALTERNATE_RENDERINGS - return a comma-separated list of format names representing the alternate formats it can return in ODMGetAlternateContent. 

	const ODMSTATUS odm = ODMGetDocInfo(odmHandle, (LPSTR) docId, wItem, lpszData, dataLen);
	switch(odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_DOCID:
		break;
	case ODM_E_ITEM:
		break;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		break;
	default:
		break;
	}
}


void CODMATestDoc::GetTitle(LPSTR lpszTitle, LPCSTR docId, LPCSTR lpszFormat)
{
	GetDocInfo(ODM_TITLETEXT, lpszTitle, ODM_TITLETEXT_MAX, docId);
	const size_t len = ODM_TITLETEXT_MAX;
	StringCchCat(lpszTitle, len, " (");
	StringCchCat(lpszTitle, len, lpszFormat);
	StringCchCat(lpszTitle, len, ")");
}

//Overrides
BOOL CODMATestDoc::OnNewDocument()
{   
	if (!CDocument::OnNewDocument())
		return FALSE;   

	CRichEditDoc::SetPathName("C:\\temp\\New Text Document", TRUE);
	
	return TRUE;
}


BOOL CODMATestDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if(m_bAppSel)
		return CRichEditDoc::OnOpenDocument(lpszPathName);
	strcpy_s(m_Format, Format);
	strcpy_s(m_DocId, DocId);
	GetTitle(m_TitleText, m_DocId, m_Format);
//	strcpy(m_TitleText, lpszPathName);
	
	CString strFormat(m_Format);
	
	if(strFormat.CompareNoCase(ODM_FORMAT_TEXT))
	{
 		if(!DMSOpenAlter(m_FileName))
			return FALSE;
	}
	else
	{
		if(!DMSOpenDoc(m_FileName))
			return FALSE;
	}

	if (!CRichEditDoc::OnOpenDocument(m_FileName))
		return FALSE;

	return TRUE;
}


BOOL CODMATestDoc::DoFileSave()
{
	OnFileSave();
	return TRUE;
}



void CODMATestDoc::OnCloseDocument()
{
	DMSCloseDoc();
	COleServerDoc::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CODMATestDoc serialization

void CODMATestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	CRichEditDoc::Serialize(ar);
}

// Discribe message map functions

void CODMATestDoc::OnFileSave()
{
	BOOL bOk;
	
	if(!*m_DocId)
		bOk = DMSSaveAsDoc();
	else
		if(m_bRTF)
			bOk = DMSSaveAlter();
		else
			bOk = DMSSaveDoc();
	
	if(bOk)
	{
		DoSave(m_FileName, FALSE);
		CRichEditDoc::SetPathName(m_TitleText, TRUE);
	}

}


void CODMATestDoc::OnFileSaveAs()
{
	BOOL bOk = FALSE;

	if(!*m_DocId)
		bOk = DMSSaveAsDoc();
	else
	{
		if(OnSelectType(m_DocId, m_Format, ODM_FORMATS))
		{
			CString strFormat(m_Format);
			if(strFormat.CompareNoCase(ODM_FORMAT_TEXT))
			{
				bOk = DMSSaveAlter();
			}
			else
				bOk = DMSSaveAsDoc();
		}
	}
	
	if(bOk)
	{
		DoSave(m_FileName, FALSE);
		CRichEditDoc::SetPathName(m_TitleText, TRUE);
	}

}


/////////////////////////////////////////////////////////////////////////////
// CODMATestDoc diagnostics

#ifdef _DEBUG
void CODMATestDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CODMATestDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// Function that work with DMS


BOOL CODMATestDoc::DMSNewDoc(LPSTR docId)
{
	if (!odmHandle)
		return FALSE;
  
	if(m_bUseEx)
		return TRUE;

	const ODMSTATUS odm = ODMNewDoc(odmHandle, docId, ODM_SILENT, ODM_FORMAT_TEXT, nullptr);
	switch(odm)
	{
	case ODM_SUCCESS:
		return TRUE;
	case ODM_E_CANCEL:
		break;
	case ODM_E_FAIL:
		break;
	case ODM_E_USERINT:
		break;
	case ODM_E_APPSELECT:
		break;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		break;
	default:
		break;
	}
	return FALSE;
}

BOOL CODMATestDoc::DMSOpenDoc(LPSTR FileName)
{
	if (!odmHandle || !*m_DocId)
		return FALSE;

	const DWORD dwFlag = 0;

	const ODMSTATUS odm = ODMOpenDoc(odmHandle, dwFlag, m_DocId, FileName);
	switch(odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_ACCESS:
		return FALSE;
	case ODM_E_INUSE:
		return FALSE;
	case ODM_E_DOCID:
		return FALSE;
	case ODM_E_USERINT: //if the ODM_SILENT
		return FALSE;
	case ODM_E_FAIL:
		return FALSE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		return FALSE;
	default:
		return FALSE;
	}
	
	m_bRTF = FALSE;

	return TRUE;
}


BOOL CODMATestDoc::DMSOpenAlter(LPSTR FileName)
{
	if(!m_bAlter)
		return FALSE;

	CString strFormat(m_Format);
	if(!strFormat.CompareNoCase(ODM_FORMAT_RTF))
	{
		DWORD dwFlags = 0;
		const ODMSTATUS odm = ODMGetAlternateContent(odmHandle, m_DocId,
			&dwFlags, m_Format, FileName);
		switch (odm)
		{
		case ODM_SUCCESS:
			break;
		case ODM_E_ACCESS:
			return FALSE;
		case ODM_E_INUSE :
			return FALSE;
		case ODM_E_DOCID:
			return FALSE;
		case ODM_E_OFFLINE:  
			return FALSE;
	//	case ODM_E_ARCHIVED: 
	//		break;
		case ODM_E_USERINT:  
			return FALSE;
		case ODM_E_INVARG:  
			return FALSE;
		case ODM_E_REQARG:  
			return FALSE;
		case ODM_E_NOSUPPORT:
			return FALSE;
		case ODM_E_FAIL:
			return FALSE;
		case ODM_E_HANDLE:
			odmHandle = nullptr;
			return FALSE;
		default:
			return FALSE;
		}
		
		m_bRTF = TRUE;
		return TRUE;
	}
	return FALSE;
}


void CODMATestDoc::DMSCloseDoc(LPSTR docId)
{
	if (!odmHandle)
		return;

	docId = docId ? docId:m_DocId;

	if (!*docId)
	{
		return;
	}

	DWORD dwFlags = ODM_SILENT;

	const ODMSTATUS odm = m_bUseEx ? ODMCloseDocEx(odmHandle, docId, &dwFlags, 0xFFFFFFFF,0xFFFFFFFF, nullptr, NULL)
			:ODMCloseDoc(odmHandle, docId, 0xFFFFFFFF, 0xFFFFFFFF, nullptr, NULL);
	switch (odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_NOOPEN:
		break;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		break;
	default:
		break;
	}
	*docId = NULL;
}


BOOL CODMATestDoc::DMSSaveDoc()
{
	if(!odmHandle)
		return FALSE;

	m_bRTF = FALSE;

	char doc_id[ODM_DOCID_MAX];
	DWORD dwFlags = ODM_SILENT;

	const ODMSTATUS odm = m_bUseEx ? ODMSaveDocEx(odmHandle, m_DocId, doc_id, &dwFlags)
				:ODMSaveDoc(odmHandle, m_DocId, doc_id);
	switch (odm)
	{
	case ODM_SUCCESS:
		strcpy_s(m_DocId, doc_id);
		break;
	case ODM_E_NOOPEN:
		return FALSE;
	case ODM_E_OPENMODE:
		return FALSE;
	case ODM_E_FAIL:
		return FALSE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		return FALSE;
	case ODM_E_CANCEL:  // -Ex function
		return FALSE;
	case ODM_E_USERINT:  // -Ex function
		return FALSE;
	case ODM_E_INVARG:  // -Ex function
		return FALSE;
	case ODM_E_OFFLINE:  // -Ex function
		return FALSE;
	default:
		return FALSE;
	}
	return TRUE;
}


BOOL CODMATestDoc::DMSSaveAsDoc()
{
 	if(!odmHandle)
		return FALSE;
  
	strcpy_s(DocId, m_DocId);
	
	if (!*DocId && !DMSNewDoc(DocId))
		return FALSE;
  
	DWORD dwFlags = 0;
	const ODMSTATUS odm = m_bUseEx ? ODMSaveAsEx(odmHandle, *DocId ? DocId : nullptr,
		m_DocId, ODM_FORMAT_TEXT, nullptr, nullptr, &dwFlags)
		:ODMSaveAs(odmHandle, DocId, m_DocId, ODM_FORMAT_TEXT, nullptr, nullptr);
	switch (odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_CANCEL:
		if(!*m_DocId && *DocId)
			ODMActivate(odmHandle, ODM_DELETE, DocId);
		return FALSE;
	case ODM_E_DOCID:
		return FALSE;
	case ODM_E_APPSELECT:
		return FALSE; 
	case ODM_E_OFFLINE:
		return FALSE; 
	case ODM_E_FAIL:
		return FALSE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		return FALSE;
	default:
		return FALSE;
	}
  
	if(!*m_DocId)
	{
		strcpy_s(m_DocId, DocId);
		*DocId = NULL;
	}

	strcpy_s(m_Format, ODM_FORMAT_TEXT);
	GetTitle(m_TitleText, m_DocId, m_Format);
	
	if(!DMSOpenDoc(m_FileName))
		return FALSE;

	DMSSaveDoc();

	if(*DocId)
	{
		DMSCloseDoc(DocId);
	}
	return TRUE;
}

BOOL CODMATestDoc::DMSSaveAlter()
{
	if(!m_bAlter)
		return FALSE;

	const BOOL bRTF = m_bRTF;
	
	if(!m_bRTF)
	{
		CString strFrmList;
		const WORD dataLen = ODM_FORMAT_MAX*5;
		LPSTR lpszListFrm = strFrmList.GetBuffer(dataLen);
		*lpszListFrm = NULL;

		CODMATestDoc::GetDocInfo(ODM_ALTERNATE_RENDERINGS, lpszListFrm, dataLen, m_DocId);
		strFrmList.ReleaseBuffer();
		if(strFrmList.Find(ODM_FORMAT_RTF)!=-1)
			DMSOpenAlter(m_FileName);
		else
		{
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath_s(m_FileName, drive, dir, fname, ext);
			_makepath_s(m_FileName, drive, dir, fname, "rtf");
		}

		m_bRTF = TRUE;
	}

	DWORD dwFlags = 0;
	const ODMSTATUS odm = ODMSetAlternateContent(odmHandle, m_DocId,
				&dwFlags, ODM_FORMAT_RTF, m_FileName);
	switch (odm)
	{
	case ODM_SUCCESS:
		break;
	case ODM_E_ACCESS:
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_INUSE :
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_DOCID:
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_OFFLINE:  
		m_bRTF = bRTF;
		return FALSE;
//	case ODM_E_ARCHIVED: 
//		break;
	case ODM_E_USERINT:  
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_INVARG:  
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_NOSUPPORT:
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_FAIL:
		m_bRTF = bRTF;
		return FALSE;
	case ODM_E_HANDLE:
		odmHandle = nullptr;
		m_bRTF = bRTF;
		return FALSE;
	default:
		m_bRTF = bRTF;
		return FALSE;
	}
	
	strcpy_s(m_Format, ODM_FORMAT_RTF);
	GetTitle(m_TitleText, m_DocId, m_Format);
 	return TRUE;
}
