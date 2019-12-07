// **************************************************************************************************************
// *                                 Classe ZUExtractModelUnitGroupAssigned                                        *
// **************************************************************************************************************
// * @doc ZUExtractModelUnitGroupAssigned                                                                        *
// * @module ZUExtractModelUnitGroupAssigned.h | Interface of the <c ZUExtractModelUnitGroupAssigned> class.    *
// *                                                                                                            *
// * ProcessSoft Classes                                                                                        *
// * <nl>Copyright <cp> 2001 - ProcessSoft SA,                                                                    *
// * All rights reserved.                                                                                        *
// *                                                                                                            *
// * This source code is only intended as a supplement to                                                        *
// * the ProcessSoft Class Reference and related                                                                *
// * electronic documentation provided with the library.                                                        *
// * See these sources for detailed information regarding                                                        *
// * ProcessSoft products.                                                                                        *
// *                                                                                                            *
// * Author:       Dom                                                                                            *
// * <nl>Created:         07/2001                                                                                *
// * <nl>Description: ZUExtractModelUnitGroupAssigned navigates through the model and                            *
// *                  extract symbol where a unit is assigned                                                    *
// **************************************************************************************************************
// * Cette classe permet de d�terminer quelle syst�me logique est attibu�e � quel symbole. A partir de cette    *
// * liste, il est possible de reconstruire la hi�rarchie des liens existants entre symboles et syst�mes        *
// * externes.                                                                                                    *
// **************************************************************************************************************

#if !defined(AFX_ZUExtractModelUnitGroupAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUExtractModelUnitGroupAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModel\ZUModelNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserEntity;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 f�vrier 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUExtractModelUnitGroupAssigned

class AFX_EXT_CLASS ZUExtractModelUnitGroupAssigned : public ZUModelNavigation
{
public:

    ZUExtractModelUnitGroupAssigned(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUExtractModelUnitGroupAssigned();

    CODComponentSet& GetComponentSet()
    {
        return m_Set;
    };

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();

    virtual bool OnSymbol(ZBSymbol* pSymbol);
    virtual bool OnLink(PSS_LinkSymbol* pLink);

private:

    ZBUserEntity*    m_pUserEntity;
    CODComponentSet    m_Set;
};

#endif // !defined(AFX_ZUExtractModelUnitGroupAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)