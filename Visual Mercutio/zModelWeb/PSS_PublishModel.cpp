/****************************************************************************
 * ==> PSS_PublishModel ----------------------------------------------------*
 ****************************************************************************
 * Description : Publishes a model                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PublishModel.h"

// processsoft
#include "ZVPublishModelWelcome.h"
#include "ZVPublishModelSelDir.h"
#include "PSS_PublishModelBannerDialog.h"
#include "PSS_PublishModelAttributesDialog.h"
#include "ZVPublishModelOptions.h"

#include "zBaseLib\ZUSystemOption.h"

// RS-MODIF 12.12.04 we need token to save attributes
#include "zBaseLib\ZBTokenizer.h"
#include "zProperty\zBPropertyAttributes.h"

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------
const CString g_PublishModelHTMLSectionName                  = _T("PublishModelToHTML");
const CString g_PublishModelHTMLAddressEntityName            = _T("PublishAddress");
const CString g_PublishModelHTMLLastLanguageEntityName       = _T("LastPublishLanguage");
const CString g_PublishModelHTMLPublishConceptor             = _T("PublishConceptor");
const CString g_PublishModelHTMLPublishConceptorDetails      = _T("PublishConceptorDetails");
const CString g_PublishModelHTMLPublishConceptorDeliverables = _T("PublishConceptorDeliverables");
const CString g_PublishModelHTMLPublishProcess               = _T("PublishProcess");
const CString g_PublishModelHTMLPublishRuleBook              = _T("PublishRuleBook");
const CString g_PublishModelHTMLVisualizeEntityName          = _T("Visualize");
const CString g_PublishModelHTMLLogoFilenameEntityName       = _T("LogoFilename");
const CString g_PublishModelHTMLLogoRefHTMLEntityName        = _T("LogoRef");
//---------------------------------------------------------------------------
// PSS_PublishModel
//---------------------------------------------------------------------------
PSS_PublishModel::PSS_PublishModel(ZBPropertyAttributes* pAttributes,
                                   ZBPropertySet*        pSet,
                                   const CString&        iniFile) :
    m_IniFile(iniFile),
    m_pPropAttributes(pAttributes),
    m_pPropSet(pSet)
{}
//---------------------------------------------------------------------------
PSS_PublishModel::PSS_PublishModel(const PSS_PublishModel& other)
{
    THROW("Calling PSS_PublishModel copy constructor is prohibited");
}
//---------------------------------------------------------------------------
const PSS_PublishModel& PSS_PublishModel::operator = (const PSS_PublishModel& other)
{
    THROW("Calling PSS_PublishModel copy operator is prohibited");
}
//---------------------------------------------------------------------------
PSS_PublishModel::~PSS_PublishModel()
{}
//---------------------------------------------------------------------------
BOOL PSS_PublishModel::SelectDir()
{
    ZVPublishModelWelcome welcome;

    if (welcome.DoModal() == IDCANCEL)
        return FALSE;

    // load the last state
    LoadStateFromIniFile();

    // load attributes
    LoadAttributesFromIniFile();

    ZVPublishModelSelectDirectory select(m_Directory, &m_ArrayOfAddress);

    if (select.DoModal() == IDCANCEL)
        return FALSE;

    // no directory selected
    if (select.GetDirectory().IsEmpty())
        return FALSE;

    m_Directory = select.GetDirectory();

    PSS_PublishModelBannerDialog banner(m_HyperLink, m_ImageFilename);

    if (banner.DoModal() == IDCANCEL)
        return FALSE;

    m_ImageFilename = banner.GetImageFilename();
    m_HyperLink = banner.GetHyperLink();

    CWaitCursor                      cursor;
    PSS_PublishModelAttributesDialog attributes(m_pPropAttributes, m_pPropSet);

    if (attributes.DoModal() == IDCANCEL)
        return FALSE;

    ZVPublishModelOptions options(m_VisualizeResult,
        m_PublishConceptor,
        m_PublishConceptorDetails,
        m_PublishConceptorDeliverables,
        m_PublishProcess,
        m_PublishRuleBook,
        m_Language);

    if (options.DoModal() == IDCANCEL)
        return FALSE;

    m_VisualizeResult = options.GetVisualize() ? true : false;
    m_PublishConceptor = options.GetPublishConceptor() ? true : false;
    m_PublishConceptorDetails = options.GetPublishConceptorDetails() ? true : false;
    m_PublishConceptorDeliverables = options.GetPublishConceptorDeliverables() ? true : false;
    m_PublishProcess = options.GetPublishProcess() ? true : false;
    m_PublishRuleBook = options.GetPublishRuleBook() ? true : false;
    m_Language = options.GetLanguage();

    // save the state
    SaveStateToIniFile();

    // also save attributes
    SaveAttributesToIniFile();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModel::AddAttribute(_ZBPropertyAttribute* pAttribute)
{
    if (!pAttribute)
        return;

    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    if (!FindAttribute(pAttribute->GetCategoryID(), pAttribute->GetItemID()))
        pPropTemp->GetAttributeSet().Add(pAttribute);
    else
        // otherwise delete the attribute
        delete pAttribute;
}
//---------------------------------------------------------------------------
_ZBPropertyAttribute* PSS_PublishModel::FindAttribute(int CategoryID, int ItemID)
{
    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    _ZBPropertyAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (_ZBPropertyAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        if (pAtt->GetCategoryID() == CategoryID && pAtt->GetItemID() == ItemID)
            return pAtt;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PublishModel::RemoveAllAttributes()
{
    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    _ZBPropertyAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (_ZBPropertyAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        delete pAtt;

    pPropTemp->GetAttributeSet().RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::LoadStateFromIniFile()
{
    ZUSystemOption systemOption(m_IniFile, g_PublishModelHTMLSectionName);

    // read the options
    m_PublishConceptor = systemOption.ReadOption(g_PublishModelHTMLPublishConceptor, true);
    m_PublishConceptorDetails = systemOption.ReadOption(g_PublishModelHTMLPublishConceptorDetails, true);
    m_PublishConceptorDeliverables = systemOption.ReadOption(g_PublishModelHTMLPublishConceptorDeliverables, true);
    m_PublishProcess = systemOption.ReadOption(g_PublishModelHTMLPublishProcess, true);
    m_PublishRuleBook = systemOption.ReadOption(g_PublishModelHTMLPublishRuleBook, true);
    m_VisualizeResult = systemOption.ReadOption(g_PublishModelHTMLVisualizeEntityName, true);
    m_Language = static_cast<Language>(systemOption.ReadOption(g_PublishModelHTMLLastLanguageEntityName, 0));
    m_Directory = systemOption.ReadOption(g_PublishModelHTMLAddressEntityName, _T(""));
    m_ImageFilename = systemOption.ReadOption(g_PublishModelHTMLLogoFilenameEntityName, _T(""));
    m_HyperLink = systemOption.ReadOption(g_PublishModelHTMLLogoRefHTMLEntityName, _T(""));

    CString     keyName;
    CString     addr;
    std::size_t index = 0;

    // remove all elements
    m_ArrayOfAddress.RemoveAll();

    // set the maximum loop at thousand objects, which is big enough
    const std::size_t max = 1000;

    do
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishModelHTMLAddressEntityName, index);
        addr = systemOption.ReadOption(keyName, _T(""));

        if (addr.IsEmpty())
            break;

        // add element to the table
        m_ArrayOfAddress.Add(addr);

        ++index;
    }
    while (index < max);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::SaveStateToIniFile()
{
    ZUSystemOption systemOption(m_IniFile, g_PublishModelHTMLSectionName);

    // save the options
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptor, m_PublishConceptor);
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptorDetails, m_PublishConceptorDetails);
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptorDeliverables, m_PublishConceptorDeliverables);
    systemOption.WriteOption(g_PublishModelHTMLPublishProcess, m_PublishProcess);
    systemOption.WriteOption(g_PublishModelHTMLPublishRuleBook, m_PublishRuleBook);
    systemOption.WriteOption(g_PublishModelHTMLVisualizeEntityName, m_VisualizeResult);
    systemOption.WriteOption(g_PublishModelHTMLLastLanguageEntityName, m_Language);
    systemOption.WriteOption(g_PublishModelHTMLAddressEntityName, m_Directory);
    systemOption.WriteOption(g_PublishModelHTMLLogoFilenameEntityName, m_ImageFilename);
    systemOption.WriteOption(g_PublishModelHTMLLogoRefHTMLEntityName, m_HyperLink);

    CString keyName;

    // add the address to the array
    bool found = false;

    for (int i = 0; i < m_ArrayOfAddress.GetSize(); ++i)
        if (m_ArrayOfAddress.GetAt(i) == m_Directory)
            found = true;

    if (!found)
        m_ArrayOfAddress.Add(m_Directory);

    for (int i = 0; i < m_ArrayOfAddress.GetSize(); ++i)
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishModelHTMLAddressEntityName, i);

        // write the string to the ini file
        systemOption.WriteOption(keyName, m_ArrayOfAddress.GetAt(i));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::LoadAttributesFromIniFile()
{
    // delete all attributes
    RemoveAllAttributes();

    ZUSystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    // set the maximum loop at 1 million objects, which is big enough
    const std::size_t max = 100000;

    do
    {
        // Format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        CString     str;
        ZBTokenizer token;

        // extract the category ID
        str = token.GetFirstToken(line);

        if (str.IsEmpty())
            continue;

        const int categoryID = std::atoi((const char*)str);

        // extract the item ID
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int itemID = std::atoi((const char*)str);

        // all objects have been extracted, create the object state
        _ZBPropertyAttribute* pAtt = new _ZBPropertyAttribute(categoryID, itemID);

        // add it to the value array
        AddAttribute(pAtt);
    }
    while (index < max);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::SaveAttributesToIniFile()
{
    ZUSystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    // need to delete all records before saving
    DeleteAttributesFromIniFile();

    std::size_t index = 0;
    CString     keyName;

    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    _ZBPropertyAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (_ZBPropertyAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext(), ++index)
    {
        // format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);
        ZBTokenizer token;

        // build the string
        token.AddToken(pAtt->GetCategoryID());
        token.AddToken(pAtt->GetItemID());

        // write the string to the ini file
        systemOption.WriteOption(keyName, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::DeleteAttributesFromIniFile()
{
    ZUSystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    // set the maximum loop at 1 million objects, which is big enough
    const std::size_t max = 1000000;

    do
    {
        // format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        // easier to set the value to null than to delete the line
        systemOption.WriteOption(keyName, _T("0;0"));
    } while (index < max);

    return true;
}
//---------------------------------------------------------------------------
