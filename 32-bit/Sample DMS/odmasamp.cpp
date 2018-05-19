/* odmasamp.cpp - Entry point, initialization, cleanup, etc. for ODMA
	sample DMS.
 *
 * COPYRIGHT (C) 1994, 1995
 * AIIM International
 * All Rights Reserved
 */

#include <windows.h>


#include <initguid.h>
#include "odmacom.h"
#include "odmasamp.h"

#include <objbase.h>

// Globals
HINSTANCE hInst;
DocumentList DocList;


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hModule;
	return 1;
}


/* ODMGetODMInterface - This is the main entry point for the ODMA connection
	manager. */
HRESULT WINAPI _export ODMGetODMInterface(REFIID riid, LPVOID *ppvObj,
LPUNKNOWN pUnkOuter, LPVOID pReserved, LPSTR lpszAppId, DWORD dwEnvData)
{            

#ifdef _TIME_BOMB	
	if(TimeBomb(1998, 3))
		return (HRESULT) E_FAIL;
#endif

	Application *pApp;
	HRESULT hRes;

	*ppvObj = nullptr;        // Ensure NULL stored here in case of error return.

	// Create a new Application object.
	pApp = new Application(pUnkOuter, dwEnvData);

	if(pApp == nullptr) {
		MessageBox((HWND)dwEnvData, "Memory allocation failure", DMSNAME, MB_OK );
		return ResultFromScode(E_OUTOFMEMORY);
	}

	// Get the requested interface on the application object.
	hRes = pApp->GetInterface(riid, ppvObj);

	if(*ppvObj)
		((LPUNKNOWN)(*ppvObj))->Release();  // Balances the ref. count from 'new'.
	else
		delete pApp;

	return hRes;
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

	MessageBox(nullptr, "This version of the ODMA Sample DMS is expired",
	"ODMA Sample DMS", MB_ICONSTOP | MB_TASKMODAL);
	return TRUE;
}
