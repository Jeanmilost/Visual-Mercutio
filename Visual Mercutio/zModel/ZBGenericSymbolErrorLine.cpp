/****************************************************************************
 * ==> PSS_GenericSymbolErrorLine ------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic symbol error line                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZBGenericSymbolErrorLine.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

ZBGenericSymbolErrorLine::ZBGenericSymbolErrorLine(const CString message /*= ""*/) :
    PSS_ErrorLine(message, -1)
{
    BuildString();
}

ZBGenericSymbolErrorLine::ZBGenericSymbolErrorLine(const CString    message,
                                                   const CString    symbolname,
                                                   const CString    symbolpath,
                                                   int                error        /*= -1*/,
                                                   int                type        /*= 0*/) :
    PSS_ErrorLine(message, -1, error, type),
    m_SymbolName(symbolname),
    m_SymbolPath(symbolpath)
{
    BuildString();
}

ZBGenericSymbolErrorLine::ZBGenericSymbolErrorLine(UINT            nIDSmessage,
                                                   const CString    symbolname,
                                                   const CString    symbolpath,
                                                   int                error        /*= -1*/,
                                                   int                type        /*= 0*/) :
    PSS_ErrorLine(nIDSmessage, -1, error, type),
    m_SymbolName(symbolname),
    m_SymbolPath(symbolpath)
{
    BuildString();
}

ZBGenericSymbolErrorLine::~ZBGenericSymbolErrorLine()
{}

ZBGenericSymbolErrorLine::ZBGenericSymbolErrorLine(const ZBGenericSymbolErrorLine& src)
{
    *this = src;
}

ZBGenericSymbolErrorLine& ZBGenericSymbolErrorLine::operator=(const ZBGenericSymbolErrorLine& src)
{
    m_SymbolName = src.m_SymbolName;
    m_SymbolPath = src.m_SymbolPath;

    // Call the base class assignement operator
    PSS_ErrorLine::operator=((const PSS_ErrorLine&)src);

    return *this;
}

void ZBGenericSymbolErrorLine::BuildString()
{
    PSS_Tokenizer Tokenizer(';');

    // Add the error type
    if (GetErrorType() == -1)
    {
        Tokenizer.AddToken(_T(" "));
    }
    else
    {
        // Add the error type
        CString s;

        switch (GetErrorType())
        {
            case 0:
            {
                s = _T("warning");
                break;
            }

            case 1:
            {
                s = _T("error");
                break;
            }

            case 2:
            default:
            {
                s = _T(".");
                break;
            }
        }

        Tokenizer.AddToken(s);

        // Add the symbol name
        Tokenizer.AddToken(GetSymbolName());

        // Add the symbol path
        Tokenizer.AddToken(_T("[") + GetSymbolPath() + _T("]"));
    }

    // Add the error message
    Tokenizer.AddToken(GetErrorMessage());

    // Assign the string
    AssignString(Tokenizer.GetString());
}

void ZBGenericSymbolErrorLine::Parse()
{
    PSS_Tokenizer Tokenizer(';');

    // Extract the type
    CString TypeStr = Tokenizer.GetFirstToken(GetBuffer(GetLength() + 1));

    if (TypeStr == _T(" "))
    {
        // Extract the message
        SetErrorMessage(Tokenizer.GetNextToken());
    }
    else
    {
        if (TypeStr == _T("warning"))
        {
            SetErrorType(0);
        }
        else if (TypeStr == _T("error"))
        {
            SetErrorType(1);
        }
        else if (TypeStr == _T("."))
        {
            SetErrorType(2);
        }
        else
        {
            SetErrorType(2);
        }

        // Extract and set the symbol name
        SetSymbolName(Tokenizer.GetNextToken());

        // Extract and set the symbol path
        CString path = Tokenizer.GetNextToken();

        if ((path.GetLength() - 2) > 0)
        {
            SetSymbolPath(path.Mid(1, path.GetLength() - 2));
        }

        // Extract and set the error message
        SetErrorMessage(Tokenizer.GetNextToken());
    }

    ReleaseBuffer(-1);
}
