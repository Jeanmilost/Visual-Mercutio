// ******************************************************************************************************
// *                                  Classe ZVPublishConceptorReport                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 29 juin 2005 - Création de la nouvelle classe ZVPublishConceptorReport.                *
// * Cette classe effectue la publication des rapports en tant que pages Internet.                        *
// ******************************************************************************************************

#if !defined(AFX_ZVPUBLISHCONCEPTORREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHCONCEPTORREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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
#include "zBaseSym\PSS_BasicSymbolVisitor.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"
#include "zWeb\PSS_HtmlFile.h"
#include "PSS_Constants.h"

#ifdef _ZREPORTWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// ******************************************************************************************************
// *                                                 Enumérateurs                                        *
// ******************************************************************************************************

// Enumérateur représentant l'opération d'exportation en cours.
enum AFX_EXT_CLASS ZVPublishConceptorProc
{
    PUBLISH_CONCEPTOR_HEADERS,
    PUBLISH_CONCEPTOR_DETAILS,
};

// ******************************************************************************************************
// *                                       Classe ZVPublishConceptorReport                                *
// ******************************************************************************************************
class AFX_EXT_CLASS ZVPublishConceptorReport : public PSS_BasicSymbolVisitor
{
public:

    ZVPublishConceptorReport(ZDProcessGraphModelMdlBP* pModel = NULL,
                             BOOL bShowDetails = TRUE,
                             BOOL bShowDeliverables = TRUE);

    virtual ~ZVPublishConceptorReport();

    bool Publish(CString Directory);

private:

    void GeneratePageFile(CString Name, CString Description);

    bool CreateFileSystem(ZBUserGroupEntity* pGroup, CString Directory);
    bool CreateProcess();
    bool StartSection(CODNodeArray& Nodes);
    bool OnDoorSymbol(ZBBPDoorSymbol* pSymbol);
    bool OnPageSymbol(ZBBPPageSymbol* pSymbol);
    bool OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol);
    bool OnProcessSymbol(ZBBPProcessSymbol* pSymbol);
    bool OnStartSymbol(ZBBPStartSymbol* pSymbol);
    bool OnStopSymbol(ZBBPStopSymbol* pSymbol);
    bool OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);
    bool OnSymbol(ZBSymbol* pSymbol);
    bool OnLink(PSS_LinkSymbol* pLink);

    virtual bool Visit(CODComponent& Symbol);

    CString GenerateFileName(CString Directory, CString EntityName);

    void WriteLine(CString Text);
    void WriteLine(int nID);

private:

    ZDProcessGraphModelMdl*                m_pRootModel;
    ZDProcessGraphModelMdlBP*            m_pModel;
    PSS_ProcessGraphModelDoc*                m_pSourceDoc;
    ZBBPProcessSymbol*                    m_pPreviousProcess;

    PSS_HtmlFile                          HtmlFile;

    PSS_PublishModelGenerateDialog        m_FileGenerateWindow;

    CString                                m_DomainName;
    CString                                m_UnitName;
    CString                                m_CurrentProcessName;

    BOOL                                m_ShowDetails;
    BOOL                                m_IncludeDeliverables;

    bool                                m_First;

    ZVPublishConceptorProc                PublishProc;
};

#endif
