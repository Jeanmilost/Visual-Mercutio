// ZRes32.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE ZRes32DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Extension DLL one-time initialization
        if (!AfxInitExtensionModule(ZRes32DLL, hInstance))
            return 0;
        TRACE0("ZRES32.DLL Initializing!\n");
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("ZRES32.DLL Terminating!\n");
        // Terminate the library before destructors are called
        AfxTermExtensionModule(ZRes32DLL);
    }
    return 1;   // ok
}


// Exported DLL initialization is run in context of application
// or Regular DLL.   
extern "C" void WINAPI InitZRes32DLL()   
{
    TRACE0("ZRES32.DLL Initializing!\n");
    // Create a new CDynLinkLibrary for this app.
    new CDynLinkLibrary(ZRes32DLL);
}


