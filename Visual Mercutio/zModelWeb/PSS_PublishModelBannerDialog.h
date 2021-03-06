/****************************************************************************
 * ==> PSS_PublishModelBannerDialog ----------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model banners to publish *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelBannerDialogH
#define PSS_PublishModelBannerDialogH

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
#include "zBaseLib\PSS_WizardDialog.h"
#include "zWinUtil32\PSS_SearchEdit.h"

// resources
#include "zModelWebRes.h"

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog box allowing to select the model banners to publish
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishModelBannerDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param hyperLink - banner hyperLink
        *@param imageFileName - banner image file namer
        *@param pParent - parent window, can be NULL
        */
        PSS_PublishModelBannerDialog(const CString& hyperLink     = _T(""),
                                     const CString& imageFileName = _T(""),
                                     CWnd*          pParent       = NULL);

        /**
        * Gets the hyperlink
        *@return the hyperlink
        */
        virtual inline CString GetHyperLink() const;

        /**
        * Gets the image file name
        *@return the image file name
        */
        virtual inline CString GetImageFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelBannerDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelBannerDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_BANNER
        };

        CString        m_ImageFileName;
        PSS_SearchEdit m_Image;
        CString        m_HyperLink;
};

//---------------------------------------------------------------------------
// PSS_PublishModelBannerDialog
//---------------------------------------------------------------------------
CString PSS_PublishModelBannerDialog::GetHyperLink() const
{
    return m_HyperLink;
}
//---------------------------------------------------------------------------
CString PSS_PublishModelBannerDialog::GetImageFileName() const
{
    return m_ImageFileName;
}
//---------------------------------------------------------------------------

#endif
