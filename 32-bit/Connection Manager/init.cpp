/* init.cpp - Module initialization and global variables for ODMA connection
              manager.
 *
 * COPYRIGHT (C) 1994, 1995, 1996
 * AIIM International
 * All Rights Reserved

 Created 5/5/94 by BHC.
*/

#include <windows.h>
#include <objbase.h>

#include "initguid.h"
#include "conman.h"

ODMRegistry Registry;                  // Global registry object
HINSTANCE hInst;						// Global App Instance

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hModule;
	return 1;
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
	MessageBox(nullptr, "This version of the ODMA Connection Manager is expired",
	"ODMA Connection Manager", MB_ICONSTOP | MB_TASKMODAL);
	return TRUE;
}

/*************************************************************
Function for display an error message.
ODMA 2.0 1997 Ivan
*************************************************************/
void ErrorMessage(UINT strId)
{
	char strErr[MAXERRSTRING];

	LoadString(hInst, strId, strErr, _countof(strErr));
	MessageBox(nullptr, strErr, "ODMA Connection Manager", MB_ICONSTOP | MB_TASKMODAL);
}

/*************************************************************
Function for write information into logging file.
ODMA 2.0 1997 Ivan
LogString - direct write, 3 other is casing.
*************************************************************/

void LogParString(const char *lpszParam, const char *str, WORD wLen, WORD wCount)
{
	LogString("\t");
	LogString(lpszParam);
	LogString("=") ;

	if(!str||!*str)
	{
		LogString("Not Defined");
		LogString("\r\n") ;
		return;
	}

	LogString(str);

	for(WORD i = 1; i<wCount; i++)
	{
		LogString(", ");
		LogString(&str[wLen*i]);
	}

	LogString(";");
	LogString("\r\n") ;
}

void LogParNumber(const char *lpszParam, ULONG lvalue)
{
	LogString("\t");
	LogString(lpszParam);
	LogString("=");

	char szValue10[32];
	_ltoa_s(lvalue, szValue10, 10);
	char szValue16[32];
	_ltoa_s(lvalue, szValue16, 16);

	LogString(szValue10);
	LogString("(");
	LogString(szValue16);
	LogString(")");
	LogString("\r\n");
}

void LogParList(const char *lpszParam, const char *str )
{
	LogString("\t");
	LogString(lpszParam);
	LogString("=");
	
	if(!str||!*str)
	{
		LogString("Not Defined");
		LogString("\r\n");
		return;
	}
	
	LPCSTR lpPosBrk = str;
	LogString(lpPosBrk);
	lpPosBrk = strchr(lpPosBrk, NULL) + 1;

	while(*lpPosBrk) 
	{
		LogString(",");
		LogString(lpPosBrk);
		lpPosBrk = strchr(lpPosBrk, NULL) + 1;
	}
	
	LogString(";");
	LogString("\r\n");
}

void LogString(const char *str)
{
	if(!str||!*str)
		return;

	HANDLE hFile = Registry.GetLogFile();

	if(hFile == INVALID_HANDLE_VALUE)
		return;

	DWORD bw = 0;
	SetFilePointer(hFile, bw, nullptr, FILE_END);
	WriteFile(hFile, str, (DWORD)strlen(str), &bw, nullptr);
	CloseHandle(hFile);
}

