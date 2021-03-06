/****************************************************************************
 * ==> PSS_ObjectUtility ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an object utility                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ObjectUtility.h"

// processsoft
#include "zBaseLib\PSS_SystemOption.h"
#include "PSS_File.h"
#include "PSS_PLFNRadioBtn.h"
#include "PSS_PLFNSquare.h"
#include "PSS_PLFNBoundText.h"
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_PLFNBitmap.h"
#include "PSS_PLFNCheckBtn.h"
#include "PSS_PLFNMaskString.h"
#include "PSS_PLFNMultiColumn.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const char g_SectionKey[] = _T("Keys");
const char g_TypeEntry[]  = _T("Entry");
const char g_LineEntry[]  = _T("Line");
//---------------------------------------------------------------------------
const UINT PSS_ObjectUtility::m_ClassResourceBitmapIDArrary[] =
{
    IDB_AMOUNT_BITMAP,
    IDB_AMOUNT_BITMAP,
    IDB_CALC_BITMAP,
    IDB_DATE_BITMAP,
    IDB_TEXT_BITMAP,
    IDB_TEXT_BITMAP,
    IDB_STEXT_BITMAP,
    IDB_MULTILINE_BITMAP,
    IDB_SMULTILINE_BITMAP,
    IDB_SECTION_BITMAP,
    IDB_SQUARE_BITMAP,
    IDB_LINE_BITMAP,
    IDB_RECT_BITMAP,
    IDB_RECTROUNDED_BITMAP,
    IDB_IMAGE_BITMAP,
    IDB_IMAGE_BITMAP,
    IDB_IMAGE_BITMAP,
    0
};
//---------------------------------------------------------------------------
const UINT PSS_ObjectUtility::m_EditionClassResourceIDArrary[] =
{
    IDS_AMOUNT_CLASS,
    IDS_HISTOAMOUNT_CLASS,
    IDS_CALCULATED_CLASS,
    IDS_DATE_CLASS,
    IDS_TEXT_CLASS,
    IDS_HISTOTEXT_CLASS,
    IDS_STATICTEXT_CLASS,
    IDS_MULTITEXT_CLASS,
    IDS_MULTITEXTSTATIC_CLASS,
    IDS_NUMBEREDSECTION_CLASS,
    IDS_SQUARETEXT_CLASS,
    IDS_CHECK_CLASS,
    IDS_RADIO_CLASS,
    IDS_MASKSTRING_CLASS,
    IDS_MASKSTRINGHISTO_CLASS,
    IDS_MULTICOLUMN_CLASS,
    0
};
//---------------------------------------------------------------------------
const UINT PSS_ObjectUtility::m_ClassResourceIDArrary[] =
{
    IDS_AMOUNT_CLASS,
    IDS_HISTOAMOUNT_CLASS,
    IDS_CALCULATED_CLASS,
    IDS_DATE_CLASS,
    IDS_TEXT_CLASS,
    IDS_HISTOTEXT_CLASS,
    IDS_STATICTEXT_CLASS,
    IDS_MULTITEXT_CLASS,
    IDS_MULTITEXTSTATIC_CLASS,
    IDS_NUMBEREDSECTION_CLASS,
    IDS_SQUARETEXT_CLASS,
    IDS_LINE_CLASS,
    IDS_RECTANGLE_CLASS,
    IDS_RECTANGLEROUNDED_CLASS,
    IDS_BITMAP_CLASS,
    IDS_CHECK_CLASS,
    IDS_RADIO_CLASS,
    IDS_MASKSTRING_CLASS,
    IDS_MASKSTRINGHISTO_CLASS,
    IDS_MULTICOLUMN_CLASS,
    0
};
//---------------------------------------------------------------------------
// PSS_ObjectUtility::IObjectDefinition
//---------------------------------------------------------------------------
PSS_ObjectUtility::IObjectDefinition::IObjectDefinition(const CString& key, const CString& description) :
    CObject(),
    m_Key(key),
    m_Description(description)
{}
//---------------------------------------------------------------------------
PSS_ObjectUtility::IObjectDefinition::~IObjectDefinition()
{}
//---------------------------------------------------------------------------
// PSS_ObjectUtility
//---------------------------------------------------------------------------
CStringArray PSS_ObjectUtility::m_ClassNameArray;
CStringArray PSS_ObjectUtility::m_EditionClassNameArray;
CObArray     PSS_ObjectUtility::m_FieldTypeDescriptionArray;
//---------------------------------------------------------------------------
PSS_ObjectUtility::PSS_ObjectUtility()
{}
//---------------------------------------------------------------------------
PSS_ObjectUtility::~PSS_ObjectUtility()
{
    Release();
}
//---------------------------------------------------------------------------
const PSS_ObjectUtility& PSS_ObjectUtility::operator = (const PSS_ObjectUtility& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
const CString PSS_ObjectUtility::GetFieldTypeDescription(PSS_PlanFinObject* pObj)
{
    switch (GetClassNameID(pObj))
    {
        case IDS_STATICTEXT_CLASS:       return GetFieldTypeDescriptionIniFile(_T("$$$PLFNStatic"));
        case IDS_DATE_CLASS:             return GetFieldTypeDescriptionIniFile(_T("$$$PLFNTime"));
        case IDS_CALCULATED_CLASS:       return GetFieldTypeDescriptionIniFile(_T("$$$PLFNCalculated"));
        case IDS_HISTOAMOUNT_CLASS:      return GetFieldTypeDescriptionIniFile(_T("$$$PLFNLongHistory"));
        case IDS_AMOUNT_CLASS:           return GetFieldTypeDescriptionIniFile(_T("$$$PLFNLong"));
        case IDS_MULTITEXTSTATIC_CLASS:  return GetFieldTypeDescriptionIniFile(_T("$$$PLFNBondTextStatic"));
        case IDS_MULTITEXT_CLASS:        return GetFieldTypeDescriptionIniFile(_T("$$$PLFNBondText"));
        case IDS_HISTOTEXT_CLASS:        return GetFieldTypeDescriptionIniFile(_T("$$$PLFNStringHistory"));
        case IDS_TEXT_CLASS:             return GetFieldTypeDescriptionIniFile(_T("$$$PLFNString"));
        case IDS_SQUARETEXT_CLASS:       return GetFieldTypeDescriptionIniFile(_T("$$$PLFNSquare"));
        case IDS_NUMBEREDSECTION_CLASS:  return GetFieldTypeDescriptionIniFile(_T("$$$PLFNAutoNumbered"));
        case IDS_LINE_CLASS:             return GetFieldTypeDescriptionIniFile(_T("$$$PLFNLine"));
        case IDS_RECTANGLEROUNDED_CLASS: return GetFieldTypeDescriptionIniFile(_T("$$$PLFNRectRounded"));
        case IDS_RECTANGLE_CLASS:        return GetFieldTypeDescriptionIniFile(_T("$$$PLFNRect"));
        case IDS_BITMAP_CLASS:           return GetFieldTypeDescriptionIniFile(_T("$$$PLFNBitmap"));
        case IDS_CHECK_CLASS:            return GetFieldTypeDescriptionIniFile(_T("$$$PLFNCheck"));
        case IDS_RADIO_CLASS:            return GetFieldTypeDescriptionIniFile(_T("$$$PLFNRadio"));
        case IDS_MASKSTRING_CLASS:       return GetFieldTypeDescriptionIniFile(_T("$$$PLFNMaskString"));
        case IDS_MASKSTRINGHISTO_CLASS:  return GetFieldTypeDescriptionIniFile(_T("$$$PLFNMaskStringHisto"));
        case IDS_MULTICOLUMN_CLASS:      return GetFieldTypeDescriptionIniFile(_T("$$$PLFNMultiColumn"));
    }

    return _T("");
}
//---------------------------------------------------------------------------
const CString PSS_ObjectUtility::GetFieldTypeDescription(const CString& className)
{
    PSS_PlanFinObject* pTempObj = BuildObject(className);
    CString            fieldExplanation;

    if (pTempObj)
    {
        fieldExplanation = GetFieldTypeDescription(pTempObj);
        delete pTempObj;
    }

    return fieldExplanation;
}
//---------------------------------------------------------------------------
const CString PSS_ObjectUtility::GetClassName(PSS_PlanFinObject* pObj)
{
    CString text;
    text.LoadString(GetClassNameID(pObj));

    return text;
}
//---------------------------------------------------------------------------
UINT PSS_ObjectUtility::GetBitmapClass(const CString& className)
{
    // fill the list with all objects' type
    const CStringArray& stringArray = GetClassNameArray();
    const int           arrayCount  = stringArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
        if (className == stringArray.GetAt(i))
            return m_ClassResourceBitmapIDArrary[i];

    return 0;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_ObjectUtility::BuildObject(const CString& className)
{
    // fill the list with all objects' type
    const CStringArray& stringArray = GetClassNameArray();
    const INT_PTR       arrayCount  = stringArray.GetSize();
          INT_PTR       index       = 0;

    for (INT_PTR i = 0; i < arrayCount; ++i)
        if (className == stringArray.GetAt(i))
        {
            index = i;
            break;
        }

    std::unique_ptr<PSS_PlanFinObject> pObj;

    switch (index)
    {
        case 0:
            pObj.reset(new PSS_PLFNLong());
            break;

        case 1:
            pObj.reset(new PSS_PLFNLong());
            static_cast<PSS_PLFNLong*>(pObj.get())->SetKeepHistory(TRUE);
            break;

        case 2:
            pObj.reset(new PSS_PLFNLong());
            static_cast<PSS_PLFNLong*>(pObj.get())->SetCalculatedField();
            break;

        case 3:
            pObj.reset(new PSS_PLFNTime());
            break;

        case 4:
            pObj.reset(new PSS_PLFNString());
            break;

        case 5:
            pObj.reset(new PSS_PLFNString);
            static_cast<PSS_PLFNString*>(pObj.get())->SetKeepHistory(TRUE);
            break;

        case 6:
            pObj.reset(new PSS_PLFNStatic());
            break;

        case 7:
            pObj.reset(new PSS_PLFNBoundText());
            break;

        case 8:
            // TRUE is for static bound text
            pObj.reset(new PSS_PLFNBoundText(TRUE));
            break;

        case 9:
            pObj.reset(new PSS_PLFNAutoNumbered());
            break;

        case 10:
            pObj.reset(new PSS_PLFNSquare());
            break;

        case 11:
            pObj.reset(new PSS_PLFNLine());
            break;

        case 12:
            pObj.reset(new PSS_PLFNRect());
            break;

        case 13:
            pObj.reset(new PSS_PLFNRect(TRUE));
            break;

        case 14:
            pObj.reset(new PSS_PLFNBitmap());
            break;

        case 15:
            pObj.reset(new PSS_PLFNCheckBtn());
            break;

        case 16:
            pObj.reset(new PSS_PLFNRadioBtn());
            break;

        case 17:
            pObj.reset(new PSS_PLFNMaskString());
            break;

        case 18:
            pObj.reset(new PSS_PLFNMaskString());
            static_cast<PSS_PLFNMaskString*>(pObj.get())->SetKeepHistory(TRUE);
            break;

        case 19:
            pObj.reset(new PSS_PLFNMultiColumn());
            break;

        default:
            return NULL;
    }

    return pObj.release();
}
//---------------------------------------------------------------------------
BOOL PSS_ObjectUtility::InitializeDefinition(const CString& iniFileName)
{
    PSS_SystemOption systemOption;

    Release();

    // check if the file exists
    PSS_File file(iniFileName);

    if (!file.Exist())
        return FALSE;

    // Create the ini reader
    if (!systemOption.Create(iniFileName, g_SectionKey))
        return FALSE;

    char    buffer[100];
    CString fieldKey;
    CString description;

    for (int i = 0; TRUE; ++i)
    {
        // build the key
        std::sprintf(buffer, _T("%s%d"), g_TypeEntry, i);
        fieldKey = systemOption.ReadOption(buffer, _T(""));

        // if no more entry
        if (fieldKey.IsEmpty())
            break;

        description = LoadFieldDefinition(iniFileName, fieldKey);

        std::unique_ptr<IObjectDefinition> pDef(new IObjectDefinition(fieldKey, description));
        m_FieldTypeDescriptionArray.Add(pDef.get());
        pDef.release();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_ObjectUtility::LoadFieldDefinition(const CString& iniFileName, const CString& fieldKey)
{
    PSS_SystemOption m_SystemOptionField(iniFileName, fieldKey);
    char             buffer[100];
    CString          description;

    for (int i = 0; ; ++i)
    {
        // build the key
        std::sprintf(buffer, _T("%s%d"), g_LineEntry, i);

        const CString line = m_SystemOptionField.ReadOption(buffer, _T(""));

        // no more entry?
        if (line.IsEmpty())
            break;

        description += line;
    }

    return description;
}
//---------------------------------------------------------------------------
std::size_t PSS_ObjectUtility::GetClassNameID(PSS_PlanFinObject* pObj)
{
    std::size_t resourceID = IDS_UNMODIFIED_CLASS;

    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNStatic)))
        resourceID = IDS_STATICTEXT_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTime)))
        resourceID = IDS_DATE_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLong)))
    {
        if (((PSS_PLFNLong*)pObj)->IsCalculatedField())
            resourceID = IDS_CALCULATED_CLASS;
        else
        if (((PSS_PLFNLong*)pObj)->GetKeepHistory())
            resourceID = IDS_HISTOAMOUNT_CLASS;
        else
            resourceID = IDS_AMOUNT_CLASS;
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBoundText)))
    {
        if (((PSS_PLFNBoundText*)pObj)->GetIsStatic())
            resourceID = IDS_MULTITEXTSTATIC_CLASS;
        else
            resourceID = IDS_MULTITEXT_CLASS;
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNMaskString)))
    {
        if (((PSS_PLFNString*)pObj)->GetKeepHistory())
            resourceID = IDS_MASKSTRINGHISTO_CLASS;
        else
            resourceID = IDS_MASKSTRING_CLASS;
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNString)))
    {
        if (((PSS_PLFNString*)pObj)->GetKeepHistory())
            resourceID = IDS_HISTOTEXT_CLASS;
        else
            resourceID = IDS_TEXT_CLASS;
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNSquare)))
        resourceID = IDS_SQUARETEXT_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)))
        resourceID = IDS_NUMBEREDSECTION_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLine)))
        resourceID = IDS_LINE_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNRect)))
    {
        if (((PSS_PLFNRect*)pObj)->IsRounded())
            resourceID = IDS_RECTANGLEROUNDED_CLASS;
        else
            resourceID = IDS_RECTANGLE_CLASS;
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBitmap)))
        resourceID = IDS_BITMAP_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNCheckBtn)))
        resourceID = IDS_CHECK_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNRadioBtn)))
        resourceID = IDS_RADIO_CLASS;
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNMultiColumn)))
        resourceID = IDS_MULTICOLUMN_CLASS;

    return resourceID;
}
//---------------------------------------------------------------------------
void PSS_ObjectUtility::Release()
{
    const int descCount = m_FieldTypeDescriptionArray.GetSize();

    for (int i = 0; i < descCount; ++i)
        if (m_FieldTypeDescriptionArray.GetAt(i))
            delete m_FieldTypeDescriptionArray.GetAt(i);

    m_FieldTypeDescriptionArray.RemoveAll();
}
//---------------------------------------------------------------------------
const CString PSS_ObjectUtility::GetFieldTypeDescriptionIniFile(const char* pKey)
{
    const int descCount = m_FieldTypeDescriptionArray.GetSize();

    for (int i = 0; i < descCount; ++i)
    {
        IObjectDefinition* pObjDef = dynamic_cast<IObjectDefinition*>(m_FieldTypeDescriptionArray.GetAt(i));

        if (pObjDef && pObjDef->m_Key == pKey)
            return pObjDef->m_Description;
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ObjectUtility::LoadResource()
{
    // assign the edition class name
    if (m_EditionClassNameArray.GetSize() <= 0)
    {
        CString label;

        for (register int i = 0; m_EditionClassResourceIDArrary[i]; ++i)
        {
            label.LoadString(m_EditionClassResourceIDArrary[i]);
            m_EditionClassNameArray.Add(label);
        }
    }

    // assign the class name
    if (m_ClassNameArray.GetSize() <= 0)
    {
        CString label;

        for (register int i = 0; m_ClassResourceIDArrary[i]; ++i)
        {
            label.LoadString(m_ClassResourceIDArrary[i]);
            m_ClassNameArray.Add(label);
        }
    }
}
//---------------------------------------------------------------------------
