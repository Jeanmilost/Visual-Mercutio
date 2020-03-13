#if !defined(_ZCInPlaceDurationEdit_H__)
#define _ZCInPlaceDurationEdit_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCInPlaceDurationEdit_H.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zProperty\PSS_InPlaceEdit.h"
#include "zWinUtil32\PSS_SearchEdit.h"


#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceDurationEdit

class AFX_EXT_CLASS ZCInPlaceDurationEdit : public PSS_SearchEdit, public PSS_InPlaceEdit
{
    ZCInPlaceDurationEdit(const ZCInPlaceDurationEdit& d);
    ZCInPlaceDurationEdit operator=(const ZCInPlaceDurationEdit& d);

protected:
    DECLARE_DYNAMIC(ZCInPlaceDurationEdit)

public:
    ZCInPlaceDurationEdit(bool IsReadOnly = false);
    ZCInPlaceDurationEdit(PSS_Duration& DurationInitValue, bool IsReadOnly = false);
    virtual ~ZCInPlaceDurationEdit();

    // Operations
public:
    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, PSS_Duration& DurationInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText);
    virtual void SetEditText(PSS_Duration& DurationValue);
    // Retrieve the text entered
    virtual CString GetEditText() const;

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Call when requires to process the extended command
    virtual void OnExtendedCommand();

    bool IsEditCtrlHit(CPoint point) const;
    bool IsEditButtonCtrlHit(CPoint point) const;

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

private:
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceDurationEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceDurationEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Data
private:
};

inline ZCInPlaceDurationEdit::ZCInPlaceDurationEdit(bool IsReadOnly /*= false*/)
    : PSS_InPlaceEdit((double)0, IsReadOnly)
{}

inline ZCInPlaceDurationEdit::ZCInPlaceDurationEdit(PSS_Duration& DurationInitValue, bool IsReadOnly /*= false*/)
    : PSS_InPlaceEdit(DurationInitValue, IsReadOnly)
{}

inline ZCInPlaceDurationEdit::~ZCInPlaceDurationEdit()
{}

#endif
