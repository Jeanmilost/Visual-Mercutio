/****************************************************************************
 * ==> PSS_SystemEntity ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system entity                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SystemEntity.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SystemEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SystemEntity
//---------------------------------------------------------------------------
PSS_SystemEntity::PSS_SystemEntity(const CString&    name,
                                   const CString&    description,
                                   PSS_SystemEntity* pParent) :
    CObject(),
    m_pParent(pParent),
    m_EntityName(name),
    m_EntityDescription(description)
{
    CreateGUID();
}
//---------------------------------------------------------------------------
PSS_SystemEntity::~PSS_SystemEntity()
{}
//---------------------------------------------------------------------------
void PSS_SystemEntity::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_GUID;
        ar << m_EntityName;
        ar << m_EntityDescription;
    }
    else
    {
        // read the elements
        ar >> m_GUID;
        ar >> m_EntityName;
        ar >> m_EntityDescription;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SystemEntity::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SystemEntity::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_SystemEntity::CreateGUID()
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
