/****************************************************************************
 * ==> PSS_ActivityLogRecordset --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log recordset                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityLogRecordset.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ActivityLogRecordset, CRecordset)
//---------------------------------------------------------------------------
// PSS_ActivityLogRecordset
//---------------------------------------------------------------------------
PSS_ActivityLogRecordset::PSS_ActivityLogRecordset(CDatabase* pDB) :
    CRecordset(pDB)
{
    // configure field number in base
    m_nFields = 11;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetDefaultConnect() const
{
    return "ODBC;DSN=ADSoft Server Database;";
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetDefaultSQL() const
{
    return "ActivityLog";
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_ActivityLogRecordset)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Date(pFX, "Date",       m_Date);
    RFX_Text(pFX, "FolderName", m_FolderName);
    RFX_Text(pFX, "File",       m_File);
    RFX_Text(pFX, "DataFile",   m_DataFile);
    RFX_Text(pFX, "Process",    m_Process);
    RFX_Text(pFX, "Activity",   m_Activity);
    RFX_Date(pFX, "DueDate",    m_DueDate);
    RFX_Text(pFX, "Status",     m_Status);
    RFX_Text(pFX, "Sender",     m_Sender);
    RFX_Text(pFX, "Receiver",   m_Receiver);
    RFX_Text(pFX, "Comments",   m_Comments);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
