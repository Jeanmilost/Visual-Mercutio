/////////////////////////////////////////////////////////////////////////////
//@doc zIso8859
//@module zIso8859.cpp | Header of the <c zIso8859> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 04/2002
// 
/////////////////////////////////////////////////////////////////////////////

#ifndef ziso8859_h
#define ziso8859_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "String16.h"
#include <string>

#ifdef _ZCONVERSIONEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 janvier 2007 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS zIso8859
{
public:

	static std::string ANSItoISO8859( std::string& inStr );
	static std::string ISO8859toANSI( std::string& inStr );
};

#endif