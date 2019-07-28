/****************************************************************************
 * ==> PSS_CommonFieldTreeCtrl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a common field tree control                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CommonFieldTreeCtrlH
#define PSS_CommonFieldTreeCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\FieldRep.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS PSS_CommonFieldTreeCtrl : public ZITreeCtrl
{
    public:
        /**
        * Constructor
        *@param pFieldRepository - filed repository, can be NULL
        */
        PSS_CommonFieldTreeCtrl(ZBFieldRepository* pFieldRepository = NULL);

        virtual ~PSS_CommonFieldTreeCtrl();

        /**
        * Initialize the control
        *@param pFieldRepository - filed repository
        */
        virtual void Initialize(ZBFieldRepository* pFieldRepository);

        /**
        * Reinitialize the control
        *@param pFieldRepository - filed repository
        */
        virtual void ReInitialize(ZBFieldRepository* pFieldRepository);

        /**
        * Refreshes the control
        */
        virtual void Refresh();

        /**
        * Gets the selected field
        *@return the selected filed, NULL if no selection or on error
        */
        virtual ZAObjectDefinition* GetSelectedField();

        //{{AFX_MSG(PSS_CommonFieldTreeCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBFieldRepository* m_pFieldRepository;
        CImageList         m_ImageListTree;
        CString            m_FieldDescriptionKey;
        CString            m_UserHelpKey;
        CString            m_IsReadOnlyKey;
        CString            m_SortedKey;
        CString            m_ClassNameKey;
        CString            m_HistoryKey;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CommonFieldTreeCtrl(const PSS_CommonFieldTreeCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_CommonFieldTreeCtrl& operator = (const PSS_CommonFieldTreeCtrl& other);

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Initializes the tree
        */
        void InitializeTree();

        /**
        * Adds a field item
        *@param pField - field item to add
        */
        void AddFieldItem(ZAObjectDefinition* pField);

        /**
        * Adds a field history item
        *@param pHistory - field history item to add
        *@param hParentTreeItem - parent item in which the history item will be added, if NULL will be added in root
        */
        void AddFieldHistoryItem(ZAHistoryField* pHistory, HTREEITEM hParentTreeItem);
};

#endif