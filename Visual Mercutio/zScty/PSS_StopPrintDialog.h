/****************************************************************************
 * ==> PSS_StopPrintDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a stop print dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StopPrintDialogH
#define PSS_StopPrintDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Stop print dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StopPrintDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window
        */
        PSS_StopPrintDialog(CWnd* pParent = NULL);

        /**
        * Gets the entered code
        *@return the entered code
        */
        virtual inline CString GetCode() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_StopPrintDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnDelock();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_Code;
};

//---------------------------------------------------------------------------
// PSS_StopPrintDialog
//---------------------------------------------------------------------------
CString PSS_StopPrintDialog::GetCode() const
{
    return m_Code;
}
//---------------------------------------------------------------------------

#endif
