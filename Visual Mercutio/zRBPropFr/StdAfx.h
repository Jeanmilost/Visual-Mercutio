/****************************************************************************
 * ==> StdAfx.h ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file for standard system files, or project         *
 *               specific include files that are used frequently, but are   *
 *               changed infrequently                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__19DF746B_A2CD_41D3_B25F_7BA1105D6A34__INCLUDED_)
#define AFX_STDAFX_H__19DF746B_A2CD_41D3_B25F_7BA1105D6A34__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

#ifndef WINVER
    #define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif                        

#ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
    #define _WIN32_IE 0x0400
#endif

// mfc
#include <afxwin.h>       // MFC core and standard components
#include <afxext.h>       // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
    #include <afxole.h>   // MFC OLE classes
    #include <afxodlgs.h> // MFC OLE dialog classes
    #include <afxdisp.h>  // MFC Automation classes
#endif

#ifndef _AFX_NO_DB_SUPPORT
    #include <afxdb.h>    // MFC ODBC database classes
#endif

#ifndef _AFX_NO_DAO_SUPPORT
    #include <afxdao.h>   // MFC DAO database classes
#endif

#include <afxdtctl.h>     // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>   // MFC support for Windows Common Controls
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__19DF746B_A2CD_41D3_B25F_7BA1105D6A34__INCLUDED_)
