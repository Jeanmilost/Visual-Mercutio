// stdafx.h : Fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclure les en-t�tes Windows rarement utilis�s
#endif

// Modifiez les d�finitions suivantes si vous devez cibler une plate-forme avant celles sp�cifi�es ci-dessous.
// Reportez-vous � MSDN pour obtenir les derni�res informations sur les valeurs correspondantes pour les diff�rentes plates-formes.
#ifndef WINVER				// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows�95 et Windows NT�4 ou version ult�rieure.
#define WINVER 0x0400		// Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�98 et Windows�2000 ou version ult�rieure.
#endif

#ifndef _WIN32_WINNT		// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows NT�4 ou version ult�rieure.
#define _WIN32_WINNT 0x0400	// Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�2000 ou version ult�rieure.
#endif						

#ifndef _WIN32_WINDOWS		// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows�98 ou version ult�rieure.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�Me ou version ult�rieure.
#endif

#ifndef _WIN32_IE			// Autorise l'utilisation des fonctionnalit�s sp�cifiques � IE�4.0 ou version ult�rieure.
#define _WIN32_IE 0x0400	// Attribuez la valeur appropri�e � cet �l�ment pour cibler IE�5.0 ou version ult�rieure.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// certains constructeurs CString seront explicites

#include <afxwin.h>			// Composants MFC principaux et standard
#include <afxext.h>			// Extensions MFC

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>			// Classes OLE MFC
#include <afxodlgs.h>		// Classes de bo�te de dialogue OLE MFC
#include <afxdisp.h>		// Classes MFC Automation
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// Classes de base de donn�es ODBC MFC
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// Classes de base de donn�es DAO MFC
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// Prise en charge des MFC pour les contr�les communs Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Prise en charge des MFC pour les contr�les communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _ENABLETRACE			// If enable trace is defined
#include "zBaseLib\ZGTrace.h"
#endif

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include <CJ60Lib.h>		// CJ60 Library components

//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

#include "zConversion\zConversionLib.h"	// To include the zConversion library

#include <zBaseLib\zBaseLib.h>			// The base library
#include <zBaseSym\zBaseSymLib.h>		// The base symbol library
#include <zProperty\zPropertyLib.h>		// The property library
#include <zDB\zDBLib.h>					// The Database library
#include <zWinUtil32\zWinUtil32Lib.h>	// The windows utility library
#include <zEvent\zEventLib.h>			// The event library
#include <zRes32\zRes32Lib.h>			// Resource library
#include <zModel\zModelLib.h>			// The model library
#include <zModelBP\zModelBPLib.h>
#include <zModelWeb\zModelWebLib.h>
#include <zWeb\zWebLib.h>				// The web library
#include <zResMgr\zResMgrLib.h>			// The resource manager library

//this was added by Stingray Appwizard. If you wish to define _GXDLL
//as a preprocessor symbol you may remove this and add this definition to 
//the settings in Developer Studio. 
#ifdef _AFXDLL
#ifndef _GXDLL
#define _GXDLL
#endif
#endif
#include <grid\gxall.h>

// Use Objective Views as a DLL
#define _OVDLL

// Objective Views Header Files
#include "Views\OdAll.h"

// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"
