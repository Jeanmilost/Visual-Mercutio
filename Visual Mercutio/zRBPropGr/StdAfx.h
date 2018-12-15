// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__74DEAE00_6E2D_4760_9537_8EBBD2A17DD8__INCLUDED_)
#define AFX_STDAFX_H__74DEAE00_6E2D_4760_9537_8EBBD2A17DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WINVER 0x0501

// Version de Winver d�finie pour Windows NT4 et sup�rieures.
#ifndef WINVER
#define WINVER 0x0400
#endif

// Plateforme cible d�finie � Windows NT4 et sup�rieures pour les versions NT de Windows.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif                        

// Plateforme cible d�finie � Windows98 et sup�rieures pour les versions standards de Windows.
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

// Internet Explorer d�finie � la version NT4.
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>            // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>            // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__74DEAE00_6E2D_4760_9537_8EBBD2A17DD8__INCLUDED_)
