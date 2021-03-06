/****************************************************************************
 * ==> PSS_HistoryProcessStatusRecordsetVersion99 --------------------------*
 ****************************************************************************
 * Description : Provides an historic process status recordset              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryProcessStatusRecordsetVersion99H
#define PSS_HistoryProcessStatusRecordsetVersion99H

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

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* History process status recordset
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoryProcessStatusRecordsetVersion99 : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_HistoryProcessStatusRecordsetVersion99)

    public:
        /**
        * Constructor
        *@param pDatabase - database
        *@param fileName - database file name
        */
        PSS_HistoryProcessStatusRecordsetVersion99(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

        /**
        * Gets the process status identifier field name
        *@return the process status identifier field name
        */
        virtual inline const CString GetProcessStatusIDFieldName() const;

        /**
        * Gets the identifier field name
        *@return the identifier field name
        */
        virtual inline const CString GetProcessIDFieldName() const;

        /**
        * Gets the date field name
        *@return the date field name
        */
        virtual inline const CString GetDateFieldName() const;

        /**
        * Gets the status field name
        *@return the status field name
        */
        virtual inline const CString GetStatusFieldName() const;

        /**
        * Gets the current activity field name
        *@return the current activity field name
        */
        virtual inline const CString GetCurrentActivityFieldName() const;

        /**
        * Gets the process status identifier
        *@return the process status identifier
        */
        virtual inline long GetProcessStatusID() const;

        /**
        * Sets the process status identifier
        *@param value - the process status identifier
        */
        virtual inline void SetProcessStatusID(long value);

        /**
        * Gets the process identifier
        *@return the process identifier
        */
        virtual inline long GetProcessID() const;

        /**
        * Sets the process identifier
        *@param value - the process identifier
        */
        virtual inline void SetProcessID(long value);

        /**
        * Gets the date
        *@return the date
        */
        virtual inline COleDateTime GetDate() const;

        /**
        * Sets the date
        *@param value - the date
        */
        virtual inline void SetDate(const COleDateTime& value);

        /**
        * Gets the status
        *@return the status
        */
        virtual inline CString GetStatus() const;

        /**
        * Sets the status
        *@return the status
        */
        virtual inline void SetStatus(const CString& value);

        /**
        * Gets the current activity
        *@return the current activity
        */
        virtual inline long GetCurrentActivity() const;

        /**
        * Sets the current activity
        *@param value - the current activity
        */
        virtual inline void SetCurrentActivity(long value);

        /**
        * Gets the default database name
        *@return the default database name
        */
        virtual CString GetDefaultDBName();

        /**
        * Gets the default SQL for recordset
        *@return the default SQL for recordset
        */
        virtual CString GetDefaultSQL();

        /**
        * DDX/DDV data exchange
        *@param pFX - DDX/DDV data
        */
        virtual void DoFieldExchange(CDaoFieldExchange* pFX);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        COleDateTime m_Date;
        CString      m_Status;
        CString      m_DatabaseFileName;
        long         m_ProcessStatusID;
        long         m_ProcessID;
        long         m_CurrentActivity;
};

//---------------------------------------------------------------------------
// PSS_HistoryProcessStatusRecordsetVersion99
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessStatusRecordsetVersion99::GetProcessStatusIDFieldName() const
{
    return _T("[ProcessStatusID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessStatusRecordsetVersion99::GetProcessIDFieldName() const
{
    return _T("[ProcessID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessStatusRecordsetVersion99::GetDateFieldName() const
{
    return _T("[Date]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessStatusRecordsetVersion99::GetStatusFieldName() const
{
    return _T("[Status]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessStatusRecordsetVersion99::GetCurrentActivityFieldName() const
{
    return _T("[CurrentActivity]");
}
//---------------------------------------------------------------------------
long PSS_HistoryProcessStatusRecordsetVersion99::GetProcessStatusID() const
{
    return m_ProcessStatusID;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::SetProcessStatusID(long value)
{
    m_ProcessStatusID = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryProcessStatusRecordsetVersion99::GetProcessID() const
{
    return m_ProcessID;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::SetProcessID(long value)
{
    m_ProcessID = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryProcessStatusRecordsetVersion99::GetDate() const
{
    return m_Date;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::SetDate(const COleDateTime& value)
{
    m_Date = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessStatusRecordsetVersion99::GetStatus() const
{
    return m_Status;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::SetStatus(const CString& value)
{
    m_Status = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryProcessStatusRecordsetVersion99::GetCurrentActivity() const
{
    return m_CurrentActivity;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::SetCurrentActivity(long value)
{
    m_CurrentActivity = value;
}
//---------------------------------------------------------------------------

#endif
