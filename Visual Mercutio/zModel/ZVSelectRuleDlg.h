// **************************************************************************************************************
// *                                       Classe ZVSelectRuleDlg                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZVSelectRuleDlg.                                        *
// **************************************************************************************************************
// * Cette classe repr�sente l'interface de s�lection d'une r�gle, ou d'un groupe de r�gles, dans la liste.        *
// **************************************************************************************************************

#if !defined(AFX_ZVSELECTRULEDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)
#define AFX_ZVSELECTRULEDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZCRulesTreeCtrl.h"
#include "zModelRes.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// Forward class declaration
class ZBRulesEntity;
class ZBLogicalRulesEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectRuleDlg dialog

class AFX_EXT_CLASS ZVSelectRuleDlg : public CDialog
{
// Construction
public:

    // Standard constructor
    ZVSelectRuleDlg( const CString                    Title                = _T( "" ),
                           ZBLogicalRulesEntity*    pMainRule            = NULL,
                           bool                        AllowRuleSelection    = true,
                           CWnd*                    pParent                = NULL );

    // Standard constructor
    ZVSelectRuleDlg( UINT                    nTitle,
                     ZBLogicalRulesEntity*    pMainRule,
                     bool                    AllowRuleSelection    = true,
                     CWnd*                    pParent                = NULL );

    ~ZVSelectRuleDlg();

    void Release();

    ZBRulesEntity* GetSelectedRuleEntity() const
    {
        return m_pRuleEntity;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVSelectRuleDlg)
    enum { IDD = IDD_RULE_SELECTION };
    ZCRulesTreeCtrl m_Ctrl;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVSelectRuleDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVSelectRuleDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedRulesTree(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CString                    m_Title;
    ZBRulesEntity*            m_pRuleEntity;
    ZBLogicalRulesEntity*    m_pMainRule;
    bool                    m_AllowRuleSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVSELECTRULEDLG_H__16B257AC_C5CD_4411_8750_F4510E61718B__INCLUDED_)