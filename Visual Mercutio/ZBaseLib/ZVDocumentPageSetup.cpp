// **********************************************************************************************************
// *                                          Classe ZVDocumentPageSetup                                    *
// **********************************************************************************************************
// * Cette classe permet la gestion du format de page du document. Elle permet de param�trer une page,        *
// * et elle prend �galement en charge le contr�le de la validit� de cette page par rapport au device        *
// * d'impression.                                                                                            *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZVDocumentPageSetup.h"

// JMR-MODIF - Le 23 f�vrier 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **********************************************************************************************************
// *                                        Constructeur(s) et destructeur                                    *
// **********************************************************************************************************

// Constructeur par d�faut de la classe ZVDocumentPageSetup.
ZVDocumentPageSetup::ZVDocumentPageSetup()
{
    sBkGndName            = _T( "" );

    m_StandardSize        = DefaultStandardSize;
    m_Orientation        = DefaultOrientation;
    m_PaperSize            = DefaultPaperSize;

    bIsFormatDefined    = FALSE;
    bIsCancelled        = FALSE;
    bCanPrint            = FALSE;
    bIsChecked            = FALSE;
}

// Destructeur de la classe ZVDocumentPageSetup.
ZVDocumentPageSetup::~ZVDocumentPageSetup()
{
}

// **********************************************************************************************************
// *                               Fonctions priv�es de la classe ZVDocumentPageSetup                        *
// **********************************************************************************************************

/* Cette fonction permet de r�cup�rer les donn�es de pages, n�cessaires au document, depuis le driver d'impression.
   Retourne TRUE si un driver existe, sinon retourne FALSE.*/
BOOL ZVDocumentPageSetup::GetPrinterSettings( CSize& PaperSize, short& StandardSize, short& Orientation )
{
    BOOL bRet = FALSE;

    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    if ( pPrintDlg == NULL )
    {
        return FALSE;
    }

    // Recherche une imprimante par d�faut.
    if ( AfxGetApp()->GetPrinterDeviceDefaults( pPrintDlg ) )
    {
        // Obtient les pointeurs vers les deux structures de param�tres.
        DEVNAMES FAR *lpDevNames    = (DEVNAMES FAR *)::GlobalLock( pPrintDlg->hDevNames );
        DEVMODE FAR  *lpDevMode        = (DEVMODE FAR  *)::GlobalLock( pPrintDlg->hDevMode );

        // Obtient les informations sp�cifiques au Driver.
        CString szDriver( (LPTSTR)lpDevNames + lpDevNames->wDriverOffset );
        CString szDevice( (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset );
        CString szOutput( (LPTSTR)lpDevNames + lpDevNames->wOutputOffset );

        // Cr�e un objet CDC bas� sur les param�tres courants.
        CDC pDC;
        pDC.CreateDC( szDriver, szDevice, szOutput, lpDevMode );

        // JMR-MODIF - Le 24 avril 2006 - Teste la validit� de la variable pDC avant de l'utiliser.
        if ( pDC == NULL )
        {
            PaperSize        = DefaultPaperSize;
            StandardSize    = DefaultStandardSize;
            Orientation        = DefaultOrientation;

            delete pPrintDlg;

            return FALSE;
        }

        // Obtient l'orientation du papier.
        Orientation        = lpDevMode->dmOrientation;

        // Obtient la taille standard.
        StandardSize    = lpDevMode->dmPaperSize;

        // Utilise l'objet CDC pour retrouver la hauteur et la largeur de la page courante.
        PaperSize.cx    = pDC.GetDeviceCaps( HORZSIZE );
        PaperSize.cy    = pDC.GetDeviceCaps( VERTSIZE );

        // D�salloue le pointeur du CDC.
        pDC.DeleteDC();

        // D�verouille les pointeurs vers les structures de param�tres.
        ::GlobalUnlock( pPrintDlg->hDevNames );
        ::GlobalUnlock( pPrintDlg->hDevMode );

        bRet = TRUE;
    }
    else
    {
        PaperSize        = DefaultPaperSize;
        StandardSize    = DefaultStandardSize;
        Orientation        = DefaultOrientation;
    }

    delete pPrintDlg;

    return bRet;
}

// Cette fonction modifie les param�tres par d�faut du driver d'impression.
void ZVDocumentPageSetup::ChangePrinterSettings( short StandardSize, short Orientation )
{
#ifdef _WIN32

    PRINTDLG pd;

    pd.lStructSize = (DWORD) sizeof( PRINTDLG );

    // Recherche une imprimante par d�faut.
    if ( AfxGetApp()->GetPrinterDeviceDefaults( &pd ) )
    {
        // Verouille les acc�s m�moires.
        DEVMODE FAR*    pDevMode = (DEVMODE FAR*)::GlobalLock( pd.hDevMode );
        LPDEVNAMES        lpDevNames;
        LPTSTR            lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE            hPrinter;

        if ( pDevMode )
        {
            // Change les propri�t�s de l'imprimante.
            pDevMode->dmPaperSize    = StandardSize;
            pDevMode->dmOrientation    = Orientation;

            // Lib�re les acc�s m�moire.
            lpDevNames = (LPDEVNAMES)GlobalLock( pd.hDevNames );
            lpszDriverName = (LPTSTR)lpDevNames + lpDevNames->wDriverOffset;
            lpszDeviceName = (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset;
            lpszPortName   = (LPTSTR)lpDevNames + lpDevNames->wOutputOffset;

            OpenPrinter( lpszDeviceName, &hPrinter, NULL );

            DocumentProperties( NULL,
                                hPrinter,
                                lpszDeviceName,
                                pDevMode,
                                pDevMode,
                                DM_IN_BUFFER | DM_OUT_BUFFER );

            // Synchronise l'objet pDevMode.
            // Voir le SDK help sous DocumentProperties pour plus d'informations.
            ClosePrinter( hPrinter );

            GlobalUnlock( pd.hDevNames );
            GlobalUnlock( pd.hDevMode );
        }
    }

#endif // _WIN32
}

// **********************************************************************************************************
// *                              Fonctions publiques de la classe ZVDocumentPageSetup                        *
// **********************************************************************************************************

// Cette fonction permet d'obtenir la dimension de la page du document, si aucun driver n'est install�.
CSize ZVDocumentPageSetup::GetDefaultPageDim( CRect Margins )
{
    CSize PageDim;

    if ( m_Orientation == DMORIENT_PORTRAIT )
    {
        PageDim.cx = 793  - Margins.right - Margins.left;        /*210 cm*/
        PageDim.cy = 1122 - Margins.top - Margins.bottom;        /*297 cm*/
    }
    else
    {
        PageDim.cx = 1122 - Margins.top - Margins.bottom;        /*297 cm*/
        PageDim.cy = 793  - Margins.right - Margins.left;        /*210 cm*/
    }

    return PageDim;
}

/*    Cette fonction permet � l'utilisateur de d�finir un format de page. La fonction retourne TRUE si
    l'utilisateur accepte le format, ou FALSE si l'utilisateur clique sur Abandonner.*/
void ZVDocumentPageSetup::OnUserDefinePageFormat()
{
    // Ces deux conditions �vitent une r�p�tition de l'apparition de la bo�te de dialogue.
    if ( bIsFormatDefined == TRUE || bIsCancelled == TRUE ) return;

    CSize    PaperSize;
    short    StandardSize;
    short    Orientation;

    BOOL    bIsPrinterExists = GetPrinterSettings( PaperSize, StandardSize, Orientation );

    if ( !bIsPrinterExists )
    {
        CString m_MsgStr = _T( "" );
        m_MsgStr.LoadString( IDS_NO_PRINTER_BY_DEFAULT );

        AfxMessageBox( m_MsgStr, MB_ICONWARNING );

        m_PageSetupDlg.SetPaperSize            ( DefaultPaperSize );
        m_PageSetupDlg.SetStandardSize        ( DefaultStandardSize );
        m_PageSetupDlg.SetOrientation        ( DefaultOrientation );

        bCanPrint = FALSE;
    }
    else
    {
        if ( StandardSize != DMPAPER_A4 )
        {
            m_PageSetupDlg.SetPaperSize        ( PaperSize );
            m_PageSetupDlg.SetStandardSize    ( StandardSize );

            // JMR-MODIF - Le 23 f�vrier 2006 - Le test d'impression ne doit plus afficher ce message.
/*            AfxMessageBox( _T( "Votre imprimante n'est pas configur�e au m�me format que le document. Tant que la configuration par d�faut de votre imprimante ne correspondra pas au format du document, vous ne pourrez pas imprimer." ),
                           MB_ICONWARNING );
*/

            bCanPrint = FALSE;
        }
        else
        {
            m_PageSetupDlg.SetPaperSize        ( PaperSize );
            m_PageSetupDlg.SetStandardSize    ( StandardSize );

            bCanPrint = TRUE;
        }

        m_PageSetupDlg.SetOrientation        ( Orientation );
    }

    if ( m_PageSetupDlg.DoModal() == IDCANCEL )
    {
        bIsCancelled    = TRUE;
        return;
    }

    m_PaperSize            = m_PageSetupDlg.GetPaperSize();
    m_StandardSize        = m_PageSetupDlg.GetStandardSize();
    m_Orientation        = m_PageSetupDlg.GetOrientation();

    sBkGndName            = m_PageSetupDlg.GetBackGroundFilename();

    if ( bIsPrinterExists )
    {
        ChangePrinterSettings( m_StandardSize, m_Orientation );
    }

    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de mettre � jour le driver d'impression en fonction des derni�res modifications entr�es.
void ZVDocumentPageSetup::OnUpdatePrinterSettings()
{
    ChangePrinterSettings( m_StandardSize, m_Orientation );
}

// Cette fonction permet de d�finir la dimension du papier.
void ZVDocumentPageSetup::SetPaperSize( CSize PaperSize )
{
    m_PaperSize            = PaperSize;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de d�finir la taille standard du papier.
void ZVDocumentPageSetup::SetStandardSize( short StandardSize )
{
    m_StandardSize        = StandardSize;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de d�finir l'orientation du papier.
void ZVDocumentPageSetup::SetOrientation( short Orientation )
{
    m_Orientation        = Orientation;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet d'obtenir la dimension courante du papier.
CSize ZVDocumentPageSetup::GetPaperSize()
{
    return m_PaperSize;
}

// Cette fonction permet d'obtenir la taille standard du papier.
short ZVDocumentPageSetup::GetStandardSize()
{
    return m_StandardSize;
}

// Cette fonction permet d'obtenir l'orientation du papier.
short ZVDocumentPageSetup::GetOrientation()
{
    return m_Orientation;
}

// Cette fonction permet de savoir si le format de page a d�j� �t� d�fini.
BOOL ZVDocumentPageSetup::IsFormatDefined()
{
    return bIsFormatDefined;
}

// Cette fonction permet de savoir si l'utilisateur � quitt� la bo�te de dialogue sans valider.
BOOL ZVDocumentPageSetup::IsCancelled()
{
    return bIsCancelled;
}

// Cette fonction permet de savoir si le format entr� en param�tre est support� par le driver d'impression.
BOOL ZVDocumentPageSetup::IsSupported( short StandardSize )
{
    if ( bIsChecked == TRUE )
    {
        return bCanPrint;
    }

    CSize    PaperSize;
    short    StandardSizeFromPrinter;
    short    Orientation;

    BOOL    bIsPrinterExists = GetPrinterSettings( PaperSize, StandardSizeFromPrinter, Orientation );

    if ( bIsPrinterExists != TRUE )
    {
        CString m_MsgStr = _T( "" );
        m_MsgStr.LoadString( IDS_NO_PRINTER_BY_DEFAULT );

        AfxMessageBox( m_MsgStr, MB_ICONWARNING );

        bCanPrint = FALSE;
    }
    else if ( StandardSize != StandardSizeFromPrinter )
    {
        // JMR-MODIF - Le 23 f�vrier 2006 - Le test d'impression ne doit plus afficher ce message.
/*        AfxMessageBox( _T( "Votre imprimante n'est pas configur�e au m�me format que le document. Tant que la configuration par d�faut de votre imprimante ne correspondra pas au format du document, vous ne pourrez pas imprimer." ),
                       MB_ICONWARNING );
*/

        bCanPrint = FALSE;
    }
    else
    {
        bCanPrint = TRUE;
    }

    bIsChecked = TRUE;

    return bCanPrint;
}

// Cette fonction permet de savoir si le document peut �tre imprim�.
BOOL ZVDocumentPageSetup::CanPrint()
{
    return bCanPrint;
}

// Cette fonction permet d'obtenir le nom du fichier pour la trame de fond, s'il a �t� d�fini par l'utilisateur.
CString ZVDocumentPageSetup::GetBackGroundFilename()
{
    return sBkGndName;
}
