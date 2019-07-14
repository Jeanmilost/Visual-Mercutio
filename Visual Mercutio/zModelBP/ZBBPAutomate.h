/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPAutomate
//@module ZBBPAutomate.h | Interface of the <c ZBBPAutomate> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         06/2001
// <nl>Description:  ZBBPAutomate Mercutio automate
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)
#define AFX_ZBBPAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zWkf\PSS_AutomationMachine.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIf - Le 21 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBBPAutomate : public PSS_AutomationMachine
{
public:

    ZBBPAutomate( ZDProcessGraphModelMdl* pModel = NULL, ZILog* pLog = NULL );
    ZBBPAutomate( ZBSymbol* pSymbol, ZDProcessGraphModelMdl* pModel = NULL, ZILog* pLog = NULL );

    virtual ~ZBBPAutomate();

    //////////////////////////////////////////////////////////////////////
    // Call back operations
    // This operation must fill sets of symbol and link corresponding to the 
    // the symbol and link pointer and the direction 
    // attributes if there is one.
    // Return the move status
    virtual IEAutomationMoveStatus RequestMoveForward(PSS_StateObject*   pState,
                                                      PSS_StateMachine*  pStateMachine,
                                                      PSS_SymbolSet&     symbolSet,
                                                      PSS_StateLinksSet& stateLinkSet,
                                                      ZILog*             pLog);

    
    //////////////////////////////////////////////////////////////////////
    // Automation basic call-back
    virtual bool OnStart    ( ZILog* pLog );
    virtual bool OnStop        ( ZILog* pLog );
    virtual bool OnPause    ( ZILog* pLog );
    virtual bool OnResume    ( ZILog* pLog );

    //////////////////////////////////////////////////////////////////////
    // Status call-back
    virtual bool OnObjectIsFinished                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnObjectIsPaused                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnObjectIsWaitingForOtherLinks    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );

    //////////////////////////////////////////////////////////////////////
    // Navigation call-back
    virtual bool OnBeforeRequestMoveForward        (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnNextSymbolAfterMoveForward    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnBeforeMoveForward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnAfterMoveForward                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnBeforeMoveBackward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnAfterMoveBackward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );

    //////////////////////////////////////////////////////////////////////
    // Exception call-back
    virtual bool OnObjectError                    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnReachMaximumLoopCounter        ( ZILog* pLog );
    virtual bool OnReachMaximumInPauseCounter    ( ZILog* pLog );

    virtual bool OnReachMaximumWaitingForOtherLinksCounter( ZILog* pLog );

private:

    IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardStartSymbol(PSS_StateObject*    pState,
                                                                                           PSS_SymbolSet&        SymbolSet,
                                                                                           PSS_StateLinksSet&    StateLinkSet,
                                                                                           ZILog*            pLog );

    IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardProcedureSymbol(PSS_StateObject*    pState,
                                                                                               PSS_SymbolSet&        SymbolSet,
                                                                                               PSS_StateLinksSet&    StateLinkSet,
                                                                                               ZILog*            pLog );

    IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardDoorSymbol(PSS_StateObject*    pState,
                                                                                          PSS_SymbolSet&        SymbolSet,
                                                                                          PSS_StateLinksSet&    StateLinkSet,
                                                                                          ZILog*            pLog );

    IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardPageSymbol(PSS_StateObject*    pState,
                                                                                          PSS_SymbolSet&        SymbolSet,
                                                                                          PSS_StateLinksSet&    StateLinkSet,
                                                                                          ZILog*            pLog );

    IEAutomationMoveStatus ZBBPAutomate::RequestMoveForwardStopSymbol(PSS_StateObject*    pState,
                                                                                          PSS_SymbolSet&        SymbolSet,
                                                                                          PSS_StateLinksSet&    StateLinkSet,
                                                                                          ZILog*            pLog );
};

#endif
