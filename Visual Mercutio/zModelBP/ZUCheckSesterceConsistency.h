/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckSesterceConsistency
//@module ZUCheckSesterceConsistency.h | Interface of the <c ZUCheckSesterceConsistency> class.
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
// Author:       Dom
// <nl>Created:         06/2001
// <nl>Description:  ZUCheckSesterceConsistency deep sesterce check
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCheckSesterceConsistency_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCheckSesterceConsistency_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseSym\PSS_BasicSymbolVisitor.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Log;
class PSS_Symbol;
class PSS_LinkSymbol;
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class PSS_ProcessGraphModelMdl;

// JMR-MODIF - Le 17 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUCheckSesterceConsistency : public PSS_BasicSymbolVisitor
{
public:

    ZUCheckSesterceConsistency(PSS_ProcessGraphModelMdl* pModel = NULL, PSS_Log* pLog = NULL);
    virtual ~ZUCheckSesterceConsistency();

    bool CheckModel();

    size_t GetErrorCounter() const
    {
        return m_ErrorCounter;
    };

    size_t GetWarningCounter() const
    {
        return m_WarningCounter;
    };

    /**
    * Visits the target symbol
    *@param symbol - target symbol to visit
    *@return true if visit succeeded, otherwise false
    */
    virtual bool Visit(CODComponent& symbol);

private:

    bool CheckDoorSymbol(ZBBPDoorSymbol* pSymbol);
    bool CheckPageSymbol(ZBBPPageSymbol* pSymbol);
    bool CheckProcedureSymbol(ZBBPProcedureSymbol* pSymbol);
    bool CheckProcessSymbol(ZBBPProcessSymbol* pSymbol);
    bool CheckStartSymbol(ZBBPStartSymbol* pSymbol);
    bool CheckStopSymbol(ZBBPStopSymbol* pSymbol);
    bool CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);
    bool CheckSymbol(PSS_Symbol* pSymbol);
    bool CheckLink(PSS_LinkSymbol* pLink);

private:

    PSS_Log*                  m_pLog;
    PSS_ProcessGraphModelMdl* m_pModel;
    size_t                    m_ErrorCounter;
    size_t                    m_WarningCounter;
};

#endif
