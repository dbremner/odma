/* document.cpp - Document class for ODMA sample DMS.
 *
 * COPYRIGHT (C) 1994, 1995
 * AIIM International
 * All Rights Reserved
 */

#include <windows.h>
#include <dos.h>
#include "odmasamp.h"
#include <stdlib.h>
#include <assert.h>

Document::Document()
{
	Init();
}

//Create new document
Document::Document(LPSTR lpszFormat, LPSTR lpszDocLocation)
{
	Init();
	strcpy_s(Format[0], lpszFormat);

	if(lpszDocLocation) 
	{
		strcpy_s(DocLocation[0], lpszDocLocation);
		DocAccessed = 1;
	}
}

//Create document as the copy
Document::Document(Document *pOldDoc)
{
	Init();
	bEdited = pOldDoc->bEdited; //BVG:
	strcpy_s(Author, pOldDoc->Author);
	strcpy_s(Name, pOldDoc->Name);
	strcpy_s(DocType, pOldDoc->DocType);

	//BVG Copy first component attributes
	iComponents = 1;
	strcpy_s(Format[0], pOldDoc->Format[0]);
}


// Load a document saved from a previous session
Document::Document(LPSTR lpszDocId)
{
	strcpy_s(DocId, lpszDocId);
	SaveFlag = 0;
	OpenCount = 0;
	DocAccessed = 1;	// It was accessed in a previous session.

	//BVG: assunption: that all profiles has been edited at previous seseion 
	bEdited=TRUE;

	GetPrivateProfileString(DocId, "Author", "", Author, sizeof(Author), DMSINI);
	GetPrivateProfileString(DocId, "Name", "", Name, sizeof(Name), DMSINI);
	GetPrivateProfileString(DocId, "DocType", "", DocType, sizeof(DocType), DMSINI);

	//BVG: Load components properties
	iComponents = GetPrivateProfileInt(DocId, "Components", 0, DMSINI);
	for( int ii=0; ii<iComponents; ii++)
	{
		char szKey[20];
		snprintf(szKey, sizeof(szKey), "%s%d", "Format", ii);
		GetPrivateProfileString(DocId, szKey, "", Format[ii], sizeof(Format[ii]), DMSINI);
		snprintf(szKey, sizeof(szKey), "%s%d", "DocLocation", ii);
		GetPrivateProfileString(DocId, szKey, "", DocLocation[ii], sizeof(DocLocation[ii]), DMSINI);
	}
}


void Document::Init(void)
{
SYSTEMTIME tm;


	bEdited = FALSE; //BVG:
	SaveFlag = 0;
	Author[0] = '\0';
	Name[0] = '\0';
	DocType[0] = '\0';
	OpenCount = 0;

	//BVG Init first component
	iComponents=1;
	Format[0][0] = '\0';
	DocLocation[0][0] = '\0';

	DocAccessed = 0;

	GetLocalTime(&tm);

	if(tm.wMilliseconds > 99)
		tm.wMilliseconds /= 10;

	sprintf_s(DocId, "%02d-%02d-%02d-%02d", tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
}


ODMSTATUS Document::Open(LPSTR lpszFileName)
{
	OpenCount++;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	if(DocLocation[0][0] == '\0') 
	{
		char szTmpPath[256];

		// WIN32 requires you to get a temp path first, then pass it to get
		// a temp filename.
		GetTempPath(_countof(szTmpPath), szTmpPath);
		GetTempFileName(szTmpPath, "ODM", 0, DocLocation[0]);
		_splitpath_s(DocLocation[0], drive, dir, fname, ext);
		_makepath_s(DocLocation[0], drive, dir, fname, "txt");
	}

	strcpy(lpszFileName, DocLocation[0]);
	DocAccessed = 1;
	return 0;
}


ODMSTATUS Document::Close(DWORD activeTime, DWORD pagesPrinted,
LPVOID sessionData, WORD dataLen)
{
	OpenCount--;
	return 0;
}


ODMSTATUS Document::EditAttributes(HWND hParent)
{
ProDlgData pdData;

	pdData.pDocument = this;
	pdData.Mode = PROFILE_EDIT;

	int err = DialogBoxParam(hInst, MAKEINTRESOURCE(PROFILE_DIALOG), hParent,
	                         (DLGPROC)ProfileProc, (LPARAM)&pdData);

	if(err == IDOK)
	{
		bEdited=TRUE; //BVG:
		err = 0;
	}
	else
		err = ODM_E_CANCEL;

	return err;
}


ODMSTATUS Document::ShowAttributes(HWND hParent)
{
ProDlgData pdData;

	pdData.pDocument = this;
	pdData.Mode = 0;

	DialogBoxParam(hInst, MAKEINTRESOURCE(PROFILE_DIALOG), hParent,
		(DLGPROC)ProfileProc, (LPARAM)&pdData);

	return 0;
}


ODMSTATUS Document::GetInfo( WORD item, LPSTR lpszData, WORD dataLen )
{
ODMSTATUS err;
char *dataSource;
char szFormatNames[MAXCOMPONENTS * (ODM_FORMAT_MAX + 1)];
char buff[165];

	switch(item) {
		case ODM_AUTHOR: dataSource = Author; break;
		case ODM_NAME: dataSource = Name; break;
		case ODM_TYPE: dataSource = DocType; break;
		case ODM_TITLETEXT:
			sprintf_s(buff, "%s - %s", DocId, Name);
			dataSource = buff;
			break;

		case ODM_CONTENTFORMAT: 
			//BVG:
			dataSource = Format[0]; 
		break;

		//BVG: Build comma-separated list of content format names  
		case ODM_ALTERNATE_RENDERINGS:
		{
			strcpy_s(szFormatNames, "");
			for(int ii=0; ii<iComponents; ii++)
			{
				strcat_s(szFormatNames, Format[ii]);
				strcat_s(szFormatNames, ",");
				if(strlen(szFormatNames) > dataLen) return ODM_E_TRUNCATED;
			}
			const size_t len = strlen(szFormatNames);
			assert(len > 0);
			const size_t last_comma = len - 1;
			szFormatNames[last_comma] = '\0';
			dataSource = szFormatNames; 
		}
		break;

		default: dataSource = nullptr;
	}

	if(dataSource) 
	{
		strncpy(lpszData, dataSource, dataLen);
		lpszData[dataLen-1] = '\0';
		err = ODM_SUCCESS;
	} else
		err = ODM_E_ITEM;

	return err;
}


ODMSTATUS Document::SetInfo( WORD item, LPSTR lpszData )
{
char *target;
int len;
ODMSTATUS err;

	switch(item) 
	{
		case ODM_AUTHOR: target = Author; len = sizeof(Author); break;
		case ODM_NAME: target = Name; len = sizeof(Name); break;
		case ODM_TYPE: target = DocType; len = sizeof(DocType); break;
		case ODM_CONTENTFORMAT:
			//BVG:
			target = Format[0]; 
			len = sizeof(Format[0]);
			break;
		default: target = nullptr;
	}

	if(target) 
	{
		strncpy(target, lpszData, len);
		target[len-1] = '\0';
		err = 0;
	} else
		err = ODM_E_ITEM;

	return err;
}


void Document::SaveInfo(void)
{
	// Put the docId into the DocList section.
	WritePrivateProfileString("DocList", DocId, "", DMSINI);

	// Put the document's info. into its own section
	WritePrivateProfileString(DocId, "Author", Author, DMSINI);
	WritePrivateProfileString(DocId, "Name", Name, DMSINI);
	WritePrivateProfileString(DocId, "DocType", DocType, DMSINI);

	//BVG:
	for( int ii=0; ii<iComponents; ii++)
	{
		char	szValue[20];
		char	szKey[20];

		sprintf_s(szValue, "%d", iComponents);
		WritePrivateProfileString(DocId, "Components", szValue, DMSINI);

		sprintf_s(szKey, "%s%d", "Format", ii);
		WritePrivateProfileString(DocId, szKey, Format[ii], DMSINI);

		sprintf_s(szKey, "%s%d", "DocLocation", ii);
		WritePrivateProfileString(DocId, szKey, DocLocation[ii], DMSINI);
	}
}

//BVG:
//Add new component, Content Format Name & Doc Location
ODMSTATUS Document::AddComponent(LPSTR lpszFormat, LPSTR lpszDocLocation)
{
	if(iComponents==MAXCOMPONENTS) return ODM_E_FAIL;

	iComponents++;
	strcpy_s(Format[iComponents-1], lpszFormat);
	strcpy_s(DocLocation[iComponents-1], lpszDocLocation);
	return ODM_SUCCESS;
}

//BVG:
//Set DocLocation for speciffic Content Format Name
ODMSTATUS Document::SetComponent(LPSTR lpszFormat, LPSTR lpszDocLocation)
{
	for(int ii=0; ii<iComponents; ii++)
	{
		if( strcmp(Format[ii], lpszFormat) == 0 )
		{
			strcpy_s(DocLocation[ii], lpszDocLocation);
			return ODM_SUCCESS;
		}
	}

	return AddComponent(lpszFormat, lpszDocLocation);
}

//BVG:
ODMSTATUS Document::DeleteComponent(LPSTR lpszFormat)
{
	for(int ii=0; ii<iComponents; ii++)
	{
		if( strcmp(Format[ii], lpszFormat) == 0 )
		{
			for(int jj=ii; jj<iComponents-1; jj++)
			{
				strcpy_s(DocLocation[jj], DocLocation[jj+1]);
				strcpy_s(Format[jj], Format[jj+1]);
			}
			iComponents--;
			return ODM_SUCCESS;
		}
	}
	return ODM_E_FAIL;	
}

//BVG:
//Get DocLocation for specific Content Format Name
ODMSTATUS Document::GetComponent(LPSTR lpszFormat, LPSTR lpszDocLocation)
{
	for(int ii=0; ii<iComponents; ii++)
	{
		if( strcmp(Format[ii], lpszFormat) == 0 )
		{
			strcpy(lpszDocLocation, DocLocation[ii]);
			return ODM_SUCCESS;
		}
	}
	return ODM_E_FAIL;
}
