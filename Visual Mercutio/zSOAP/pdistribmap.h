/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:         03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PDISTRIBMAP_HDR_
#define __PDISTRIBMAP_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"
string convertTo( String16 inStr );

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS pdistribmap
{
public:

    pdistribmap()
    {
    }

    pdistribmap( int pdattribid, int attribdefid, String16 mdata, int mlop )
    {
        this->pdattribid    = pdattribid;
        this->attribdefid    = attribdefid;
        this->mdata            = convertTo( mdata );
        this->mlop            = mlop;
    }

    int        pdattribid;
    int        attribdefid;    
    string    mdata;    
    int        mlop;
};

#endif