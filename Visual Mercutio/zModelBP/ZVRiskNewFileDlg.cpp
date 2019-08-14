// **************************************************************************************************************
// *                                             Classe ZVRiskNewFileDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 12 juillet 2007 - Ajout de la classe ZVRiskNewFileDlg.                                        *
// **************************************************************************************************************
// * Cette classe permet � l'utilisateur de cr�er un nouveau fichier pour les �l�ments des menus des risques.    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskNewFileDlg.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\ZDTextFile.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP( ZVRiskNewFileDlg, CDialog )
    //{{AFX_MSG_MAP(ZVRiskNewFileDlg)
    ON_BN_CLICKED(IDC_DIRECTORY_SELECT, OnBnClickedDirectorySelect)
    ON_EN_CHANGE(IDC_FILENAME, OnEnChangeFilename)
    ON_EN_CHANGE(IDC_DIRECTORY, OnEnChangeDirectory)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVRiskNewFileDlg dialog

ZVRiskNewFileDlg::ZVRiskNewFileDlg( CString Extension, CWnd* pParent /*= NULL*/ )
    : CDialog        ( ZVRiskNewFileDlg::IDD, pParent ),
      m_Extension    ( Extension ),
      m_Filename    ( _T( "" ) ),
      m_Directory    ( _T( "" ) )
{
    //{{AFX_DATA_INIT(ZVRiskNewFileDlg)
    //}}AFX_DATA_INIT
}

// Cette fonction retourne le nom du r�pertoire utilis� pour la nouvelle liste.
CString ZVRiskNewFileDlg::GetDirectory()
{
    return m_Directory;
}

// Cette fonction retourne le nom du fichier utilis� pour la nouvelle liste.
CString ZVRiskNewFileDlg::GetFilename()
{
    return m_Filename;
}

// Cette fonction contr�le les entr�es utilisateurs.
void ZVRiskNewFileDlg::CheckUserEntry()
{
    if ( ( m_Filename.IsEmpty() == FALSE ) && ( m_Directory.IsEmpty() == FALSE ) )
    {
        m_OK_Ctrl.EnableWindow( TRUE );
    }
    else
    {
        m_OK_Ctrl.EnableWindow( FALSE );
    }
}

void ZVRiskNewFileDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVRiskNewFileDlg)
    DDX_Text(pDX, IDC_FILENAME, m_Filename);
    DDX_Text(pDX, IDC_DIRECTORY, m_Directory);
    DDX_Control(pDX, IDC_FILENAME, m_Filename_Ctrl);
    DDX_Control(pDX, IDC_DIRECTORY, m_Directory_Ctrl);
    DDX_Control(pDX, IDOK, m_OK_Ctrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRiskNewFileDlg message handlers

// Cette fonction est appel�e lorsque la fen�tre s'initialise.
BOOL ZVRiskNewFileDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_Directory = PSS_Application::Instance()->GetMainForm()->GetApplicationDir() + g_RiskDirectory;
    m_Directory_Ctrl.SetWindowText(m_Directory);

    m_OK_Ctrl.EnableWindow(FALSE);

    return TRUE;
}

// Cette fonction est appel�e lorsque le nom du fichier change.
void ZVRiskNewFileDlg::OnEnChangeFilename()
{
    m_Filename_Ctrl.GetWindowText( m_Filename );

    CheckUserEntry();
}

// Cette fonction est appel�e lorsque le nom du r�pertoire change.
void ZVRiskNewFileDlg::OnEnChangeDirectory()
{
    m_Directory_Ctrl.GetWindowText( m_Directory );

    CheckUserEntry();
}

// Cette fonction est appel�e lorsque l'utilisateur clique sur le bouton "Changer".
void ZVRiskNewFileDlg::OnBnClickedDirectorySelect()
{
    CSHFileInfo m_FileInfo;
    m_FileInfo.m_strTitle = _T( m_Directory );

    if ( m_FileInfo.BrowseForFolder( GetParent() ) == IDOK )
    {
        m_Directory = m_FileInfo.m_strPath;
        m_Directory_Ctrl.SetWindowText( m_Directory );
    }
}

// Cette fonction est appel�e lorsque l'utilisateur clique sur le bouton "Ok".
void ZVRiskNewFileDlg::OnBnClickedOk()
{
    PSS_File m_File;

    if ( !m_File.Exist( m_Directory ) )
    {
        MsgBox m_Box;

        m_Box.DisplayMsgBox( IDS_BAD_DIRECTORY, MB_OK );

        return;
    }

    if ( m_File.Exist( m_Directory + _T( "\\" ) + m_Filename + m_Extension ) )
    {
        MsgBox m_Box;

        m_Box.DisplayMsgBox( IDS_RISK_FILE_ALREADY_EXIST, MB_OK );

        return;
    }

    OnOK();
}
