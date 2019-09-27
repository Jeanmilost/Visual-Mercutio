// ******************************************************************************************************************
// *                                      Classe ZBLogicalRulesObserverMsg                                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZBLogicalRulesObserverMsg.                                *
// ******************************************************************************************************************
// * Cette classe est un observateur d'�v�nements pour les classes de gestion des r�gles.                            *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZBLogicalRulesObserverMsg.h"

#include "ZBRulesEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBLogicalRulesObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalRulesObserverMsg::ZBLogicalRulesObserverMsg(UINT                MessageID    /*= 0*/,
                                                     ZBRulesEntity*    pEntity        /*= NULL*/,
                                                     const CString        RootName    /*= _T( "" )*/) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEntity(pEntity),
    m_RootName(RootName)
{}

ZBLogicalRulesObserverMsg::~ZBLogicalRulesObserverMsg()
{}
