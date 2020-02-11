// **********************************************************************************************************
// *                                  Classe ZUDeleteCorruptedSymbols                                        *
// **********************************************************************************************************
// * JMR-MODIF - Le 19 octobre 2006 - Ajout de la classe ZUDeleteCorruptedSymbols.                            *
// **********************************************************************************************************
// * Cette classe contr�le et d�truit les symboles corrompus, par exemple : Porte sans clone, copie sans    *
// * symbole local rattach�, label sans lien, etc...                                                        *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZUDeleteCorruptedSymbols.h"

ZUDeleteCorruptedSymbols::ZUDeleteCorruptedSymbols()
{}

ZUDeleteCorruptedSymbols::~ZUDeleteCorruptedSymbols()
{}

void ZUDeleteCorruptedSymbols::CheckModel(PSS_ProcessGraphModelMdlBP* m_StartRootModel)
{
    if (m_StartRootModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if (pSet != NULL)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for (PSS_ProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contr�leur de mod�le de la page courante.
                PSS_ProcessGraphModelMdlBP* m_CurModel =
                    dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if (pCompSet != NULL)
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for (int j = 0; j < pCompSet->GetSize(); ++j)
                        {
                            CODComponent* pComponent = pCompSet->GetAt(j);

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une proc�dure.
                            if (pComponent && ISA(pComponent, PSS_ProcedureSymbolBP))
                            {
                                PSS_ProcedureSymbolBP* m_Procedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

                                if (IsCorrupted(m_Procedure))
                                {
                                    CorruptedSymbols.Add(m_Procedure);
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point start.
                            if (pComponent && ISA(pComponent, ZBBPStartSymbol))
                            {
                                ZBBPStartSymbol* m_Start = dynamic_cast<ZBBPStartSymbol*>(pComponent);

                                if (IsCorrupted(m_Start))
                                {
                                    CorruptedSymbols.Add(m_Start);
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un point stop.
                            if (pComponent && ISA(pComponent, ZBBPStopSymbol))
                            {
                                ZBBPStopSymbol* m_Stop = dynamic_cast<ZBBPStopSymbol*>(pComponent);

                                if (IsCorrupted(m_Stop))
                                {
                                    CorruptedSymbols.Add(m_Stop);
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'une porte.
                            if (pComponent && ISA(pComponent, PSS_DoorSymbolBP))
                            {
                                PSS_DoorSymbolBP* m_Door = dynamic_cast<PSS_DoorSymbolBP*>(pComponent);

                                if (IsCorrupted(m_Door))
                                {
                                    CorruptedSymbols.Add(m_Door);
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un lien.
                            if (pComponent && ISA(pComponent, ZBDeliverableLinkSymbol))
                            {
                                ZBDeliverableLinkSymbol* m_Link =
                                    dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent);

                                if (IsCorrupted(m_Link))
                                {
                                    CorruptedSymbols.Add(m_Link);
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if (pComponent && ISA(pComponent, PSS_ProcessSymbolBP))
                            {
                                // Convertit le symbole.
                                PSS_ProcessSymbolBP* m_Process = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

                                if (IsCorrupted(m_Process))
                                {
                                    CorruptedSymbols.Add(m_Process);
                                }
                                else
                                {
                                    // Obtient le contr�leur de mod�le du processus.
                                    PSS_ProcessGraphModelMdlBP* m_ChildModel =
                                        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_Process->GetModel());

                                    // Appel r�cursif � CheckModel, jusqu'� ce que toutes les pages des processus
                                    // enfants aient �t� visit�es.
                                    CheckModel(m_ChildModel);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Contr�le que les propri�t�s du symbole processus donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(PSS_ProcessSymbolBP* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole proc�dure donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(PSS_ProcedureSymbolBP* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole start donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(ZBBPStartSymbol* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole stop donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(ZBBPStopSymbol* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole porte donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(PSS_DoorSymbolBP* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    // Si une porte ne peut plus retrouver son jumeau, c'est que celui-ci a �t� effac�.
    // Dans ce cas, le symbole est corrompu, car une porte ne peut pas exister sans jumeau.
    if (m_Symbol->GetTwinDoorSymbol() == NULL)
    {
        return TRUE;
    }

    // Si la porte jumelle d'un symbole contient un pointeur sur une porte qui ne correspond pas au symbole de d�part,
    // alors la porte est consid�r�e comme corrompue.
    if (m_Symbol->GetTwinDoorSymbol() != NULL && m_Symbol->GetTwinDoorSymbol()->GetTwinDoorSymbol() != m_Symbol)
    {
        return TRUE;
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole page donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(PSS_PageSymbolBP* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    // Si une page ne peut plus retrouver son jumeau, c'est que celui-ci a �t� effac�.
    // Dans ce cas, le symbole est corrompu, car une porte ne peut pas exister sans jumeau.
    if (m_Symbol->GetTwinPageSymbol() == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole package donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(PSS_PackageSymbolBP* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// Contr�le que les propri�t�s du symbole de lien donn� soient convenables.
BOOL ZUDeleteCorruptedSymbols::IsCorrupted(ZBDeliverableLinkSymbol* m_Symbol)
{
    if (m_Symbol == NULL)
    {
        return FALSE;
    }

    // Si le symbole est une copie, il doit pouvoir retrouver son symbole original.
    // Si ce n'est pas possible, alors l'original a �t� effa��, donc le symbole est corrompu.
    if (!m_Symbol->IsLocal())
    {
        if (m_Symbol->GetLocalSymbol() == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}

CODComponentSet* ZUDeleteCorruptedSymbols::GetCorruptedSymbolList()
{
    return &CorruptedSymbols;
}
