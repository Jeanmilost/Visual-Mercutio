// **********************************************************************************************************************
// *                                               Classe ZBMediator                                                    *
// **********************************************************************************************************************
// * Type de la classe : Singleton                                                                                        *
// **********************************************************************************************************************
// * Cette classe joue le r�le de "chef d'orchestre" du programme. Ici viennent s'inscrire toutes les classes qui ont    *
// * des fonctions qui doivent �tre accessibles par n'importe quelle classe de n'importe quel projet. C'est le cas, par *
// * exemple, des fonctions de rafra�chissement, qui doivent pouvoir �tre ordonn�e facilement depuis n'importe quel        *
// * point du programme.                                                                                                *
// **********************************************************************************************************************

#include "StdAfx.h"
#include "ZBMediator.h"

ZBMediator* ZBMediator::p_Instance = NULL;

// Cette fonction retourne l'instance unique du m�diateur.
ZBMediator* ZBMediator::Instance()
{
    if ( p_Instance == NULL )
    {
        // Cr�e l'instance unique du m�diateur.
        p_Instance = new ZBMediator();

        // Initialise toutes les donn�es contenues dans le m�diateur.
        p_Instance->p_MainApp = NULL;
    }

        return p_Instance;
}

// Cette fonction permet de lib�rer les ressources utilis�es par le m�diateur.
void ZBMediator::Release()
{
    if ( p_Instance != NULL )
    {
        delete p_Instance;
        p_Instance = NULL;
    }
}

// Cette fonction permet l'enregistrement d'une classe dans le m�diateur.
void ZBMediator::Register( zMediatorZAApp* p_Class )
{
    p_MainApp = p_Class;
}

// Cette fonction permet d'annuler l'enregistrement de la classe principale de l'application dans le m�diateur.
void ZBMediator::UnregisterMainApp()
{
    p_MainApp = NULL;
}

// Cette fonction permet d'obtenir la classe principale de l'application.
zMediatorZAApp* ZBMediator::GetMainApp()
{
    return p_MainApp;
}

// Cette fonction ordonne le rafra�chissement de l'espace des propri�t�s.
void ZBMediator::RefreshPropertiesWorkspace()
{
    if ( p_MainApp != NULL )
    {
        p_MainApp->DoRefreshProperties();
    }
}

// Cette fonction ordonne le rafra�chissement du symbole s�lectionn�, ainsi que des propri�t�s qui lui sont li�es.
void ZBMediator::RefreshSelectedSymbolAndProperties()
{
    if ( p_MainApp != NULL )
    {
        p_MainApp->DoRefreshSymbolsAndProperties();
    }
}
