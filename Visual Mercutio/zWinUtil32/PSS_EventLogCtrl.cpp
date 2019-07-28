/****************************************************************************
 * ==> PSS_EventLogCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event log control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventLogCtrl.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_MessageColText[] =
{
    IDS_COLUMN1_EVENTLOG,
    IDS_COLUMN2_EVENTLOG,
    IDS_COLUMN3_EVENTLOG
};

static int g_MessageColSize[] =
{
    160,
    300,
    300
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_EventLogCtrl, CListCtrl)
    //{{AFX_MSG_MAP(PSS_EventLogCtrl)
    ON_MESSAGE(UM_NEWEVENT, OnNewEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventLogCtrl
//---------------------------------------------------------------------------
PSS_EventLogCtrl::PSS_EventLogCtrl(ZBEventManager* pEventManager) :
    m_pEventManager(pEventManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EventLogCtrl::~PSS_EventLogCtrl()
{}
//---------------------------------------------------------------------------
#ifdef _WIN32
    ZBEventServer& operator >> (ZBEventServer& left, PSS_EventLogCtrl& listCtrl)
    {
        const int index = listCtrl.GetItemCount();

        // add the event date
        listCtrl.InsertItem(index, left.GetFormatedTimeStamp());

        // add the filename
        listCtrl.SetItem(index, 1, LVIF_TEXT, left.GetFilename(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the result
        listCtrl.SetItem(index, 2, LVIF_TEXT, left.GetEventResultStr(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return left;
    }
#endif
//---------------------------------------------------------------------------
void PSS_EventLogCtrl::Initialize(ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_EventLogCtrl::Refresh()
{
    DeleteAllItems();

    // columns were built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
        ((ZBEventServer&)*m_pEventManager->GetEventAt(i)) >> *this;
}
//---------------------------------------------------------------------------
LRESULT PSS_EventLogCtrl::OnNewEvent(WPARAM wParam, LPARAM lParam)
{
    ZBEventServer* pEvent = (ZBEventServer*)lParam;

    // columns were built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;

    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_EventLogCtrl::BuildColumns()
{
    ZIListCtrl::BuildColumns(3, g_MessageColSize, g_MessageColText);
    m_ColumnsHasBeenBuilt = TRUE;
    return TRUE;
}
//---------------------------------------------------------------------------