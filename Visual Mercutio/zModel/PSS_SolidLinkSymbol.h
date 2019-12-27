/****************************************************************************
 * ==> PSS_SolidLinkSymbol -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a solid link symbol                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SolidLinkSymbolH
#define PSS_SolidLinkSymbolH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_LinkSymbol.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Solid link symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SolidLinkSymbol : public PSS_LinkSymbol
{
    public:
        PSS_SolidLinkSymbol();
        virtual ~PSS_SolidLinkSymbol();
};

#endif
