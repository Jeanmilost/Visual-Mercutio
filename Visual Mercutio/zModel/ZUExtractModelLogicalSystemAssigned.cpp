// **************************************************************************************************************
// *                              Classe ZUExtractModelLogicalSystemAssigned                                    *
// **************************************************************************************************************
// * Cette classe permet de d�terminer quelle unit� est attibu�e � quel symbole. A partir de cette liste, il    *
// * est possible de reconstruire la hi�rarchie des liens existants entre symboles et unit�s logiques.            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ProcGraphModelMdl.h"
#include "ZUExtractModelLogicalSystemAssigned.h"

#include "ZBSystemEntity.h"

#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 f�vrier 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractModelLogicalSystemAssigned::ZUExtractModelLogicalSystemAssigned(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                         void*                        pClass    /*= NULL*/)
    : ZUModelNavigation(pModel, pClass)
{}

ZUExtractModelLogicalSystemAssigned::~ZUExtractModelLogicalSystemAssigned()
{}

bool ZUExtractModelLogicalSystemAssigned::OnStart()
{
    m_pLogicalSystem = static_cast<ZBSystemEntity*>(m_pClass);

    if (!m_pLogicalSystem)
    {
        return false;
    }

    // Remove all elements from the set
    m_Set.RemoveAll();

    // Nothing more to do
    return true;
}

bool ZUExtractModelLogicalSystemAssigned::OnFinish()
{
    return true;
}

bool ZUExtractModelLogicalSystemAssigned::OnSymbol(ZBSymbol* pSymbol)
{
    if (pSymbol->ExtAppExist(m_pLogicalSystem->GetEntityName()) ||
        pSymbol->ExtAppExist(m_pLogicalSystem->GetGUID()))
    {
        m_Set.Add(pSymbol);
    }

    return true;
}
bool ZUExtractModelLogicalSystemAssigned::OnLink(PSS_LinkSymbol* pLink)
{
    if (pLink->ExtAppExist(m_pLogicalSystem->GetEntityName()) ||
        pLink->ExtAppExist(m_pLogicalSystem->GetGUID()))
    {
        m_Set.Add(pLink);
    }

    return true;
}
