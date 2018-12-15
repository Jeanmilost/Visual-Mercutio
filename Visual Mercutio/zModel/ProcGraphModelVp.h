// ProcGraphModelVp.h : interface of the ZIProcessGraphModelViewport class
//

#if !defined(AFX_OBJECTIVVP_H__32F500A5_589A_45D2_A615_D168340EAFC6__INCLUDED_)
#define AFX_OBJECTIVVP_H__32F500A5_589A_45D2_A615_D168340EAFC6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "Views/OdRulerWrapper.h"
#include "ZBPageUnits.h"

#include "zBaseLib\ZVDocumentPageSetup.h"

// Forward declaration
class ZDProcessGraphModelController;
class ZDProcessGraphModelMdl;

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZIProcessGraphModelViewport : public CODBufferedRulerViewport
{
public:

    ZIProcessGraphModelViewport();

// Operations
public:

    virtual void OnInitialUpdate();

    // OnInitialUpdateVp is calling OnInitialUpdate()
    void OnInitialUpdateVp()
    {
        ZIProcessGraphModelViewport::OnInitialUpdate();
    };

    virtual void OnUpdate( IMvcSubject* pSubject, IMvcMessage* pMsg );

    // Resize the model
    void SizeVp( ZVDocumentPageSetup* PageSetup );

    // Update the page look according to model settings
    void UpdatePageLook( ZVDocumentPageSetup* PageSetup );

    ZDProcessGraphModelController*    GetModelController();
    ZDProcessGraphModelMdl*            GetModel();

    void    SetRuler( CODRuler& Ruler );
    void    SetPageUnits( ZBPageUnits& PageUnits );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIProcessGraphModelViewport)
    virtual BOOL CreateController();
    //}}AFX_VIRTUAL

    BOOL AssignNewController( ZDProcessGraphModelController* pCtlr, ZDProcessGraphModelMdl* pModel );

    static SECImage* CreateImageObjectFromFileExtension( const CString Filename );
    static SECImage* LoadImageFromFile( const CString Filename );
    bool ExportModelToImageFile( const CString Filename, CDC& dc );

protected:

    void CenterOrigin();

// Implementation
public:

    virtual ~ZIProcessGraphModelViewport();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTIVVP_H__32F500A5_589A_45D2_A615_D168340EAFC6__INCLUDED_)