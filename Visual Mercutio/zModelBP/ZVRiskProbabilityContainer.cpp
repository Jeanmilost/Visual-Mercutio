// **************************************************************************************************************
// *                                      Classe ZVRiskProbabilityContainer                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 11 juillet 2007 - Ajout de la classe ZVRiskProbabilityContainer.                            *
// **************************************************************************************************************
// * Cette classe contient en m�moire les probabilit�s pour les risques, en synchronisation avec le fichier des    *
// * probabilit�s.                                                                                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskProbabilityContainer.h"

#include "zBaseLib\ZDTextFile.h"

// Constructeur de la classe ZVRiskProbabilityContainer.
ZVRiskProbabilityContainer::ZVRiskProbabilityContainer()
{
}

// Destructeur de la classe ZVRiskProbabilityContainer.
ZVRiskProbabilityContainer::~ZVRiskProbabilityContainer()
{
    RemoveAllElements();
}

// Cette fonction permet d'ouvrir un fichier de donn�es.
BOOL ZVRiskProbabilityContainer::LoadFile( CString Filename )
{
    if ( Filename.IsEmpty() == true )
    {
        return FALSE;
    }

    m_Filename = Filename;

    ZDTextFile p_File;

    if ( p_File.OpenRead( m_Filename ) == FALSE )
    {
        return FALSE;
    }

    BOOL    m_EndReached    = FALSE;
    CString    m_Text            = _T( "" );

    while( m_EndReached != TRUE )
    {
        p_File >> m_Text;

        if ( m_Text.IsEmpty() == false )
        {
            m_Set.Add( m_Text );
        }
        else
        {
            m_EndReached = TRUE;
        }
    }

    p_File.CloseFile();

    return TRUE;
}

// Obtient la liste des �l�ments.
CStringArray* ZVRiskProbabilityContainer::GetElementsArray()
{
    return &m_Set;
}

// Obtient l'�l�ment � la position indiqu�e.
CString ZVRiskProbabilityContainer::GetElementAt( size_t Index ) const
{
    if ( Index < GetElementCount() )
    {
        return m_Set.GetAt( Index );
    }

    return _T( "" );
}

// Cette fonction retourne le nom du fchier en cours d'utilisation.
CString ZVRiskProbabilityContainer::GetFilename()
{
    return m_Filename;
}

// Cette fonction permet la suppression de tous les �l�ments dans la liste.
void ZVRiskProbabilityContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
