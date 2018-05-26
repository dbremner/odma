/* doclist.cpp - This file contains the implementation of the document list
	object for the ODMA sample application.  This is a container object
	holding lists of Document objects. */

#include "stdafx.h"
#include <windows.h>
#include "odmasamp.h"
#include <assert.h>


DocumentList::DocumentList()
	:List{}
{
int i;
	char *entry;
    const size_t size = 2048;
	char *buff = new char[size];

	if(buff) {
		// Read in documents from previous session if any.
		GetPrivateProfileString("DocList", nullptr, "", buff, size, DMSINI);

		for(i=0, entry=buff; *entry; i++, entry += strlen(entry)+1)
			List[i] = new Document(entry);

		delete[] buff;
	}
}


DocumentList::~DocumentList()
{
	// Delete all the document objects in the list.
	for(auto & i : List) {
		delete i;
	}
}


Document* DocumentList::GetDocumentByIndex(int n)
{
	assert(n > 0);
	assert(n < _countof(List));
	if(List[n])
	{
		return List[n];
	}
	else
		return nullptr;
}


int DocumentList::GetDocumentIndexById(LPSTR lpszDocId)
{
	// ::ODMA\<DmsId>\<doc-specific>
	const int offset = 7+strlen(DMSID)+1;

	for(int i = 0; i<MAXDOCS; i++) {
		if(List[i] == nullptr)
			continue;

		char *lp = List[i]->GetId();

		if(!strcmp(lp, lpszDocId+offset)) {
			return i;
		}
	}//for

	return -1;
}


Document* DocumentList::GetDocumentById(LPSTR lpszDocId)
{
	const int n = GetDocumentIndexById(lpszDocId);

	if(n == -1)
		return nullptr;
	else
		return List[n];
}


ODMSTATUS DocumentList::NewDocument(LPSTR lpszFormat, LPSTR lpszDocLocation,
Document** ppDoc, DWORD dwFlags, HWND hParent)
{
int i;
ODMSTATUS err;

	for(i=0; i<MAXDOCS; i++) {
		if(List[i] == nullptr) 
		{
			// Found an empty slot.
			List[i] = new Document(lpszFormat, lpszDocLocation);

			if(List[i] == nullptr) 
			{
				err = ODM_E_FAIL;
				break;
			}

			if(dwFlags & ODM_SILENT) 
			{
				// Non-interactive mode. Fill in default values.
				List[i]->SetInfo(ODM_AUTHOR, "Default");
				List[i]->SetInfo(ODM_TYPE, "Default");
				err = 0;
			}
			else
				err = List[i]->EditAttributes( hParent );

			if(err) 
			{
				delete List[i];
				List[i] = nullptr;
				break;
			}

			*ppDoc = List[i];
			break;
		}//if
	}//for

	if(i == MAXDOCS) {
		MessageBox(nullptr, "Too many documents", DMSNAME,
			MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL );

		err = ODM_E_FAIL;
	}

	return err;
}


ODMSTATUS DocumentList::CopyDocument( LPSTR lpszDocId, Document **ppDoc,
HWND hParent )
{
int i;
ODMSTATUS err;

	Document *pOldDoc = GetDocumentById(lpszDocId);

	if(!pOldDoc)
		return ODM_E_DOCID;

	for(i=0; i<MAXDOCS; i++) {
		if(List[i] == nullptr) {
			// Found an empty slot.
			List[i] = new Document(pOldDoc);

			if(List[i] == nullptr) {
				err = ODM_E_FAIL;
				break;
			}

			err = List[i]->EditAttributes(hParent);

			if(err)
				break;

			*ppDoc = List[i];
			break;
		}
	}

	if(i == MAXDOCS) {
		MessageBox(nullptr, "Too many documents", DMSNAME,
			MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL );

		err = ODM_E_FAIL;
	}

	return err;
}


ODMSTATUS DocumentList::DeleteDocument( LPSTR lpszDocId )
{
	const int n = GetDocumentIndexById(lpszDocId);

	if(n == -1)
		return ODM_E_DOCID;

	delete List[n];
	List[n] = nullptr;
	return 0;
}


void DocumentList::SaveList()
{
	// First wipe out the previous list
	WritePrivateProfileString("DocList", nullptr, nullptr, "ODMASAMP.INI");

	// Now save each document's info. to the file.
	for(auto & i : List) {
		if(i)
			i->SaveInfo();
	}
}

