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


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD /*fdwReason*/, LPVOID /*lpvReserved*/)
{
	hInst = hModule;
	return 1;
}


/* ODMGetODMInterface - This is the main entry point for the ODMA connection
	manager. */
HRESULT WINAPI _export ODMGetODMInterface(REFIID riid, LPVOID *ppvObj,
LPUNKNOWN pUnkOuter, LPVOID /*pReserved*/, LPSTR /*lpszAppId*/, DWORD dwEnvData)
{
	*ppvObj = nullptr;        // Ensure NULL stored here in case of error return.

	// Create a new Application object.
	Application *pApp = new Application(pUnkOuter, dwEnvData);

	if(pApp == nullptr) {
		MessageBox(reinterpret_cast<HWND>(dwEnvData), "Memory allocation failure", DMSNAME, MB_OK );
		return ResultFromScode(E_OUTOFMEMORY);
	}

	// Get the requested interface on the application object.
	const HRESULT hRes = pApp->GetInterface(riid, ppvObj);

	if(*ppvObj)
		static_cast<LPUNKNOWN>(*ppvObj)->Release();  // Balances the ref. count from 'new'.
	else
		delete pApp;

	return hRes;
}
