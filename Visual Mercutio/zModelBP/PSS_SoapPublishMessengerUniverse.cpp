/****************************************************************************
 * ==> PSS_SoapPublishMessengerUniverse ------------------------------------*
 ****************************************************************************
 * Description : Publish the Messenger universe to Messenger through a SOAP *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublishMessengerUniverse.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "PSS_PublishMessengerModelInformation.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SoapPublishMessengerUniverse
//---------------------------------------------------------------------------
PSS_SoapPublishMessengerUniverse::PSS_SoapPublishMessengerUniverse(PSS_PublishMessengerModelInformation* pInfo, PSS_Log* pLog) :
    m_pInfo(pInfo),
    m_pLog(pLog)
{}
//---------------------------------------------------------------------------
PSS_SoapPublishMessengerUniverse::~PSS_SoapPublishMessengerUniverse()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishMessengerUniverse::Publish()
{
    // valid info to send?
    if (m_pInfo && m_pInfo->m_pDoc && m_pInfo->m_pDoc->GetMainLogicalSystem())
    {
        // copy the publication address from source info
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

        // publish the Messenger universe and its alias
        m_PubMngUni.Reset();
        m_PubMngUni.Add(PSS_SoapData_MessengerUniverse(PSS_String16(m_pInfo->m_pDoc->GetSystemDefGUID()),
                                                       PSS_String16(m_pInfo->m_pDoc->GetPrestationsDefGUID()),
                                                       PSS_String16(m_pInfo->m_pDoc->GetUserDefGUID())));
        m_PubMngUni.AddAlias(m_pInfo->m_MessengerAlias);

        // log the debug info
        #ifdef _DEBUG
            CString s;
            s.Format(_T(" System def GUID = %s\n" ), (const char*)m_pInfo->m_pDoc->GetSystemDefGUID());
            TRACE(s);

            s.Format(_T(" Prestations def GUID = %s\n"), (const char*)m_pInfo->m_pDoc->GetPrestationsDefGUID());
            TRACE(s);

            s.Format(_T( " Workgroup def GUID = %s\n" ), (const char*)m_pInfo->m_pDoc->GetUserDefGUID());
            TRACE(s);
        #endif

        // send the data to Messenger
        return m_PubMngUni.Send();
    }

    return false;
}
//---------------------------------------------------------------------------
