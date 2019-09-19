// ******************************************************************************************************
// *                                    Classe ZVPublishProcessReport                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 1er mars 2006 - Cr�ation de la nouvelle classe ZVPublishProcessReport.                *
// ******************************************************************************************************
// * Cette classe effectue la publication du rapport processus en tant que pages Internet.                *
// ******************************************************************************************************

#include "stdafx.h"
#include "ZVPublishProcessReport.h"

#include "zConversion\PSS_StringTools.h"
#include "zBaseLib\ZUStringFormater.h"

#include "zReportWebRes.h"
#include "zRMdlBP.h"

// ******************************************************************************************************
// *                              Fonctions utilis�es par les classes internes                            *
// ******************************************************************************************************

_ZVSymbolEntity::_ZVSymbolEntity()
{
}

_ZVSymbolEntity::_ZVSymbolEntity( int        Ref,
                                  CString    Name,
                                  CString    Description )
{
    nRef            = Ref;
    m_Name            = Name;
    m_Description    = Description;
}

_ZVSymbolEntity::~_ZVSymbolEntity()
{
}

void _ZVSymbolEntity::SetRef( int Ref )
{
    nRef = Ref;
}

int _ZVSymbolEntity::GetRef()
{
    return nRef;
}

void _ZVSymbolEntity::SetName( CString Name )
{
    m_Name = Name;
}

CString _ZVSymbolEntity::GetName()
{
    return m_Name;
}

void _ZVSymbolEntity::SetDescription( CString Description )
{
    m_Description = Description;
}

CString _ZVSymbolEntity::GetDescription()
{
    return m_Description;
}

// Constructeur par d�faut de la classe _ZVSymbolContainer.
_ZVSymbolContainer::_ZVSymbolContainer()
{
    m_Pos = NULL;
}

// Destructeur de la classe _ZVSymbolContainer.
_ZVSymbolContainer::~_ZVSymbolContainer()
{
}

// JMR-MODIF - Le 13 juin 2006 - Cette fonction permet de vider les caract�res vides redondants dans la cha�ne.
CString _ZVSymbolContainer::WashString( CString EntryString )
{
    CString    s_TmpStr            = _T( "" );
    int        i                    = 0;
    BOOL    FirstCharIsNotEmpty    = FALSE;
    BOOL    DoTestNextChar        = FALSE;

    while ( i < EntryString.GetLength() )
    {
        // Efface tous les caract�res vides avant la premi�re occurence de texte.
        if ( FirstCharIsNotEmpty == FALSE )
        {
            if ( EntryString.GetAt( i ) != _T( ' ' ) )
            {
                s_TmpStr += EntryString.GetAt( i );
                FirstCharIsNotEmpty = TRUE;
            }
        }
        else
        {
            // Si un caract�re vide est rencontr�, teste si le suivant est vide aussi.
            // Si c'est le cas, supprime ce caract�re de la cha�ne finale.
            if ( DoTestNextChar == FALSE )
            {
                s_TmpStr += EntryString.GetAt( i );

                if ( EntryString.GetAt( i ) == _T( ' ' ) )
                {
                    DoTestNextChar = TRUE;
                }
            }
            else
            {
                if ( EntryString.GetAt( i ) != _T( ' ' ) )
                {
                    s_TmpStr += EntryString.GetAt( i );
                    DoTestNextChar = FALSE;
                }
            }
        }

        i++;
    }

    return s_TmpStr;
}

// Cette fonction permet de trier les num�ros de r�f�rence d'une liste par ordre croissant.
void _ZVSymbolContainer::Sort()
{
    POSITION CurPos        = GetHeadPosition();
    POSITION NextPos    = CurPos;

    while ( CurPos != NULL )
    {
        m_SymbolList.GetNext( NextPos );

        _ZVSymbolEntity* m_TmpCurSymbol = dynamic_cast<_ZVSymbolEntity*>( m_SymbolList.GetAt( CurPos ) );
        _ZVSymbolEntity* m_TmpNxtSymbol = NULL;

        // Le symbole suivant directement le symbole courant existe.
        if ( NextPos != NULL )
        {
            m_TmpNxtSymbol = dynamic_cast<_ZVSymbolEntity*>( m_SymbolList.GetAt( NextPos ) );
        }

        // On v�rifie que les deux symboles � comparer soient valides.
        if ( m_TmpCurSymbol != NULL && m_TmpNxtSymbol != NULL )
        {
            // Si le num�ro de r�f�rence du sumbole courant est plus grand que le num�ro de r�f�rence du
            // symbole suivant, on �change les symboles.
            // JMR-MODIF - Le 6 juin 2006 - Tri par ordre alphab�tique plut�t que par num�ro de symboles.
            // Au besoin, pour revenir � un tri par num�ro, �changer les commentaires des deux lignes ci-dessous.
//            if ( m_TmpCurSymbol->GetRef() > m_TmpNxtSymbol->GetRef() )
            if ( WashString( m_TmpCurSymbol->GetName() ).Collate( WashString( m_TmpNxtSymbol->GetName() ) ) > 0 )
            {
                m_SymbolList.SetAt( CurPos,  m_TmpNxtSymbol );
                m_SymbolList.SetAt( NextPos, m_TmpCurSymbol );

                // On recommence l'algorythme jusqu'� ce que tous les r�sultats soient
                // class�s comme d�sir�. (Fonction r�cursive)
                Sort();
                return;
            }
        }

        CurPos = NextPos;
    }
}

// Cette fonction permet de lib�rer la ressource m�moire utilis�e par cet objet.
void _ZVSymbolContainer::RemoveAll()
{
    POSITION Pos = GetHeadPosition();

    while ( Pos != NULL )
    {
        _ZVSymbolEntity* m_TmpSymbol = dynamic_cast<_ZVSymbolEntity*>( m_SymbolList.GetAt( Pos ) );

        if ( m_TmpSymbol != NULL )
        {
            delete m_TmpSymbol;
            m_TmpSymbol = NULL;
        }

        GetNextPosition();

        m_SymbolList.RemoveAt( Pos );

        Pos = m_Pos;
    }
}

// Cette fonction permet d'ajouter un nouveau symbole dans la liste.
void _ZVSymbolContainer::AddSymbol( _ZVSymbolEntity* SymbolEntity )
{
    m_Pos = m_SymbolList.AddTail( SymbolEntity );
}

// Cette fonction permet d'obtenir un symbole en fonction de sa position.
_ZVSymbolEntity* _ZVSymbolContainer::GetAt( POSITION Pos )
{
    if ( Pos != NULL )
    {
        return dynamic_cast<_ZVSymbolEntity*>( m_SymbolList.GetAt( Pos ) );
    }

    return NULL;
}

// Cette fonction permet d'obtenir la position du premier symbole de la liste.
POSITION _ZVSymbolContainer::GetHeadPosition()
{
    m_Pos = m_SymbolList.GetHeadPosition();

    return m_Pos;
}

// Cette fonction permet d'obtenir la position du dernier symbole de la liste.
POSITION _ZVSymbolContainer::GetTailPosition()
{
    m_Pos = m_SymbolList.GetTailPosition();

    return m_Pos;
}

// Cette fonction permet d'obtenir la position du symbole pr�c�dant le symbole courant. NULL si inexistant.
POSITION _ZVSymbolContainer::GetPrevPosition()
{
    if ( m_Pos != NULL )
    {
        m_SymbolList.GetPrev( m_Pos );
    }

    return m_Pos;
}

// Cette fonction permet d'obtenir la position du symbole suivant le symbole courant. NULL si inexistant.
POSITION _ZVSymbolContainer::GetNextPosition()
{
    if ( m_Pos != NULL )
    {
        m_SymbolList.GetNext( m_Pos );
    }

    return m_Pos;
}

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur de la classe ZVPublishProcessReport.
ZVPublishProcessReport::ZVPublishProcessReport( ZDProcessGraphModelMdlBP*    pModel            /*= NULL*/,
                                                ZBPropertyAttributes*        pPropAttributes    /*= NULL*/ )
{
    m_pRootModel            = pModel;
    m_pPropAttributes        = pPropAttributes;
}

// Destructeur de la classe ZVPublishProcessReport.
ZVPublishProcessReport::~ZVPublishProcessReport()
{
    ResetDatas();
}

// ******************************************************************************************************
// *                         Fonctions publiques de la classe ZVPublishProcessReport                    *
// ******************************************************************************************************

// Cette fonction permet de publier le rapport dans le r�pertoire fourni en entr�e.
bool ZVPublishProcessReport::Publish( CString Directory )
{
    // if no doc nor model defined. nothing to do.
    if ( !m_pRootModel )
    {
        return false;
    }

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    if ( !CreateFileSystem( Directory ) )
    {
        // Hide the feedback dialog
        m_FileGenerateWindow.ShowWindow( SW_HIDE );

        return false;
    }

    // Hide the feedback dialog
    m_FileGenerateWindow.ShowWindow( SW_HIDE );

    return true;
}

// ******************************************************************************************************
// *                        Fonctions priv�es de la classe ZVPublishProcessReport                        *
// ******************************************************************************************************

// Cette fomction permet de r�initialiser toutes les donn�es du publicateur, avant une nouvelle publication.
void ZVPublishProcessReport::ResetDatas()
{
    m_StartContainer.RemoveAll();
    m_StopContainer.RemoveAll();
    m_ProcedureContainer.RemoveAll();

    // JMR-MODIF - Le 31 mai 2006 - Ajout du code de nettoyage pour le conteneur des portes.
    m_DoorContainer.RemoveAll();
}

// Cette fonction retrouve l'original d'un symbole � travers tout le syst�me de mod�les.
ZBSymbol* ZVPublishProcessReport::FindSymbol( const CString SymbolName,
                                              ZDProcessGraphModelMdlBP* m_StartRootModel /* = NULL */ )
{
    // Si le nom est vide, retourne 0.
    if ( SymbolName.IsEmpty() )
    {
        return NULL;
    }

    // Si le mod�le d'entr�e est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if ( m_StartRootModel == NULL )
    {
        // Obtient le contr�leur de mod�les du document.
        m_StartRootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pRootModel );
    }

    if ( m_StartRootModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        ZBProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contr�leur de mod�le de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel =
                    dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une proc�dure.
                            if ( pComponent && ISA( pComponent, ZBBPProcedureSymbol ) )
                            {
                                ZBBPProcedureSymbol* m_Procedure = dynamic_cast<ZBBPProcedureSymbol*>( pComponent );

                                if ( m_Procedure != NULL )
                                {
                                    if ( m_Procedure->GetSymbolName() == SymbolName && m_Procedure->IsLocal() )
                                    {
                                        return m_Procedure;
                                    }
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point start.
                            if ( pComponent && ISA( pComponent, ZBBPStartSymbol ) )
                            {
                                ZBBPStartSymbol* m_Start = dynamic_cast<ZBBPStartSymbol*>( pComponent );

                                if ( m_Start != NULL )
                                {
                                    if ( m_Start->GetSymbolName() == SymbolName && m_Start->IsLocal() )
                                    {
                                        return m_Start;
                                    }
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point stop.
                            if ( pComponent && ISA( pComponent, ZBBPStopSymbol ) )
                            {
                                ZBBPStopSymbol* m_Stop = dynamic_cast<ZBBPStopSymbol*>( pComponent );

                                if ( m_Stop != NULL && m_Stop->IsLocal() )
                                {
                                    if ( m_Stop->GetSymbolName() == SymbolName )
                                    {
                                        return m_Stop;
                                    }
                                }
                            }

                            // JMR-MODIF - Le 31 mai 2006 - Ajout du code d'identification des portes.
                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une porte.
                            if ( pComponent && ISA( pComponent, ZBBPDoorSymbol ) )
                            {
                                ZBBPDoorSymbol* m_Door = dynamic_cast<ZBBPDoorSymbol*>( pComponent );

                                if ( m_Door != NULL && m_Door->IsLocal() )
                                {
                                    if ( m_Door->GetSymbolName() == SymbolName )
                                    {
                                        return m_Door;
                                    }
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if ( pComponent && ISA( pComponent, ZBBPProcessSymbol ) )
                            {
                                ZBSymbol* Result = NULL;

                                // Convertit le symbole.
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>( pComponent );

                                // Obtient le contr�leur de mod�le du processus.
                                ZDProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<ZDProcessGraphModelMdlBP*>( m_Process->GetpModel() );

                                // Appel r�cursif � FindSymbol, jusqu'� ce que toutes les pages des processus
                                // enfants aient �t� visit�es, ou que le symbole original ait �t� trouv�.
                                Result = FindSymbol( SymbolName, m_ChildModel );

                                // L'original n'est peut-�tre pas dans cet ensemble de pages si le r�sultat
                                // vaut NULL. Alors, il faut continuer � chercher.
                                if ( Result != NULL )
                                {
                                    return Result;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return NULL;
}

// Cette fonction retrouve l'original d'un symbole de lien � travers tout le syst�me de mod�les.
ZBLinkSymbol* ZVPublishProcessReport::FindLinkSymbol( const CString SymbolName,
                                                      ZDProcessGraphModelMdlBP* m_StartRootModel /* = NULL */ )
{
    // Si le nom est vide, retourne 0.
    if ( SymbolName.IsEmpty() )
    {
        return NULL;
    }

    // Si le mod�le d'entr�e est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if ( m_StartRootModel == NULL )
    {
        // Obtient le contr�leur de mod�les du document.
        m_StartRootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pRootModel );
    }

    if ( m_StartRootModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        ZBProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contr�leur de mod�le de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un livrable.
                            if ( pComponent && ISA( pComponent, ZBDeliverableLinkSymbol ) )
                            {
                                ZBDeliverableLinkSymbol* m_Deliverable =
                                    dynamic_cast<ZBDeliverableLinkSymbol*>( pComponent );

                                if ( m_Deliverable != NULL && m_Deliverable->IsLocal() )
                                {
                                    if ( m_Deliverable->GetSymbolName() == SymbolName )
                                    {
                                        return m_Deliverable;
                                    }
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if ( pComponent && ISA( pComponent, ZBBPProcessSymbol ) )
                            {
                                ZBLinkSymbol* Result = NULL;

                                // Convertit le symbole.
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>( pComponent );

                                // Obtient le contr�leur de mod�le du processus.
                                ZDProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<ZDProcessGraphModelMdlBP*>( m_Process->GetpModel() );

                                // Appel r�cursif � FindSymbol, jusqu'� ce que toutes les pages des processus
                                // enfants aient �t� visit�es, ou que le symbole original ait �t� trouv�.
                                Result = FindLinkSymbol( SymbolName, m_ChildModel );

                                // L'original n'est peut-�tre pas dans cet ensemble de pages si le r�sultat
                                // vaut NULL. Alors, il faut continuer � chercher.
                                if ( Result != NULL )
                                {
                                    return Result;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return NULL;
}

// Cette fonction permet de cr�er le syst�me de fichiers.
bool ZVPublishProcessReport::CreateFileSystem( CString Directory,
                                               ZDProcessGraphModelMdlBP* m_StartRootModel /* = NULL */ )
{
    // Si le mod�le d'entr�e est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if ( m_StartRootModel == NULL )
    {
        // Obtient le contr�leur de mod�les du document.
        m_StartRootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pRootModel );
    }

    if ( m_StartRootModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        ZBProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contr�leur de mod�le de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if ( pComponent && ISA( pComponent, ZBBPProcessSymbol ) )
                            {
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>( pComponent );

                                if ( m_Process != NULL )
                                {
                                    ZDProcessGraphModelMdlBP* m_ChildModel =
                                        dynamic_cast<ZDProcessGraphModelMdlBP*>( m_Process->GetpModel() );

                                    if ( m_ChildModel != NULL )
                                    {
                                        CreateFileSystem( Directory, m_ChildModel );
                                    }

                                    ResetDatas();

                                    CString ProcessName    = m_Process->GetSymbolName();
                                    CString DomainName    = _T( "" );

                                    if ( !HtmlFile.Create( GenerateFilename( Directory, ProcessName ) ) )
                                    {
                                        return false;
                                    }

                                    m_FileGenerateWindow.SetDestination( GenerateFilename( Directory,
                                                                                           ProcessName ) );

                                    m_FileGenerateWindow.UpdateWindow();

                                    GenerateHTMLPageHead( ProcessName );

                                    ZDProcessGraphModelMdl* m_pOwnerModel =
                                        (ZDProcessGraphModelMdl*)m_Process->GetOwnerModel();

                                    ZDProcessGraphPage* pPage = m_pRootModel->FindModelPage( m_pOwnerModel, true );

                                    if ( pPage )
                                    {
                                        DomainName = pPage->GetPageName();
                                    }
                                    else
                                    {
                                        DomainName.LoadString( IDS_REPORTWEB_NOTFOUND );
                                    }

                                    // JMR-MODIF - Le 18 avril 2007 - Suppression du 3�me param�tre.
                                    GenerateHTMLReportTitle( DomainName,
                                                             ProcessName );

                                    GenerateHTMLTableHead();

                                    CreateReport( m_Process );

                                    GenerateHTMLPageFoot();

                                    HtmlFile.CloseFile();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

// Cette fonction permet la g�n�ration du rapport.
void ZVPublishProcessReport::CreateReport( ZBBPProcessSymbol* m_pProcessSymbol )
{
    CString Output = _T( "" );

    ZDProcessGraphModelMdlBP* m_ChildModel = NULL;

    if ( m_pProcessSymbol != NULL )
    {
        ZBPropertySet PropSet;
        m_pProcessSymbol->FillProperties( PropSet );

        GenerateSection( PropSet );

        ZBPropertyIterator i( &PropSet );
        ZBProperty* pProp = NULL;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp != NULL )
            {
                delete pProp;
            }
        }

        m_ChildModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pProcessSymbol->GetpModel() );
    }

    GenerateHTMLTableFoot();

    if ( m_ChildModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        ZBProcessGraphPageSet* pSet = m_ChildModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contr�leur de mod�le de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une proc�dure.
                            if ( pComponent && ISA( pComponent, ZBBPProcedureSymbol ) )
                            {
                                ZBBPProcedureSymbol* m_Procedure = dynamic_cast<ZBBPProcedureSymbol*>( pComponent );

                                if ( m_Procedure != NULL )
                                {
                                    _ZVSymbolEntity* m_SymEntity =
                                        new _ZVSymbolEntity( m_Procedure->GetSymbolReferenceNumber(),
                                                             m_Procedure->GetSymbolName(),
                                                             m_Procedure->GetSymbolComment() );

                                    m_ProcedureContainer.AddSymbol( m_SymEntity );
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point start.
                            if ( pComponent && ISA( pComponent, ZBBPStartSymbol ) )
                            {
                                ZBBPStartSymbol* m_Start = dynamic_cast<ZBBPStartSymbol*>( pComponent );

                                if ( m_Start != NULL )
                                {
                                    _ZVSymbolEntity* m_SymEntity =
                                        new _ZVSymbolEntity( m_Start->GetSymbolReferenceNumber(),
                                                             m_Start->GetSymbolName(),
                                                             m_Start->GetSymbolComment() );

                                    m_StartContainer.AddSymbol( m_SymEntity );
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point stop.
                            if ( pComponent && ISA( pComponent, ZBBPStopSymbol ) )
                            {
                                ZBBPStopSymbol* m_Stop = dynamic_cast<ZBBPStopSymbol*>( pComponent );

                                if ( m_Stop != NULL )
                                {
                                    _ZVSymbolEntity* m_SymEntity =
                                        new _ZVSymbolEntity( m_Stop->GetSymbolReferenceNumber(),
                                                             m_Stop->GetSymbolName(),
                                                             m_Stop->GetSymbolComment() );

                                    m_StopContainer.AddSymbol( m_SymEntity );
                                }
                            }

                            // JMR-MODIF - Le 31 mai 2006 - Ajout du code pour la gestion des portes.
                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une porte.
                            if ( pComponent && ISA( pComponent, ZBBPDoorSymbol ) )
                            {
                                ZBBPDoorSymbol* m_Door = dynamic_cast<ZBBPDoorSymbol*>( pComponent );

                                if ( m_Door != NULL )
                                {
                                    _ZVSymbolEntity* m_SymEntity =
                                        new _ZVSymbolEntity( m_Door->GetSymbolReferenceNumber(),
                                                             m_Door->GetSymbolName(),
                                                             m_Door->GetSymbolComment() );

                                    m_DoorContainer.AddSymbol( m_SymEntity );
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    m_StartContainer.Sort();
    m_StopContainer.Sort();
    m_ProcedureContainer.Sort();

    // JMR-MODIF - Le 31 mai 2006 - Ordonne le tri des portes par ordre alphab�tique.
    m_DoorContainer.Sort();

    POSITION myPos = m_StartContainer.GetHeadPosition();

    if ( myPos != NULL )
    {
        // Cr�e la ligne de s�paration pour les paragraphes.
        GenerateSeparation();
        GenerateBlackLine();
    }

    while ( myPos != NULL )
    {
        _ZVSymbolEntity* myCurNode = m_StartContainer.GetAt( myPos );

        CString ObjType = _T( "" );
        ObjType.LoadString( IDS_OBJECTTYPE_START );

        GenerateHTMLSymbolTitle( myCurNode->GetRef(),
                                 myCurNode->GetName(),
                                 ObjType,
                                 RGB( 0, 255, 0 ) );

        ZBBPStartSymbol* m_StartSymbol = NULL;

        if ( FindSymbol( myCurNode->GetName() ) != NULL &&
             ISA ( FindSymbol( myCurNode->GetName() ), ZBBPStartSymbol ) )
        {
            m_StartSymbol = dynamic_cast<ZBBPStartSymbol*>( FindSymbol( myCurNode->GetName() ) );
        }

        if ( m_StartSymbol != NULL )
        {
            ZBPropertySet PropSet;
            m_StartSymbol->FillProperties( PropSet );

            GenerateSection( PropSet );

            ZBPropertyIterator i( &PropSet );
            ZBProperty* pProp = NULL;

            for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                if ( pProp != NULL )
                {
                    delete pProp;
                }
            }
        }

        GenerateHTMLTableFoot();

        // *********************************************************************************************************
        // JMR-MODIF - Le 29 mai 2006 - Ajout du code pour l'affichage des livrables li�s aux points start.
        if ( m_StartSymbol != NULL )
        {
            _ZVSymbolContainer m_DeliverableContainer;

            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            // Retrouve tous les livrables en sortie.
            CODEdgeArray Edges;

            if ( m_StartSymbol->GetEdgesLeaving( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                 m_LinkSymbol->GetSymbolName(),
                                                 ObjType,
                                                 RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }
        // *********************************************************************************************************

        myPos = m_StartContainer.GetNextPosition();
    }

    // *************************************************************************************************************
    // JMR-MODIF - Le 31 mai 2006 - Ajout des portes en entr�e dans le rapport.
    myPos = m_DoorContainer.GetHeadPosition();

    if ( myPos != NULL )
    {
        // Cr�e la ligne de s�paration pour les paragraphes.
        GenerateBlackLine();
    }

    while ( myPos != NULL )
    {
        _ZVSymbolEntity* myCurNode = m_DoorContainer.GetAt( myPos );

        ZBBPDoorSymbol* m_DoorSymbol = NULL;

        if ( FindSymbol( myCurNode->GetName() ) != NULL &&
             ISA ( FindSymbol( myCurNode->GetName() ), ZBBPDoorSymbol ) )
        {
            m_DoorSymbol = dynamic_cast<ZBBPDoorSymbol*>( FindSymbol( myCurNode->GetName() ) );
        }

        if ( m_DoorSymbol != NULL )
        {
            // Inscrit le symbole porte dans le rapport uniquement si un livrable lui est attribu�.
            CODEdgeArray Edges;

            // Retrouve les livrables en sortie.
            if ( m_DoorSymbol->GetEdgesLeaving( Edges ) > 0 )
            {
                CString ObjType = _T( "" );
                ObjType.LoadString( IDS_OBJECTTYPE_DOOR );

                GenerateHTMLSymbolTitle( myCurNode->GetRef(),
                                         myCurNode->GetName(),
                                         ObjType,
                                         RGB( 155, 255, 155 ) );

                ZBPropertySet PropSet;
                m_DoorSymbol->FillProperties( PropSet );

                GenerateSection( PropSet );

                ZBPropertyIterator i( &PropSet );
                ZBProperty* pProp = NULL;

                for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                {
                    if ( pProp != NULL )
                    {
                        delete pProp;
                    }
                }

                GenerateHTMLTableFoot();

                // JMR-MODIF - Le 16 avril 2007 - Le titre de section ne doit appara�tre que si un livrable existe.
                if ( Edges.GetSize() > 0 )
                {
                    // Cr�e la ligne de s�paration pour les paragraphes.
                    GenerateSeparation();
                    GenerateHTMLTableHead();

                    Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
                    GenerateHTMLSectionTitle( Output );

                    GenerateHTMLTableFoot();
                }

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Check if null and continue if the case
                    if ( !pComp )
                    {
                        continue;
                    }

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( pComp->GetSymbolName() ) != NULL &&
                         ISA ( FindLinkSymbol( pComp->GetSymbolName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol = dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( pComp->GetSymbolName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                 m_LinkSymbol->GetSymbolName(),
                                                 ObjType,
                                                 RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }
                }

                GenerateSeparation();
            }
        }

        myPos = m_DoorContainer.GetNextPosition();
    }
    // *************************************************************************************************************

    myPos = m_ProcedureContainer.GetHeadPosition();

    while ( myPos != NULL )
    {
        // Cr�e la ligne de s�paration pour les paragraphes.
        GenerateBlackLine();

        _ZVSymbolEntity* myCurNode = m_ProcedureContainer.GetAt( myPos );

        CString ObjType = _T( "" );
        ObjType.LoadString( IDS_OBJECTTYPE_PROCEDURE );

        GenerateHTMLSymbolTitle( myCurNode->GetRef(),
                                 myCurNode->GetName(),
                                 ObjType,
                                 RGB( 192, 192, 192 ) );

        ZBBPProcedureSymbol* m_ProcedureSymbol = NULL;

        if ( FindSymbol( myCurNode->GetName() ) != NULL &&
             ISA ( FindSymbol( myCurNode->GetName() ), ZBBPProcedureSymbol ) )
        {
            m_ProcedureSymbol = dynamic_cast<ZBBPProcedureSymbol*>( FindSymbol( myCurNode->GetName() ) );
        }

        if ( m_ProcedureSymbol != NULL )
        {
            ZBPropertySet PropSet;
            m_ProcedureSymbol->FillProperties( PropSet );

            GenerateSection( PropSet );

            ZBPropertyIterator i( &PropSet );
            ZBProperty* pProp = NULL;

            for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                if ( pProp != NULL )
                {
                    delete pProp;
                }
            }
        }

        GenerateHTMLTableFoot();

        if ( m_ProcedureSymbol != NULL )
        {
            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            CODEdgeArray        Edges;
            _ZVSymbolContainer    m_DeliverableContainer;

            // Retrouve tous les livrables en entr�e en haut du symbole.
            if ( m_ProcedureSymbol->GetEnteringUpDeliverable( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_2 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            // Retrouve tous les livrables en sortie � droite du symbole.
            if ( m_ProcedureSymbol->GetEdgesLeaving_Right( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_2 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            // Retrouve tous les livrables en sortie � gauche du symbole.
            if ( m_ProcedureSymbol->GetEdgesLeaving_Left( Edges ) > 0 )
            {
                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_3 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            // Retrouve tous les livrables en entr�e � droite du symbole.
            if ( m_ProcedureSymbol->GetEdgesEntering_Right( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_3 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            // Retrouve tous les livrables en entr�e � gauche du symbole.
            if ( m_ProcedureSymbol->GetEdgesEntering_Left( Edges ) > 0 )
            {
                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            // Retrouve tous les livrables en sortie en bas du symbole.
            if ( m_ProcedureSymbol->GetEdgesLeaving_Down( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }

        myPos = m_ProcedureContainer.GetNextPosition();
    }

    // *************************************************************************************************************
    // JMR-MODIF - Le 31 mai 2006 - Ajout des portes en sortie dans le rapport.
    myPos = m_DoorContainer.GetHeadPosition();

    if ( myPos != NULL )
    {
        // Cr�e la ligne de s�paration pour les paragraphes.
        GenerateBlackLine();
    }

    while ( myPos != NULL )
    {
        _ZVSymbolEntity* myCurNode = m_DoorContainer.GetAt( myPos );

        ZBBPDoorSymbol* m_DoorSymbol = NULL;

        if ( FindSymbol( myCurNode->GetName() ) != NULL &&
             ISA ( FindSymbol( myCurNode->GetName() ), ZBBPDoorSymbol ) )
        {
            m_DoorSymbol = dynamic_cast<ZBBPDoorSymbol*>( FindSymbol( myCurNode->GetName() ) );
        }

        if ( m_DoorSymbol != NULL )
        {
            // Inscrit le symbole porte dans le rapport uniquement si un livrable lui est attribu�.
            CODEdgeArray Edges;

            // Retrouve les livrables en sortie.
            if ( m_DoorSymbol->GetEdgesEntering( Edges ) > 0 )
            {
                CString ObjType = _T( "" );
                ObjType.LoadString( IDS_OBJECTTYPE_DOOR );

                GenerateHTMLSymbolTitle( myCurNode->GetRef(),
                                         myCurNode->GetName(),
                                         ObjType,
                                         RGB( 255, 155, 155 ) );

                ZBPropertySet PropSet;
                m_DoorSymbol->FillProperties( PropSet );

                GenerateSection( PropSet );

                ZBPropertyIterator i( &PropSet );
                ZBProperty* pProp = NULL;

                for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                {
                    if ( pProp != NULL )
                    {
                        delete pProp;
                    }
                }

                GenerateHTMLTableFoot();

                // JMR-MODIF - Le 16 avril 2007 - Le titre de section ne doit appara�tre que si un livrable existe.
                if ( Edges.GetSize() > 0 )
                {
                    // Cr�e la ligne de s�paration pour les paragraphes.
                    GenerateSeparation();
                    GenerateHTMLTableHead();

                    Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4 );
                    GenerateHTMLSectionTitle( Output );

                    GenerateHTMLTableFoot();
                }

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Check if null and continue if the case
                    if ( !pComp )
                    {
                        continue;
                    }

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( pComp->GetSymbolName() ) != NULL &&
                         ISA ( FindLinkSymbol( pComp->GetSymbolName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol = dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( pComp->GetSymbolName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                 m_LinkSymbol->GetSymbolName(),
                                                 ObjType,
                                                 RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }
                }

                GenerateSeparation();
            }
        }

        myPos = m_DoorContainer.GetNextPosition();
    }
    // *************************************************************************************************************

    myPos = m_StopContainer.GetHeadPosition();

    if ( myPos != NULL )
    {
        // Cr�e la ligne de s�paration pour les paragraphes.
        GenerateBlackLine();
    }

    while ( myPos != NULL )
    {
        _ZVSymbolEntity* myCurNode = m_StopContainer.GetAt( myPos );

        CString ObjType = _T( "" );
        ObjType.LoadString( IDS_OBJECTTYPE_STOP );

        GenerateHTMLSymbolTitle( myCurNode->GetRef(),
                                 myCurNode->GetName(),
                                 ObjType,
                                 RGB( 255, 0, 0 ) );

        ZBBPStopSymbol* m_StopSymbol = NULL;

        if ( FindSymbol( myCurNode->GetName() ) != NULL &&
             ISA ( FindSymbol( myCurNode->GetName() ), ZBBPStopSymbol ) )
        {
            m_StopSymbol = dynamic_cast<ZBBPStopSymbol*>( FindSymbol( myCurNode->GetName() ) );
        }

        if ( m_StopSymbol != NULL )
        {
            ZBPropertySet PropSet;
            m_StopSymbol->FillProperties( PropSet );

            GenerateSection( PropSet );

            ZBPropertyIterator i( &PropSet );
            ZBProperty* pProp = NULL;

            for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                if ( pProp != NULL )
                {
                    delete pProp;
                }
            }
        }

        GenerateHTMLTableFoot();

        // *********************************************************************************************************
        // JMR-MODIF - Le 29 mai 2006 - Ajout du code pour l'affichage des livrables li�s aux points stop.
        if ( m_StopSymbol != NULL )
        {
            // ************************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
            // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

            /*
            // Cr�e la ligne de s�paration pour les paragraphes.
            GenerateSeparation();
            GenerateHTMLTableHead();

            Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1 );
            GenerateHTMLSectionTitle( Output );

            GenerateHTMLTableFoot();
            */
            // ************************************************************************************************************

            CODEdgeArray        Edges;
            _ZVSymbolContainer    m_DeliverableContainer;

            // Retrouve tous les livrables en entr�e en haut du symbole.
            if ( m_StopSymbol->GetEdgesEntering( Edges ) > 0 )
            {
                // ************************************************************************************************
                // JMR-MODIF - Le 16 avril 2007 - Teste s'il existe au moins un livrable avant d'afficher le titre.

                // Cr�e la ligne de s�paration pour les paragraphes.
                GenerateSeparation();
                GenerateHTMLTableHead();

                Output.LoadString( IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1 );
                GenerateHTMLSectionTitle( Output );

                GenerateHTMLTableFoot();
                // ************************************************************************************************

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
                    ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Teste si le pointeur est vide, et passe � l'it�ration suivante si c'est le cas.
                    if ( !pComp )
                    {
                        continue;
                    }

                    _ZVSymbolEntity* m_DeliverableEntity =
                        new _ZVSymbolEntity( 0, pComp->GetSymbolName(), _T( "" ) );

                    m_DeliverableContainer.AddSymbol( m_DeliverableEntity );
                }

                m_DeliverableContainer.Sort();

                POSITION myDelivPos = m_DeliverableContainer.GetHeadPosition();

                while ( myDelivPos != NULL )
                {
                    _ZVSymbolEntity* myDelivCurNode = m_DeliverableContainer.GetAt( myDelivPos );

                    ZBDeliverableLinkSymbol* m_LinkSymbol = NULL;

                    if ( FindLinkSymbol( myDelivCurNode->GetName() ) != NULL &&
                            ISA ( FindLinkSymbol( myDelivCurNode->GetName() ), ZBDeliverableLinkSymbol ) )
                    {
                        m_LinkSymbol =
                            dynamic_cast<ZBDeliverableLinkSymbol*>( FindLinkSymbol( myDelivCurNode->GetName() ) );
                    }

                    if ( m_LinkSymbol != NULL )
                    {
                        CString ObjType = _T( "" );
                        ObjType.LoadString( IDS_OBJECTTYPE_DELIVERABLE );

                        GenerateHTMLSymbolTitle( m_LinkSymbol->GetSymbolReferenceNumber(),
                                                    m_LinkSymbol->GetSymbolName(),
                                                    ObjType,
                                                    RGB( 162, 221, 198 ) );

                        ZBPropertySet PropSet;
                        m_LinkSymbol->FillProperties( PropSet );

                        GenerateSection( PropSet );

                        ZBPropertyIterator i( &PropSet );
                        ZBProperty* pProp = NULL;

                        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                        {
                            if ( pProp != NULL )
                            {
                                delete pProp;
                            }
                        }

                        GenerateHTMLTableFoot();
                    }

                    myDelivPos = m_DeliverableContainer.GetNextPosition();
                }

                m_DeliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }
        // *********************************************************************************************************

        myPos = m_StopContainer.GetNextPosition();
    }
}

// Cette fonction permet de cr�er le nom de fichier correct pour chaque page du rapport.
CString ZVPublishProcessReport::GenerateFilename( CString Directory, CString ProcessName )
{
    CString sFilename     = Directory;
    sFilename            += _T( "ProcessReport_" );
    sFilename            += PSS_StringTools::ConvertSpecialChar( ProcessName );
    sFilename            += _T( ".htm" );

    return sFilename;
}

// Cette fonction permet la g�n�ration d'une section contenant toutes les propri�t�s d'un symbole.
void ZVPublishProcessReport::GenerateSection( ZBPropertySet& PropSet )
{
    ZBPropertyIterator    i( &PropSet );
    ZBProperty*            pProp;
    int                    nCatID            = -1;
    CString                s                = _T( "" );

    // JMR-MODIF - Le 10 ao�t 2007 - Ajout des variables pour le traitement des risques.
    int                    nRiskID            = -1;
    BOOL                DoPublishRisk    = FALSE;
    BOOL                RiskIsValid        = FALSE;
    CStringArray        m_RiskContainer;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        CString Value = _T( "" );

        // Check if we want filter property attributes to display
        if ( m_pPropAttributes )
        {
            // Check if he is defined
            if ( !m_pPropAttributes->FindAttribute( pProp->GetCategoryID(), pProp->GetItemID() ) )
            {
                continue;
            }
        }

        // *************************************************************************************************************
        // JMR-MODIF - Le 16 avril 2007 - Les lignes de code ci-dessous g�n�rent des titres vides si elles sont plac�es
        // � cet endroit du code. Elles ont �t� d�plac�es plus bas, apr�s le test de valeur de la propri�t�.

        /*
        // Si la cat�gorie est nouvelle, on cr�e une nouvelle section.
        if ( pProp->GetCategoryID() != nCatID )
        {
            GenerateHTMLSectionTitle( pProp->GetCategory() );
            nCatID = pProp->GetCategoryID();
        }
        */
        // *************************************************************************************************************

        // Retrouve la valeur formatt�e en fonction du type de donn�e.
        switch ( pProp->GetPTValueType() )
        {
            case ZBProperty::PT_DOUBLE:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDouble(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_FLOAT:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueFloat(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DATE:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( (PSS_Date&)pProp->GetValueDate(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_TIMESPAN:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( (ZBTimeSpan&)pProp->GetValueTimeSpan(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DURATION:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( (PSS_Duration&)pProp->GetValueDuration(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_STRING:
            {
                Value = pProp->GetValueString();
                break;
            }

            default:
            {
                break;
            }
        }

        // *************************************************************************************************************
        // JMR-MODIF - Le 10 ao�t 2007 - Ajout du traitement appropri� pour la publication des risques.

        CString s_PropCatName = _T( "" );
        s_PropCatName.LoadString( IDS_ZS_BP_PROP_RISK_TITLE );

        if ( pProp->GetCategory().Find( s_PropCatName ) > -1 )
        {
            // G�n�re une nouvelle section pour les risques.
            if ( pProp->GetCategoryID() != nRiskID )
            {
                // JMR-MODIF - Le 30 septembre 2007 - Correction du bug de publication. Lorsqu'un groupe de risque est
                // rejet�, la valeur de la cat�gorie est malgr� tout ajout�e dans le conteneur. Si celui-ci n'est
                // pas nettoy� avant une nouvelle section, cette valeur reste, et fait planter le syst�me lors de la
                // publication.
                m_RiskContainer.RemoveAll();

                nRiskID = pProp->GetCategoryID();
                m_RiskContainer.Add( pProp->GetCategory() );
            }

            if ( Value != _T( "" ) )
            {
                m_RiskContainer.Add( pProp->GetLabel() );
                m_RiskContainer.Add( Value );

                CString s_PropLabelName = _T( "" );
                s_PropLabelName.LoadString( IDS_Z_RISK_SEVERITY_NAME );

                // Contr�le que la s�v�rit� ne soit pas � 0. Sinon, le risque n'est pas valide pour la publication.
                if ( pProp->GetLabel() == s_PropLabelName && Value != _T( "0" ) )
                {
                    RiskIsValid = TRUE;
                }

                s_PropLabelName.LoadString( IDS_Z_RISK_ACTION_NAME );

                // Si on a atteint la derni�re valeur du risque et si le risque est valide, alors on publie.
                if ( pProp->GetLabel() == s_PropLabelName && RiskIsValid == TRUE )
                {
                    DoPublishRisk = TRUE;
                }

                // Rend la valeur non valide, ainsi elle ne sera pas publi�e plus bas.
                Value = _T( "" );
            }
        }

        // Si l'ordre de publication est donn�, on publie le risque.
        if ( DoPublishRisk == TRUE )
        {
            if ( m_RiskContainer.IsEmpty() == FALSE )
            {
                GenerateHTMLSectionTitle( m_RiskContainer.GetAt( 0 ) );

                for ( int j = 1; j < m_RiskContainer.GetCount(); j += 2 )
                {
                    GenerateHTMLSectionLine( _T( "" ), m_RiskContainer.GetAt( j ), m_RiskContainer.GetAt( j + 1 ) );
                }

                // On remet toutes les valeurs � leurs �tat initial pour la prochaine publication.
                m_RiskContainer.RemoveAll();
                RiskIsValid = FALSE;
                DoPublishRisk = FALSE;
            }
        }
        // *************************************************************************************************************

        if ( Value != _T( "" ) )
        {
            // *********************************************************************************************************
            // JMR-MODIF - Le 16 avril 2007 - On ne cr�e un nouveau titre que si au moins une valeur peut �tre affich�e.

            // Si la cat�gorie est nouvelle, on cr�e une nouvelle section.
            if ( pProp->GetCategoryID() != nCatID )
            {
                GenerateHTMLSectionTitle( pProp->GetCategory() );
                nCatID = pProp->GetCategoryID();
            }
            // *********************************************************************************************************

            GenerateHTMLSectionLine( _T( "" ), pProp->GetLabel(), Value );
        }
    }
}

// Cette fonction permet la g�n�ration d'un en-t�te standard HTML.
void ZVPublishProcessReport::GenerateHTMLPageHead( CString Title )
{
    CString Output = _T( "" );

    Output.Format( IDS_PROCESSREPORT_HTML_1, Title );

    WriteLine( Output );
}

// Cette fonction permet la g�n�ration d'un pied de page standard HTML.
void ZVPublishProcessReport::GenerateHTMLPageFoot()
{
    WriteLine( IDS_PROCESSREPORT_HTML_2 );
}

// Cette fonction permet de g�n�rer un en-t�te pour un tableau dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLTableHead()
{
    WriteLine( IDS_PROCESSREPORT_HTML_3 );
}

// Cette fonction permet de g�n�rer une fin pour un tableau dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLTableFoot()
{
    WriteLine( IDS_PROCESSREPORT_HTML_4 );
}

// JMR-MODIF - Le 18 avril 2007 - Suppression du 3�me param�tre.
// Cette fonction permet de g�n�rer le titre du rapport dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLReportTitle( CString DomainName, CString Title )
{
    CString Output = _T( "" );

    // JMR-MODIF - Le 18 avril 2007 - Suppression du 3�me param�tre.
    Output.Format( IDS_PROCESSREPORT_HTML_5,
                   DomainName,
                   Title );

    WriteLine( Output );
}

// Cette fonction permet de g�n�rer un titre de symbole dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLSymbolTitle( int        NbRef,
                                                      CString    Title,
                                                      CString    ObjectType,
                                                      COLORREF    ColorTitle )
{
    CString Output = _T( "" );

    // Les couleurs sont converties � l'envers. Donc il faut croiser le sens.
    COLORREF R = ( ColorTitle & 0xFF0000 ) >> 16;
    COLORREF G =   ColorTitle & 0xFF00;
    COLORREF B = ( ColorTitle & 0xFF ) << 16;

    COLORREF OutColorTitle = R + G + B;

    Output.Format( IDS_PROCESSREPORT_HTML_6,
                   (UINT)OutColorTitle,
                   NbRef,
                   Title,
                   (UINT)OutColorTitle,
                   ObjectType );

    // Lors du formattage de la couleur, 6 caract�res sont r�serv�s pour l'encodage, mais les 0 situ�s avant
    // le premier chiffre ne sont pas reproduits. Or ceux-ci sont importants pour une repr�sentation correcte de
    // la couleur. Par exemple #ff00 donne du rouge, alors que #00ff00 donne du vert. Dans la cha�ne formatt�e,
    // on retrouve #  ff00. Dans internet explorer, l'absence de 0 est interpr�t� correctement, mais pour �viter
    // tout probl�mes de compatibilit�, la boucle ci-dessous convertit les espaces en 0 dans cette partie de la
    // cha�ne de caract�res. Ainsi on obtient bien #00ff00 et non pas #  ff00.
    BOOL bFindStartChar = FALSE;

    for ( int i = 0; i < Output.GetLength(); i++ )
    {
        if ( Output.GetAt( i ) == '#' )
        {
            bFindStartChar = TRUE;
        }

        if ( bFindStartChar == TRUE )
        {
            if ( Output.GetAt( i ) == ' ' )
            {
                Output.SetAt( i, '0' );
            }

            if ( Output.GetAt( i ) == '"' )
            {
                bFindStartChar = FALSE;
            }
        }
    }

    WriteLine( Output );
}

// Cette fonction permet de g�n�rer un titre de symbole dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLSymbolTitle( int        NbRef,
                                                      CString    Title,
                                                      COLORREF    ColorTitle )
{
    CString Output = _T( "" );

    // Les couleurs sont converties � l'envers. Donc il faut croiser le sens.
    COLORREF R = ( ColorTitle & 0xFF0000 ) >> 16;
    COLORREF G =   ColorTitle & 0xFF00;
    COLORREF B = ( ColorTitle & 0xFF ) << 16;

    COLORREF OutColorTitle = R + G + B;

    Output.Format( IDS_PROCESSREPORT_HTML_7,
                   (UINT)OutColorTitle,
                   NbRef,
                   Title );

    // Lors du formattage de la couleur, 6 caract�res sont r�serv�s pour l'encodage, mais les 0 situ�s avant
    // le premier chiffre ne sont pas reproduits. Or ceux-ci sont importants pour une repr�sentation correcte de
    // la couleur. Par exemple #ff00 donne du rouge, alors que #00ff00 donne du vert. Dans la cha�ne formatt�e,
    // on retrouve #  ff00. Dans internet explorer, l'absence de 0 est interpr�t� correctement, mais pour �viter
    // tout probl�mes de compatibilit�, la boucle ci-dessous convertit les espaces en 0 dans cette partie de la
    // cha�ne de caract�res. Ainsi on obtient bien #00ff00 et non pas #  ff00.
    BOOL bFindStartChar = FALSE;

    for ( int i = 0; i < Output.GetLength(); i++ )
    {
        if ( Output.GetAt( i ) == '#' )
        {
            bFindStartChar = TRUE;
        }

        if ( bFindStartChar == TRUE )
        {
            if ( Output.GetAt( i ) == ' ' )
            {
                Output.SetAt( i, '0' );
            }

            if ( Output.GetAt( i ) == '"' )
            {
                bFindStartChar = FALSE;
            }
        }
    }

    WriteLine( Output );
}

// Cette fonction permet de g�n�rer un titre de section dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLSectionTitle( CString Title )
{
    CString Output = _T( "" );

    Output.Format( IDS_PROCESSREPORT_HTML_8, Title );

    WriteLine( Output );
}

// Cette fonction permet de g�n�rer une ligne de section dans la page HTML.
void ZVPublishProcessReport::GenerateHTMLSectionLine( CString NbRef, CString Title, CString Description )
{
    CString Output = _T( "" );

    Output.Format( IDS_PROCESSREPORT_HTML_9,
                   NbRef,
                   Title,
                   Description);

    WriteLine( Output );
}

// Cette fonction permet de g�n�rer une ligne de s�paration noire dans la page HTML.
void ZVPublishProcessReport::GenerateBlackLine()
{
    WriteLine( IDS_PROCESSREPORT_HTML_10 );
}

// Cette fonction permet de g�n�rer une s�paration de paragraphe dans la page HTML.
void ZVPublishProcessReport::GenerateSeparation()
{
    WriteLine( IDS_PROCESSREPORT_HTML_11 );
}

// Cette fonction permet d'�crire une cha�ne de caract�res sur le disque, en provenance d'un ID.
void ZVPublishProcessReport::WriteLine( int nID )
{
    CString Output = _T( "" );

    Output.LoadString( nID );

    if ( Output != _T( "" ) )
    {
        HtmlFile << Output;
    }
}

// Cette fonction permet d'�crire une cha�ne de caract�res sur le disque.
void ZVPublishProcessReport::WriteLine( CString Text )
{
    if ( Text != _T( "" ) )
    {
        HtmlFile << Text;
    }
}
