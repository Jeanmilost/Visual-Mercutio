#if !defined(_ZVInputAttributes_H__)
#define _ZVInputAttributes_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInputAttributes.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "PSS_InputAttributesList.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarInputAttributes window

class _ZVFlatToolBarInputAttributes : public CStatic, public PSS_Subject
{
    // Construction
public:
    _ZVFlatToolBarInputAttributes();

    // Attributes
private:
    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_AddInputAttributeButton;
    CCJFlatButton    m_DeleteInputAttributeButton;
    CCJFlatButton    m_ModifyInputAttributeButton;
    CCJFlatButton    m_ShowSymbolAttributeButton;
    CCJFlatButton    m_ShowAllAttributeButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    // Operations
public:

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(_ZVFlatToolBarInputAttributes)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~_ZVFlatToolBarInputAttributes();

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZVFlatToolBarInputAttributes)
    afx_msg void OnRefreshButton();
    afx_msg void OnAddInputAttributeButton();
    afx_msg void OnDeleteInputAttributeButton();
    afx_msg void OnModifyInputAttributeButton();
    afx_msg void OnShowSymbolAttributeButton();
    afx_msg void OnShowAllAttributeButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributes view

class AFX_EXT_CLASS ZVInputAttributes : public CWnd,
                                        public PSS_Subject,
                                        public PSS_Observer
{

public:
    DECLARE_DYNCREATE(ZVInputAttributes)
    ZVInputAttributes();           // protected constructor used by dynamic creation
    virtual ~ZVInputAttributes();

    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Operations
    void Initialize(PSS_InputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager)
    {
        m_listctrl.Initialize(pInputManager, pPropManager);
    };
    void ShowAll(bool value = true, bool bRefresh = true)
    {
        CWaitCursor    Cursor;
        if (::IsWindow(m_listctrl.GetSafeHwnd()))
            m_listctrl.ShowAll(value, bRefresh);
    };
    void SetSymbolRef(int value, bool bRefresh = true)
    {
        if (::IsWindow(m_listctrl.GetSafeHwnd()))
            m_listctrl.SetSymbolRef(value, bRefresh);
    };

    void Refresh();
    void Empty();

    PSS_InputAttribute* GetSelectedInputAttribute()
    {
        return m_listctrl.GetSelectedInputAttribute();
    };

    // Generated message map functions
protected:
    //{{AFX_MSG(ZVInputAttributes)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void OnAddInputAttribute();
    void OnDeleteInputAttribute();
    void OnModifyInputAttribute();
    void OnRefresh();



private:
    _ZVFlatToolBarInputAttributes m_FlatToolBar;
    PSS_InputAttributesList       m_listctrl;
    PSS_ProcessGraphModelDoc*     m_pCurrentDoc;
    int                           m_SymbolRef;
};

#endif
