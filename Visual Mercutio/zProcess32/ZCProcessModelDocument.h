// ZCProcessModelDocument.h : header file

#if !defined(AFX_ZCPROCESSMODELDOCUMENT_H__7E93C702_5D30_42EF_B694_0B86EF25FE4C__INCLUDED_)
#define AFX_ZCPROCESSMODELDOCUMENT_H__7E93C702_5D30_42EF_B694_0B86EF25FE4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_ProcessModelTree.h"

// JMR-MODIF - Le 14 juin 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelDocument view

class ZCProcessModelDocument : public PSS_ProcessModelTree, public PSS_Observer
{
public:

    DECLARE_DYNCREATE(ZCProcessModelDocument)

    ZCProcessModelDocument();
    virtual ~ZCProcessModelDocument();

    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Generated message map functions
protected:

    //{{AFX_MSG(ZCProcessModelDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif
