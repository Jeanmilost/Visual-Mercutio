/****************************************************************************************************************
 *                                            classe ZVDynamicAttributesDuplication                                *
 ****************************************************************************************************************
 * JMR-MODIF - Le 18 ao�t 2005 - Ajout de la classe ZVDynamicAttributesDuplication.                                *
 * Cette classe repr�sente la bo�te de dialogue permettant de param�trer la copie d'attributs dynamiques. Elle    *
 * s'occupe de la validit� des donn�es, et mets ces derni�res � disposition pour l'op�ration de copie.            *
 ****************************************************************************************************************/

#include "stdafx.h"
#include "ZVDynamicAttributesDuplication.h"
#include ".\zvdynamicattributesduplication.h"

 // **************************************************************************************************************
 // *                                                  Impl�mentation                                            *
 // **************************************************************************************************************

IMPLEMENT_DYNAMIC(ZVDynamicAttributesDuplication, ZIWizardDialog)

// Gestionnaires de messages ZVDynamicAttributesDuplication
BEGIN_MESSAGE_MAP(ZVDynamicAttributesDuplication, ZIWizardDialog)
    ON_LBN_SELCHANGE(IDC_ATTRIB_CATEGORY_LIST, OnLbnSelchangeAttribCategoryList)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// **************************************************************************************************************
// *                                            Construction / Destruction                                        *
// **************************************************************************************************************

// Constructeur par d�faut de la classe ZVDynamicAttributesDuplication.
ZVDynamicAttributesDuplication::ZVDynamicAttributesDuplication(ZDProcessGraphModelDoc*    pModelDoc,
                                                               bool                    SymbolSelected)
    : ZIWizardDialog(ZVDynamicAttributesDuplication::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS3_ST_T,
                     IDS_WZ_DYNATTRS3_ST_S),
    m_pModelDoc(pModelDoc),
    m_InternalNameChange(false),
    m_Name(_T("")),
    m_Category(_T("")),
    m_bDupValuesIsChecked(TRUE)
{}

// Destructeur de la classe ZVDynamicAttributesDuplication.
ZVDynamicAttributesDuplication::~ZVDynamicAttributesDuplication()
{}

// **************************************************************************************************************
// *                               Fonctions de la classe ZVDynamicAttributesDuplication                        *
// **************************************************************************************************************

void ZVDynamicAttributesDuplication::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ATTRIB_CATEGORY_LIST, m_CategoryList);
    DDX_Text(pDX, IDC_ATTRIB_NAME, m_Name);
    DDX_Text(pDX, IDC_ATTRIB_CATEGORY_NAME, m_Category);
    DDX_Check(pDX, IDC_DUPLICATE_VALUES, m_bDupValuesIsChecked);
    DDX_Control(pDX, IDC_ATTRIB_NAME, m_AttribNameTxtBox);
    DDX_Control(pDX, IDC_DUPLICATE_VALUES, m_cbDuplicateValues);
}

// Cette fonction est appel�e lorsque la classe s'initialise.
BOOL ZVDynamicAttributesDuplication::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    if (m_pModelDoc &&
        m_pModelDoc->GetModel() &&
        m_pModelDoc->GetDynamicPropertiesManager())
    {
        ZUDynamicAttributesManipulator::GetCategories(m_pModelDoc->GetModel(),
                                                      m_StaticAttribArray,
                                                      m_DynamicAttribArray);

        // Remplit la liste avec les propri�t�s dynamiques.
        for (int i = 0; i < m_DynamicAttribArray.GetSize(); ++i)
            m_CategoryList.AddString(m_DynamicAttribArray.GetAt(i));
    }

    return TRUE;
}

// Cette fonction est appel�e lorsque l'utilisateur choisit une entr�e dans la liste des cat�gories.
void ZVDynamicAttributesDuplication::OnLbnSelchangeAttribCategoryList()
{
    // Ces deux lignes sont n�cessaire pour conserver l'�tat des valeurs. Bug de MFC ?
    m_AttribNameTxtBox.GetWindowText(m_Name);
    m_bDupValuesIsChecked = m_cbDuplicateValues.GetCheck();

    int CurSel = m_CategoryList.GetCurSel();

    if (CurSel != LB_ERR)
    {
        m_InternalNameChange = true;

        m_CategoryList.GetText(CurSel, m_Category);
        UpdateData(FALSE);

        m_InternalNameChange = false;
    }
}

// Cette fonction est appel�e lorsque l'utilisateur clique sur le bouton Ok.
void ZVDynamicAttributesDuplication::OnBnClickedOk()
{
    UpdateData(TRUE);

    // Teste si les deux champs n�cessaires � la copie ont �t� remplis.
    if (m_Category.IsEmpty() || m_Name.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_COPYNAMEORCATEGORY_IS_MISSING, MB_OK);
        return;
    }

    // Teste ensuite si le nom d�sir� n'est pas d�j� attribu� � un attribut statique.
    for (int i = 0; i < m_StaticAttribArray.GetSize(); ++i)
    {
        if (m_StaticAttribArray.GetAt(i) == m_Name)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return;
        }
    }

    // Teste enfin si le nom d�sir� n'est pas d�j� attribu� � un autre attribut dynamique.
    for (int i = 0; i < m_DynamicAttribArray.GetSize(); ++i)
    {
        if (m_DynamicAttribArray.GetAt(i) == m_Name)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return;
        }
    }

    ZIWizardDialog::OnOK();
}
