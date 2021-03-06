/****************************************************************************
 * ==> PSS_SrvMsgs ---------------------------------------------------------*
 ****************************************************************************
 * Description : This file defines the Messenger server Windows messages    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SrvMsgsH
#define PSS_SrvMsgsH

#if _MSC_VER > 1000
    #pragma once
#endif

// windows
#include <Windows.h>

const UINT UM_STARTSERVER                 = WM_USER + 10;
const UINT UM_STOPSERVER                  = WM_USER + 11;
const UINT UM_PAUSESERVER                 = WM_USER + 12;
const UINT UM_RESTARTSERVER               = WM_USER + 13;
const UINT UM_CHOOSESERVER                = WM_USER + 14;
const UINT UM_ICON_NOTIFY                 = WM_USER + 15;
const UINT UM_SHOWORGANIZED               = WM_USER + 16;
const UINT UM_SHOWDETAILED                = WM_USER + 17;
const UINT UM_SHOWUSER                    = WM_USER + 18;
const UINT UM_SHOWALLUSERS                = WM_USER + 19;

// sent when a new event has been created
const UINT UM_NEWEVENT                    = WM_USER + 20;

// sent when a new activity event has been created
const UINT UM_NEWACTIVITYEVENT            = WM_USER + 21;

// should animate the icon
const UINT UM_ZSERVERANIMATE              = WM_USER + 22;

// should animate the icon for ZProcView
const UINT UM_ZPROCVIEWERANIMATE          = WM_USER + 23;

// sent when a new reminder event has been created
const UINT UM_NEWACTIVITYREMINDEREVENT    = WM_USER + 24;

// sent when a new user activity event has been created
const UINT UM_NEWUSERACTIVITYEVENT        = WM_USER + 25;
const UINT UM_NEWUSERACTIVITYEVENT_ADD    = WM_USER + 26;
const UINT UM_NEWUSERACTIVITYEVENT_REMOVE = WM_USER + 27;
const UINT UM_MESSAGELIST                 = WM_USER + 28;
const UINT UM_DELETE                      = WM_USER + 29;
const UINT UM_SHOWUNASSIGNED              = WM_USER + 30;
const UINT UM_OPTIONS                     = WM_USER + 31;
const UINT UM_REFRESH                     = WM_USER + 32;

#endif