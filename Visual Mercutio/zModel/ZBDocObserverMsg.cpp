// ZBDocObserverMsg.cpp: implementation of the ZBDocObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDocObserverMsg.h"
#include "PSS_Symbol.h"
#include "PSS_ProcessGraphModelDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 ao�t 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC(ZBDocObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDocObserverMsg::ZBDocObserverMsg(MessageActionType        actionType    /*= NoAction*/,
                                   PSS_ProcessGraphModelDoc*    pDoc        /*= NULL*/,
                                   PSS_ProcessGraphModelMdl*    pModel        /*= NULL*/,
                                   CODSymbolComponent*        pElement    /*= NULL*/) :
    PSS_ObserverMsg(),
    m_ActionType(actionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pElement(pElement)
{}

ZBDocObserverMsg::~ZBDocObserverMsg()
{}
