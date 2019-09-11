// ProcGraphModelVp.cpp : implementation of the ZIProcessGraphModelViewport class

#include "stdafx.h"
#include "ProcGraphModelVp.h"
#include "ProcGraphModelCtlr.h"
#include "ProcGraphModelView.h"
#include "ProcGraphModelMdl.h"

#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelViewport

ZIProcessGraphModelViewport::ZIProcessGraphModelViewport()
{
}

ZIProcessGraphModelViewport::~ZIProcessGraphModelViewport()
{
    // JMR-MODIF - Le 7 octobre 2005 - Supprime le lien sur le mod�le, car celui-ci est d�j� d�truit.
    m_pModel = NULL;
}

ZDProcessGraphModelController* ZIProcessGraphModelViewport::GetModelController()
{ 
    return dynamic_cast<ZDProcessGraphModelController*>( GetController() );
}

ZDProcessGraphModelMdl*    ZIProcessGraphModelViewport::GetModel()
{
    if ( GetCanvasModel() && ISA( GetCanvasModel(), ZDProcessGraphModelMdl ) )
    {
        return dynamic_cast<ZDProcessGraphModelMdl*>( GetCanvasModel() );
    }

    return NULL;
}

void ZIProcessGraphModelViewport::OnInitialUpdate()
{
    CODViewport::OnInitialUpdate();

    if ( GetModelController() )
    {
        GetModelController()->OnInitialUpdate();
    }
}

// JMR-MODIF - le 14 juillet 2005 - Supprim� les variables m_PageSize, m_StandardSize et m_Orientation de la fonction,
// remplac� par la classe PageSetup.
void ZIProcessGraphModelViewport::SizeVp( PSS_DocumentPageSetup* PageSetup )
{
    if ( PageSetup == NULL )
    {
        return;
    }

    SetMapMode( MM_ANISOTROPIC );

    // Sets the right units for the ruler
    GetRuler()->SetUnitOfMeasure    ( OD_CENTIMETERS );
    CODMeasure mGridSpacing            ( OD_CENTIMETERS, (const float)0.2 );
    SetHorizontalGridSpacing        ( mGridSpacing );
    SetVerticalGridSpacing            ( mGridSpacing );

    // Retreive the model pointer
    CODModel* pModel = GetCanvasModel();

    if (pModel != NULL)
    {
        // Sets the model page settings to the paper size and orientation
        pModel->GetPageSettings().SetPaperOrientation    ( PageSetup->GetOrientation() );
        pModel->GetPageSettings().SetPaperSize            ( PageSetup->GetStandardSize() );

        UpdatePageLook( PageSetup );

        OnUpdateMappingMode();
    }
}

// JMR-MODIF - le 18 juillet 2005 - Ajout� la variable PageSetup � la fonction.
void ZIProcessGraphModelViewport::UpdatePageLook( PSS_DocumentPageSetup* PageSetup )
{
    // Retreive the model pointer
    ZDProcessGraphModelMdl* pModel = GetModel();

    if ( pModel != NULL )
    {
        // Origin is initially 0,0.
        SetOrigin( 0, 0 );
        SetLogOrigin( 0, 0 );

        CalcPageDimensions();
        CSize pg = GetPageDimensions();

        // JMR-MODIF - Le 18 juillet 2005 - S'il n'y a pas d'imprimante install�e, ou si le format de papier
        // n'est pas reconnu, configure les dimensions de la page avec les valeurs par d�faut.
        if ( PageSetup->CanPrint() == FALSE ) pg = PageSetup->GetDefaultPageSize( CRect( 11, 32, 11, 32 ) );

        // Now sets the model size according to the page dimension
        pModel->SetSize( pg.cx, pg.cy );

        // Resize the viewport to the model size
        SizeToModel();

        SetExtents( pg.cx, pg.cy );
        SetLogExtents( pg.cx, pg.cy );

        SetVirtualOrigin( 0, 0 );
        SetVirtualSize( pg.cx, pg.cy );

        UpdateAll();
    }
}

void ZIProcessGraphModelViewport::CenterOrigin()
{
    CSize szVirtual( GetVirtualSize() );
    CPoint ptVirtualOrg( GetVirtualOrigin() );

    CSize szLog( GetLogSize() );

    CPoint ptLogOrg;
    
    // Assumes the logical origin is within the bounds of the virtual space.
    ptLogOrg.x = 0 - szLog.cx / 2; 
    ptLogOrg.y = 0 - szLog.cy / 2; 

    SetLogOrigin( ptLogOrg.x, ptLogOrg.y );

    Invalidate();
}

void ZIProcessGraphModelViewport::SetRuler( CODRuler& Ruler )
{
    CODRuler* pRuler = GetRuler();

    if ( pRuler )
    {
        pRuler->SetUnitOfMeasure( Ruler.GetUnitOfMeasure() );

        CODMeasure            logXUnit;
        CODMeasure            logYUnit;
        Ruler.GetLogicalUnitMeasure( logXUnit, logYUnit );

        if ( (float)logXUnit != 0 || (float)logYUnit != 0 )
        {
            pRuler->SetLogicalUnitMeasure( logXUnit, logYUnit );
        }

        CODMeasure            scaleFrom;
        CODMeasure            scaleTo;
        Ruler.GetMeasurementScale( scaleFrom, scaleTo );

        if ( (float)scaleFrom != 0 || (float)scaleTo != 0 )
        {
            pRuler->SetMeasurementScale( scaleFrom, scaleTo );
        }
    }
}

void ZIProcessGraphModelViewport::SetPageUnits( ZBPageUnits& PageUnits )
{
    CODRuler* pRuler = GetRuler();

    if ( pRuler )
    {
        pRuler->SetUnitOfMeasure( PageUnits.GetUnitOfMeasure() );

        CODMeasure            logXUnit;
        CODMeasure            logYUnit;
        PageUnits.GetLogicalUnitMeasure( logXUnit, logYUnit );

        if ( (float)logXUnit != 0 || (float)logYUnit != 0 )
        {
            pRuler->SetLogicalUnitMeasure( logXUnit, logYUnit );
        }

        CODMeasure            scaleFrom;
        CODMeasure            scaleTo;
        PageUnits.GetMeasurementScale( scaleFrom, scaleTo );

        if ( (float)scaleFrom != 0 || (float)scaleTo != 0 )
        {
            pRuler->SetMeasurementScale( scaleFrom, scaleTo );
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphModelViewport implementation

BOOL ZIProcessGraphModelViewport::CreateController()
{
    if ( GetModel() )
    {
        if ( m_pCtlr != NULL && m_bAutoDelCtlr )
        {
            delete m_pCtlr;
        }

        m_pCtlr = GetModel()->CreateController( this );

        // Sets the controller
        GetModel()->SetController( (CODController*)m_pCtlr );
        m_bAutoDelCtlr = TRUE;

        return TRUE;
    }

    return FALSE;
}

BOOL ZIProcessGraphModelViewport::AssignNewController( ZDProcessGraphModelController*    pCtlr,
                                                       ZDProcessGraphModelMdl*            pModel )
{
    if ( pCtlr )
    {
        if ( m_pCtlr != NULL && m_bAutoDelCtlr )
        {
            // First, remove the listener
            m_pCtlr->RemoveListener( this );
            delete m_pCtlr;
        }

        // Assigns the new controller to the viewport
        m_pCtlr = pCtlr;

        // Assigns the new model to the controller
        m_pCtlr->SetModel( pModel );

        // Create the controler
        m_pCtlr->Create( m_pWnd, this );

        // And add a listener to this viewport
        m_pCtlr->AddListener( this );

        // Sets the controller
        pModel->SetController( (CODController*)m_pCtlr );

        m_bAutoDelCtlr = TRUE;

        return TRUE;
    }

    return FALSE;
}

SECImage* ZIProcessGraphModelViewport::CreateImageObjectFromFileExtension( const CString Filename )
{
    SECImage* pImage = NULL;
    PSS_File file( Filename );

    if ( file.GetFileExt().CompareNoCase( _T( ".gif" ) ) == 0 )
    {
        pImage = new SECGif();
    }
    else if ( file.GetFileExt().CompareNoCase( _T( ".dib" ) ) == 0 )
    {
        pImage = new SECDib();
    }
    else if ( file.GetFileExt().CompareNoCase( _T( ".jpg" ) ) == 0 )
    {
        pImage = new SECJpeg();
    }
    else if ( file.GetFileExt().CompareNoCase( _T( ".pcx" ) ) == 0 )
    {
        pImage = new SECPcx();
    }
    else if ( file.GetFileExt().CompareNoCase( _T( ".tga" ) ) == 0 )
    {
        pImage = new SECTarga();
    }
    else if ( file.GetFileExt().CompareNoCase( _T( ".tif" ) ) == 0 )
    {
        pImage = new SECTiff();
    }

    return pImage;
}

SECImage* ZIProcessGraphModelViewport::LoadImageFromFile( const CString Filename )
{
    // JMR-MODIF - Le 5 ao�t 2005 - Ajout du test de la pr�sence d'un fichier avant de tenter de charger ce fichier.
    PSS_File myFile( Filename );

    if ( myFile.Exist() )
    {
        SECImage* pImage = CreateImageObjectFromFileExtension( Filename );

        if ( pImage )
        {
            if ( !pImage->LoadImage( Filename ) )
            {
                delete pImage;
                pImage = NULL;
            }
        }

        return pImage;
    }
    else return NULL;
}

bool ZIProcessGraphModelViewport::ExportModelToImageFile( const CString Filename, CDC& dc )
{
    SECImage* pImage = CreateImageObjectFromFileExtension( Filename );

    if ( pImage )
    {
        DrawImage( pImage, &dc );
        BOOL RetValue;

        TRY
        {
            RetValue = pImage->SaveImage( Filename );
        }
        CATCH( CFileException, e )
        {
            RetValue = FALSE;
        }
        END_CATCH

        delete pImage;

        return ( RetValue == TRUE ) ? true : false;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////

void ZIProcessGraphModelViewport::OnUpdate( IMvcSubject* pSubject, IMvcMessage* pMsg )
{
    CODViewport::OnUpdate( pSubject, pMsg );
}
