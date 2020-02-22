// ZUProcessCalculateTotals.cpp: implementation of the ZUProcessCalculateTotals class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessCalculateTotals.h"

#include "ZUProcedureCalculateTotals.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 mars 2006 - Ajout des d�clarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessCalculateTotals::ZUProcessCalculateTotals(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                   void*                    pClass    /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUProcessCalculateTotals::~ZUProcessCalculateTotals()
{}

bool ZUProcessCalculateTotals::OnStart()
{
    m_ProcedureCost = 0;
    m_ProcedureWorkloadForecast = 0;
    m_ProcedureCostForecast = 0;

    // Reset all members
    return true;
}

bool ZUProcessCalculateTotals::OnFinish()
{
    return true;
}

bool ZUProcessCalculateTotals::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcessCalculateTotals::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcessCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcessCalculateTotals::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    // Now initiate the procedure totals for the process
    ZUProcedureCalculateTotals ProcedureTotals(dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel()),
                                               NULL);

    if (ProcedureTotals.Navigate())
    {
        // The total procedure workload forecast
        pSymbol->SetProcessWorkloadForecast(ProcedureTotals.GetProcedureWorkloadForecast());

        // The procedure cost forecast
        pSymbol->SetProcessCostForecast(ProcedureTotals.GetProcedureCostForecast());

        // JMR-MODIF - Le 14 mars 2006 - Ajout de la prise en charge du co�t HMO pour les processus.
        pSymbol->SetProcessCostHMO(ProcedureTotals.GetProcedureCost());
    }

    return true;
}

bool ZUProcessCalculateTotals::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcessCalculateTotals::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    return true;
}

bool ZUProcessCalculateTotals::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    return true;
}
