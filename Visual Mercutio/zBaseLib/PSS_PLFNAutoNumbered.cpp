/****************************************************************************
 * ==> PSS_PLFNAutoNumbered ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an financial plan auto-numbered object            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNAutoNumbered.h"

// processsoft
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNAutoNumbered, PSS_PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNAutoNumbered
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::PSS_PLFNAutoNumbered() :
    PSS_PlanFinObject(),
    m_pObject(NULL),
    m_TextOffset(20),
    m_SectionNumber(0),
    m_Level(0),
    m_AutoCalculate(TRUE)
{}
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::PSS_PLFNAutoNumbered(const PSS_PLFNAutoNumbered& other) :
    PSS_PlanFinObject(),
    m_pObject(NULL),
    m_TextOffset(20),
    m_SectionNumber(0),
    m_Level(0),
    m_AutoCalculate(TRUE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::~PSS_PLFNAutoNumbered()
{
    if (m_pObject)
        delete m_pObject;
}
//---------------------------------------------------------------------------
const PSS_PLFNAutoNumbered& PSS_PLFNAutoNumbered::operator = (const PSS_PLFNAutoNumbered& other)
{
    PSS_PlanFinObject::operator = ((inherited&)other);
    m_TextLevel     = other.m_TextLevel;
    m_pObject       = other.m_pObject->Clone();
    m_TextOffset    = other.m_TextOffset;
    m_SectionNumber = other.m_SectionNumber;
    m_Level         = other.m_Level;
    m_AutoCalculate = other.m_AutoCalculate;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNAutoNumbered& PSS_PLFNAutoNumbered::operator = (const PSS_PLFNAutoNumbered* pOther)
{
    PSS_PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_pObject       = NULL;
        m_TextOffset    = 20;
        m_SectionNumber = 0;
        m_Level         = 0;
        m_AutoCalculate = TRUE;
    }
    else
    {
        m_TextLevel     = pOther->m_TextLevel;
        m_pObject       = pOther->m_pObject->Clone();
        m_TextOffset    = pOther->m_TextOffset;
        m_SectionNumber = pOther->m_SectionNumber;
        m_Level         = pOther->m_Level;
        m_AutoCalculate = pOther->m_AutoCalculate;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNAutoNumbered::Clone() const
{
    return new PSS_PLFNAutoNumbered(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNAutoNumbered*>(pSrc));
}
//---------------------------------------------------------------------------
CString PSS_PLFNAutoNumbered::GetFormattedObject()
{
    if (m_pObject)
        return m_pObject->GetFormattedObject();

    return "";
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNAutoNumbered::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    if (m_pObject)
        return m_pObject->ConvertFormattedObject(value, locateFormat, emptyWhenZero);

    // hasn't changed
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::DrawObject(CDC* pDC, PSS_View* pView)
{
    DrawFillObject(pDC, pView);
    m_TextLevel.DrawObject(pDC, pView);

    // must draw the object
    if (m_pObject)
        m_pObject->DrawObject(pDC, pView);

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SizePositionHasChanged()
{
    if (!m_pObject)
        return;

    // call the basic fonction
    PSS_PlanFinObject::SizePositionHasChanged();

    // recalculate all element positions.
    GetTextLevel().SetClientRect(m_ObjectRect);
    m_pObject->SetClientRect(m_ObjectRect);
    m_pObject->GetClientRect().left += GetTextOffset();

    // if automatic recalculation of section
    if (GetAutoCalculate())
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        if (pWnd)
            pWnd->SendMessageToDescendants(UM_REBUILDAUTOMATICNUMBER);
    }
}
//---------------------------------------------------------------------------
CString PSS_PLFNAutoNumbered::GetUnformattedObject()
{
    if (m_pObject)
        return m_pObject->GetUnformattedObject();

    return "";
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetStyle(PSS_Style::Handle hStyle)
{
    if (m_pObject)
        m_pObject->SetStyle(hStyle);
}
//---------------------------------------------------------------------------
const COLORREF PSS_PLFNAutoNumbered::GetFillColor() const
{
    if (m_pObject)
        return m_pObject->GetFillColor();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetFillColor(COLORREF value)
{
    if (m_pObject)
        m_pObject->SetFillColor(value);
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::Serialize(CArchive& ar)
{
    PSS_PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_TextOffset);
        ar << WORD(m_AutoCalculate);
        ar << WORD(m_SectionNumber);
        ar << WORD(m_Level);

        // serialize the defined object
        ar << m_pObject;
    }
    else
    {
        // read the elements
        WORD wValue;
        ar >> wValue;
        m_TextOffset = wValue;

        ar >> wValue;
        m_AutoCalculate = wValue;

        ar >> wValue;
        m_SectionNumber = wValue;

        ar >> wValue;
        m_Level = wValue;

        // serialize the defined object
        ar >> m_pObject;
    }

    // should serialize the static member, serialize the Text Level
    m_TextLevel.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAutoNumbered::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAutoNumbered::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
