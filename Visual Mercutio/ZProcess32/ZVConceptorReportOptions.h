// ZVConceptorReportOptions.h : header file

#if !defined(AFX_ZVCONCEPTORREPORTOPTIONS_H__4ADDB473_588E_4D04_AD86_146AE0FB649B__INCLUDED_)
#define AFX_ZVCONCEPTORREPORTOPTIONS_H__4ADDB473_588E_4D04_AD86_146AE0FB649B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JMR-MODIF - Le 6 mars 2006 - Ajout de l'en-t�te ZWizard.h.
#include "zBaseLib\ZWizard.h"

#include "Resource.h"

// JMR-MODIF - Le 6 mars 2006 - Ajout des d�clarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// JMR-MODIF - Le 6 mars 2006 - Utilisation de ZIWizardDialog comme h�ritage plut�t que CDialog, et
// mise � jour de l'interface de la fen�tre de s�lection pour correspondance avec le look g�n�ral de Mercutio.

/////////////////////////////////////////////////////////////////////////////
// ZVConceptorReportOptions dialog

class ZVConceptorReportOptions : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVConceptorReportOptions( CWnd* pParent = NULL );

    // Dialog Data
    //{{AFX_DATA(ZVConceptorReportOptions)
    enum { IDD = IDD_CONCEPTOR_REPORT };
    BOOL    m_Deliverables;
    BOOL    m_Detail;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVConceptorReportOptions)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(ZVConceptorReportOptions)
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVCONCEPTORREPORTOPTIONS_H__4ADDB473_588E_4D04_AD86_146AE0FB649B__INCLUDED_)
