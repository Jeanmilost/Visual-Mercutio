// ZCInPlaceDateEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZCInPlaceDateEdit.h"
#include "ZCPropertyListCtrl.h"

#include "zProperty\ZBPropertyItem.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "zBaseLib\ZBKeyboardObserverMsg.h"
#include "zBaseLib\ZBMenuObserverMsg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceDateEdit

IMPLEMENT_DYNAMIC(ZCInPlaceDateEdit, CEdit)




BEGIN_MESSAGE_MAP(ZCInPlaceDateEdit, ZCSearchEdit)
    //{{AFX_MSG_MAP(ZCInPlaceDateEdit)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL ZCInPlaceDateEdit::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)
    {
         CWnd* pOwner = GetOwner();
        WPARAM nChar = pMsg->wParam;

        switch(nChar)
        {
            case VK_DELETE:
            {
                SetHasChanged(true);
                break;
            }
            case VK_ESCAPE:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                // First, cancel the edit
                CancelEdit();
                // Notify observers
                if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
                {
                    GetParent()->PostMessage( WM_KEYPRESSED_EDIT, pMsg->wParam );
                    return TRUE;
                }

//                ZBKeyboardObserverMsg Msg( WM_KEYPRESSED_EDIT, pMsg->wParam ); 
//                NotifyAllObservers( &Msg );
//                return TRUE;
            }
            case VK_RETURN:
            case VK_TAB:
            {
                ::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
                // First, save the value
//                SaveValue();
                // Notify observers
                if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
                {
                    GetParent()->PostMessage( WM_KEYPRESSED_EDIT, (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT|pMsg->wParam) : pMsg->wParam );
                    return TRUE;
                }
                // Notify observers
//                ZBKeyboardObserverMsg Msg( WM_KEYPRESSED_EDIT, (GetKeyState(VK_SHIFT) & 0x80000000) ? (VK_SHIFT|pMsg->wParam) : pMsg->wParam ); 
//                NotifyAllObservers( &Msg );
//                return TRUE;
            }
            default:
                ;
        }
    }
    
    return ZCSearchEdit::PreTranslateMessage(pMsg);
}

void ZCInPlaceDateEdit::SetEditText(const CString& strText)
{
    m_strText = strText;

    if (::IsWindow(GetSafeHwnd()))
        SetWindowText(strText);
}

void ZCInPlaceDateEdit::SetEditText(ZBDate& DateValue)
{
    // Sets the duration value
    m_DateValue = DateValue;
    // Build the string
    CString strInitText;
    // Format the value function of the string format specified
    strInitText = ZUStringFormatter::GetFormattedBuffer( (ZBDate&)m_DateValue, m_pItem->GetStringFormat() );
    SetEditText( strInitText );
}

CString ZCInPlaceDateEdit::GetEditText() const
{
    CString strText;
    if (::IsWindow(GetSafeHwnd()))
        GetWindowText(strText);
    return strText;
}


BOOL ZCInPlaceDateEdit::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0"*/)
{    
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_LEFT|exDwStyle, rect, pWndParent, 1);
    SetEditText( strInitText );    
    // Saves the initial value
    m_strInitialValueText = strInitText;
    // Reset the has changed value
    SetHasChanged( false );
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_STRING;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}

BOOL ZCInPlaceDateEdit::InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, ZBDate& DateInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle /*= 0"*/)
{
    m_pItem = pItem;

    BOOL rValue = Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_LEFT|exDwStyle, rect, pWndParent, 1);
    SetEditText( (ZBDate&)DateInitValue );    
    // Saves the initial value
    m_InitialDateValue = DateInitValue;
    // Reset the has changed value
    SetHasChanged( false );
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DATE;
    // Sets the current selection to all
    SetSelAll();
    return rValue;
}

bool ZCInPlaceDateEdit::IsEditCtrlHit( CPoint point ) const
{
    CRect rect;
    GetClientRect(rect);

    ClientToScreen(&rect);

    return (rect.PtInRect(point)) ? true : false;
}



void ZCInPlaceDateEdit::SaveValue()
{
    if (GetHasChanged())
    {
        if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
        {
            CString ProposedValue = GetEditText();
            // If correct, process the data
            if (m_pItem) 
            {
                bool ConversionCorrect = true;
                switch (GetEditType())
                {
                    case ZIInPlaceEdit::IPE_STRING:
                    {
                        // do nothing for string
                        break;
                    }
                    case ZIInPlaceEdit::IPE_DATE:
                    {
                        // Check the conversion
                        // RS-MODIF 05.08.05 �dition de date
                        //ZBDuration value;

                        ZBDate value;

                        ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer( ProposedValue, (ZBDate&)value, m_pItem->GetStringFormat() );
                        if (!ConversionCorrect)
                            ZCInPlaceDateEdit::CancelEdit();
                        break;
                    }
                }
                // Now, if conversion correct and check value, save the edit value
                if (ConversionCorrect &&
                    dynamic_cast<ZCPropertyListCtrl*>(GetParent())->CheckCurrentPropertyData(m_pItem, ProposedValue))
                {
                    // Set the has changed flag for the property item
                    m_pItem->SetHasChanged();
                    // Notify observers for value changed
                    ZBToolbarObserverMsg Msg( WM_VALUESAVED_EDIT );
                    NotifyAllObservers( &Msg );
                    // Reset the change flag
                    m_HasChanged = false;
                    // OK
                    return;
                }
            }
            // Otherwise, not correct
            // Change the window text to the proposed value
            SetEditText(ProposedValue);
        }
    }
    // Set the focus to properties control
    SetFocus();
}


void ZCInPlaceDateEdit::CancelEdit()
{
    switch (GetEditType())
    {
        case ZIInPlaceEdit::IPE_STRING:
        {
            // Set back the initial value
            SetEditText( m_strInitialValueText );
            break;
        }
        case ZIInPlaceEdit::IPE_DATE:
        {
            // Set back the initial duration value
            SetEditText( (ZBDate&)m_InitialDateValue );
            break;
        }
    }
    // Set the focus to properties control
    SetFocus();
    // Reset the has changed value
    SetHasChanged( false );
}



/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceDateEdit message handlers

void ZCInPlaceDateEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    // Sets the has changed flag
    m_HasChanged = true;    
    // Call the base function
    ZCSearchEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZCInPlaceDateEdit::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
}

void ZCInPlaceDateEdit::OnExtendedCommand()
{
    // Process Extended
    if (GetParent() && ISA(GetParent(), ZCPropertyListCtrl))
    {
        ZBPropertyItem* pItem = dynamic_cast<ZCPropertyListCtrl*>(GetParent())->GetCurrentPropertyItem();

        CString ProposedValue = GetEditText();
        // Save the value
        SaveValue();
        // The extended function for duration is handled internally.
        // We own the standard duration dialog
        if (pItem)
        {
            // Display the duration dialog and 
            // Change the window text to the proposed value

            // Check the conversion
            // RS-MODIF 05.08.2005: �dition de date
            //ZBDuration value;
            ZBDate value;
            bool ConversionCorrect = ZUStringFormatter::ConvertFormattedBuffer( ProposedValue, (ZBDate&)value, pItem->GetStringFormat() );
            if (ConversionCorrect)
            {

                // Format the value function of the string format specified
                ProposedValue = ZUStringFormatter::GetFormattedBuffer( (ZBDate&)value, pItem->GetStringFormat() );
                SetEditText( ProposedValue );
                // Set the has changed value
                SetHasChanged( true );
            }
        }
    }
}

int ZCInPlaceDateEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    // JMR-MODIF - Le 11 ao�t 2005 - Ajout de l'appel � la fonction DoCreateButton.
    ZCSearchEdit::DoCreateButton( FALSE );

    if( ZCSearchEdit::OnCreate( lpCreateStruct ) == -1 )
        return -1;
    
    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(0, 1);

    CWnd* pParent = GetParent();
    ASSERT(pParent != NULL);

    CFont* pFont = pParent->GetFont();
    DWORD dwStyle = WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL;
    if (m_IsReadOnly)
        dwStyle |= ES_READONLY;
    SetFont(pFont);

    return 0;
}


BOOL ZCInPlaceDateEdit::OnEraseBkgnd(CDC* /*pDC*/)
{
    return TRUE;    
}

void ZCInPlaceDateEdit::OnSetFocus(CWnd* pOldWnd) 
{
    ZCSearchEdit::OnSetFocus(pOldWnd);
    
}

