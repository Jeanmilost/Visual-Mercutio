/****************************************************************************
 * ==> PSS_SoapPublishModelAttributes --------------------------------------*
 ****************************************************************************
 * Description : Publish the model attributes to Messenger through a SOAP   *
 *               protocol                                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishModelAttributesH
#define PSS_SoapPublishModelAttributesH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zModel\PSS_ModelNavigation.h"
#include "zProperty\PSS_Property.h"
#include "zSOAP\PSS_SoapPublisher_ModelAttributes.h"
#include "PSS_PublishMessengerModelInformation.h"

// forward class declaration
class PSS_PublishMessengerModelInformation;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publish the model attributes to Messenger through a SOAP protocol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishModelAttributes : public PSS_ModelNavigation
{
    public:
        /**
        * Constructor
        *@param pInfo - the info to publish
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_SoapPublishModelAttributes(PSS_PublishMessengerModelInformation* pInfo,
                                       PSS_ProcessGraphModelMdl*             pModel = NULL,
                                       void*                                 pClass = NULL);

        virtual ~PSS_SoapPublishModelAttributes();

        /**
        * Called when a publication is starting
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when a publication is finished
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when symbol properties should be added to publication
        *@param pSymbol - symbol for which attributes sould be published
        *@return true on success, otherwise false
        */
        virtual bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when link properties should be added to publication
        *@param pSymbol - symbol for which attributes sould be published
        *@return true on success, otherwise false
        */
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        /**
        * Publishes the properties
        *@param propSet - properties to publish
        */
        void Publish(const PSS_Properties::IPropertySet& propSet);

        /**
        * Checks if a property mathcing with key already exists in the array, adds it if not
        *@param key - key to check and add
        *@return true if key already exists and was not added, false if key was not found and added
        */
        bool KeyExist(int key);

    private:
        PSS_PublishMessengerModelInformation* m_pInfo;
        PSS_SoapPublisher_ModelAttributes     m_PubMdlAttr;
        int                                   m_IDArray[500];
        CString                               m_MessengerAddress;
};

#endif
