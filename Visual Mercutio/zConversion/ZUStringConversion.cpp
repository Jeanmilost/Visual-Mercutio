/////////////////////////////////////////////////////////////////////////////
//@doc ZUStringConversion
//@module ZUStringConversion.cpp | Implementation of the <c ZUStringConversion> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 05/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUStringConversion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUStringConversion::ZUStringConversion()
{
}

ZUStringConversion::~ZUStringConversion()
{
}

// Cette fonction permet de convertir tous les caract�res sp�ciaux d'une cha�ne de caract�res.
CString ZUStringConversion::ConvertSpecialChar( CString s )
{
	// Replace all dot and : by underscore
	char* p = s.GetBuffer( s.GetLength() + 1 );

	// Copy char after the decimal point, till the end
	while ( *p )
	{
		if ( *p == ' ' || *p == '.' || *p == ':'  || *p == '�'  || *p == '?'  || *p == '<'  || *p == '>' ||
			 *p == '=' || *p == '!' || *p == '\'' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '~' )
		{
			*p = '_';
		}
		else if ( *p == '�' || *p == '�' || *p == '�' )
		{
			*p = 'e';
		}
		else if ( *p == '�' || *p == '�' || *p == '�' )
		{
			*p = 'a';
		}
		else if ( *p == '�' || *p == '�' )
		{
			*p = 'i';
		}
		else if ( *p == '�' )
		{
			*p = 'o';
		}
		else if ( *p == '�' )
		{
			*p = 'c';
		}
		else if ( *p == '�' || *p == '�' || *p == '�' )
		{
			*p = 'u';
		}

		++p;
	}

	// Don't forget to release the buffer
	s.ReleaseBuffer( -1 );

	return s;
}
