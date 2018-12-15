/////////////////////////////////////////////////////////////////////////////
//@doc ZBProcCombinations
//@module ZBProcCombinations.cpp | Implementation of the <c ZBProcCombinations> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// Author: Dom
// <nl>Created: 06/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBProcCombinations.h"

#include "ZBBPCombinationProp.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 f�vrier 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastCombinationIDProperties = ZS_BP_PROP_COMBINATION + 39;

IMPLEMENT_SERIAL( ZBProcCombinations, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBProcCombinations::ZBProcCombinations( CODSymbolComponent* pParent /*= NULL*/ )
    : m_pParent( pParent )
{
}

ZBProcCombinations::~ZBProcCombinations()
{
    RemoveAllCombinations();
}

ZBProcCombinations::ZBProcCombinations( const ZBProcCombinations& src )
{
    *this = src;
}

ZBProcCombinations& ZBProcCombinations::operator=( const ZBProcCombinations& src )
{
    // Copy the members.
    ZBBPCombinationPropertiesIterator i( &const_cast<ZBProcCombinations&>( src ).GetCombinationSet() );

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddCombination( pProp->Dup() );
    }

    m_pParent = src.m_pParent;

    return *this;
}

ZBProcCombinations* ZBProcCombinations::Dup() const
{
    return ( new ZBProcCombinations( *this ) );
}

void ZBProcCombinations::SetParent( CODSymbolComponent* pParent )
{
    m_pParent = pParent;
}

bool ZBProcCombinations::CreateInitialProperties()
{
    if ( GetCombinationCount() > 0 )
    {
        return true;
    }

    ZBBPCombinationProperties* pProps = new ZBBPCombinationProperties;

    if ( AddCombination( pProps ) >= 0 )
    {
        return true;
    }

    return false;
}

int ZBProcCombinations::AddNewCombination()
{
    ZBBPCombinationProperties* pProps = new ZBBPCombinationProperties;

    return AddCombination( pProps );
}

int ZBProcCombinations::AddCombination( ZBBPCombinationProperties* pProperty )
{
    if ( pProperty )
    {
        // If no combination name specified, set it by default
        if ( pProperty->GetCombinationName().IsEmpty() )
        {
            pProperty->SetCombinationName( GetNextCombinationValidName() );
        }

        m_Set.Add( pProperty );

        // Returns the index
        return GetCombinationCount() - 1;
    }

    return -1;
}

bool ZBProcCombinations::DeleteCombination( size_t Index )
{
    if ( Index < GetCombinationCount() )
    {
        ZBBPCombinationProperties* pProperty = GetProperty( Index );

        if ( pProperty != NULL )
        {
            delete pProperty;
            pProperty = NULL;

            m_Set.RemoveAt( Index );

            return true;
        }
    }

    return false;
}

bool ZBProcCombinations::DeleteCombination( ZBBPCombinationProperties* pProperty )
{
    ZBBPCombinationPropertiesIterator i( &m_Set );

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProperty == pProp )
        {
            delete pProp;
            pProp = NULL;

            i.Remove();

            return true;
        }
    }

    return false;
}

void ZBProcCombinations::RemoveAllCombinations()
{
    ZBBPCombinationPropertiesIterator i( &m_Set );

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    // Then, remove all elements
    m_Set.RemoveAll();
}

CString ZBProcCombinations::GetCombinationName( size_t Index ) const
{
    if ( Index < GetCombinationCount() )
    {
        return m_Set.GetAt( Index )->GetCombinationName();
    }

    return _T( "" );
}

void ZBProcCombinations::SetCombinationName( size_t Index, CString Value )
{
    if ( Index < GetCombinationCount() )
    {
        m_Set.GetAt(Index)->SetCombinationName( Value );
    }
}

CString ZBProcCombinations::GetCombinationDeliverables( size_t Index ) const
{
    if ( Index < GetCombinationCount() )
    {
        return m_Set.GetAt( Index )->GetCombinationDeliverables();
    }

    return _T( "" );
}

void ZBProcCombinations::SetCombinationDeliverables( size_t Index, CString Value )
{
    if ( Index < GetCombinationCount() )
    {
        m_Set.GetAt( Index )->SetCombinationDeliverables( Value );
    }
}

bool ZBProcCombinations::AddCombinationDeliverable( size_t Index, CString Value )
{
    CString Deliverables = GetCombinationDeliverables( Index );

    ZBTokenizer token;    // Initialize the token with ; as separator

    CString str = token.GetFirstToken( Deliverables );
    bool Found = false;
    
    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If we found the same deliverable,
        // then sets the Found flag to true
        if ( str == Value )
        {
            Found = true;
            break;
        }

        // Get the next token
        str = token.GetNextToken();
    }

    // If not found, add it
    if ( Found == false )
    {
        token.InitializeString( Deliverables );
        token.AddToken( Value );

        // Set the new deliverable complete string
        SetCombinationDeliverables( Index, token.GetString() );
    }

    return true;
}

bool ZBProcCombinations::RemoveCombinationDeliverable( size_t Index, CString Value )
{
    CString Deliverables = GetCombinationDeliverables( Index );

    ZBTokenizer srcToken;    // Initialize the source token with ; as separator
    ZBTokenizer dstToken;    // Initialize the destination token with ; as separator

    CString str = srcToken.GetFirstToken( Deliverables );
    bool Found = false;

    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If we found the same deliverable,
        // then sets the Found flag to true
        // and skip it
        if ( str == Value )
        {
            Found = true;
        }
        else
        {
            // If not the same, can be added to the destination token
            dstToken.AddToken( str );
        }

        // Get the next token
        str = srcToken.GetNextToken();
    }

    // If we found it, sets the new string
    if ( Found == true )
    {
        // Set the new deliverable complete string
        SetCombinationDeliverables( Index, dstToken.GetString() );
        return true;
    }

    return false;
}

bool ZBProcCombinations::RemoveAllCombinationDeliverable( size_t Index )
{
    SetCombinationDeliverables( Index, _T( "" ) );
    return true;
}

float ZBProcCombinations::GetCombinationActivationPerc( size_t Index ) const
{
    if ( Index < GetCombinationCount() )
    {
        return m_Set.GetAt( Index )->GetCombinationActivationPerc();
    }

    return 0;
}

void ZBProcCombinations::SetCombinationActivationPerc( size_t Index, const float value )
{
    if ( Index < GetCombinationCount() )
    {
        m_Set.GetAt( Index )->SetCombinationActivationPerc( value );
    }
}

CString ZBProcCombinations::GetCombinationMaster( size_t Index ) const
{
    if ( Index < GetCombinationCount() )
    {
        return m_Set.GetAt( Index )->GetCombinationMaster();
    }

    return _T( "" );
}

void ZBProcCombinations::SetCombinationMaster( size_t Index, CString Value )
{
    if ( Index < GetCombinationCount() )
    {
        m_Set.GetAt(Index)->SetCombinationMaster( Value );
    }
}

bool ZBProcCombinations::CombinationNameExist( const CString Name ) const
{
    // Run through the set and build the string
    ZBBPCombinationPropertiesIterator i( &m_Set );

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetCombinationName() == Name )
        {
            return true;
        }
    }

    return false;
}

CString ZBProcCombinations::GetNextCombinationValidName() const
{
    CString str;
    int i = 1;

    do
    {
        str.Format( _T( "Comb %d" ), i++ );
    }
    while ( CombinationNameExist( str ) == true );

    return str;
}

CString ZBProcCombinations::GetAvailableDeliverables( const CString AllDeliverables ) const
{
    // First, retreive the allocated deliverables
    CString AllocatedDeliverables = GetAllocatedDeliverables();

    // Now run through all deliverables and check wich one is available
    ZBTokenizer srcToken;    // Initialize the source token with ; as separator
    ZBTokenizer dstToken;    // Initialize the destination token with ; as separator

    CString str = srcToken.GetFirstToken( AllDeliverables );

    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If the token is not in the allocated deliverable string
        // add it to the destination token string
        if ( !IsDeliverableInString( AllocatedDeliverables, str ) )
        {
            dstToken.AddToken( str );
        }

        // Get the next token
        str = srcToken.GetNextToken();
    }

    // Return the available deliverables string
    return dstToken.GetString();
}

CString ZBProcCombinations::GetAllocatedDeliverables() const
{
    ZBTokenizer token;    // Initialize the token with ; as separator

    // Run through the set and build the string
    ZBBPCombinationPropertiesIterator i( &m_Set );

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        // Add the deliverables
        token.AddToken( pProp->GetCombinationDeliverables() );
    }

    // Return the constructed string
    return token.GetString();
}        

bool ZBProcCombinations::IsDeliverableInString( const CString Deliverables, const CString Value ) const
{
    ZBTokenizer token;    // Initialize the token with ; as separator

    CString str = token.GetFirstToken( Deliverables );

    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If we found the same deliverable,
        // then return true
        if ( str == Value )
        {
            return true;
        }

        // Get the next token
        str = token.GetNextToken();
    }

    return false;
}

ZBBPCombinationProperties* ZBProcCombinations::LocateCombinationOfDeliverable( const CString DeliverableName ) const
{
    int Index = LocateCombinationIndexOfDeliverable( DeliverableName );

    if ( Index == -1 )
    {
        return NULL;
    }

    return GetProperty( Index );
}

int ZBProcCombinations::LocateCombinationIndexOfDeliverable( const CString DeliverableName ) const
{
    // Run through the set of deliverables and check if found
    ZBBPCombinationPropertiesIterator i( &m_Set );
    int Index = 0;

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Index )
    {
        if ( IsDeliverableInString( pProp->GetCombinationDeliverables(), DeliverableName ) )
        {
            return Index;
        }
    }

    return -1;
}

ZBBPCombinationProperties* ZBProcCombinations::LocateCombinationOfMaster( const CString Master ) const
{
    int Index = LocateCombinationIndexOfMaster( Master );

    if ( Index == -1 )
    {
        return NULL;
    }

    return GetProperty( Index );
}

int ZBProcCombinations::LocateCombinationIndexOfMaster( const CString Master ) const
{
    // Run through the set of deliverables and check if found
    ZBBPCombinationPropertiesIterator i( &m_Set );
    int Index = 0;

    for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Index )
    {
        if ( !pProp->GetCombinationMaster().IsEmpty() && pProp->GetCombinationMaster() == Master )
        {
            return Index;
        }
    }

    return -1;
}

bool ZBProcCombinations::ReplaceDeliverable( const CString OldDeliverableName, const CString NewDeliverableName )
{
    int Index        = LocateCombinationIndexOfDeliverable( OldDeliverableName );
    bool RetValue    = false;

    if ( Index != -1 )
    {
        // First, remove the old deliverable
        if ( !RemoveCombinationDeliverable( Index, OldDeliverableName ) )
        {
            return false;
        }
    
        // Then add the new name and return the status
        RetValue = AddCombinationDeliverable( Index, NewDeliverableName );
    }

    ZBBPCombinationProperties* pCombination = LocateCombinationOfMaster( OldDeliverableName );

    if ( pCombination )
    {
        // Sets the new deliverable name
        pCombination->SetCombinationMaster( NewDeliverableName );
        RetValue = true;
    }

    // Not found or not done
    return RetValue;
}

bool ZBProcCombinations::DeleteDeliverableFromAllCombinations( const CString DeliverableName )
{
    int Index        = LocateCombinationIndexOfDeliverable( DeliverableName );
    bool RetValue    = false;

    if ( Index != -1 )
    {
        // First, remove the old deliverable
        if ( !RemoveCombinationDeliverable( Index, DeliverableName ) )
        {
            return false;
        }
    }

    ZBBPCombinationProperties* pCombination = LocateCombinationOfMaster( DeliverableName );

    if ( pCombination )
    {
        // Sets the new deliverable name
        pCombination->SetCombinationMaster( _T( "" ) );
        RetValue = true;
    }

    // Not found or not done
    return RetValue;
}

void ZBProcCombinations::Serialize( CArchive& ar )
{
    // Only if the object is serialize from and to a document
    if ( ar.m_pDocument )
    {
        if ( ar.IsStoring() )
        {
            TRACE( _T( "ZBProcCombinations::Serialize : Start Save\n" ) );
    
            // JMR-MODIF - Le 7 septembre 2005 - Ajout de la conversion explicite de SEC_INT en int.
            // Serialize the size of the set
            ar << (int)m_Set.GetSize();

            ZBBPCombinationPropertiesIterator i( &m_Set );

            for ( ZBBPCombinationProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                ar << pProp;
            }

            TRACE( _T( "ZBProcCombinations::Serialize : End Save\n" ) );
        }
        else
        {
            TRACE( _T( "ZBProcCombinations::Serialize : Start Read\n" ) );

            RemoveAllCombinations();

            // Read the size of the set
            int Count;
            ar >> Count;

            ZBBPCombinationProperties* pProp;

            for ( int i = 0; i < (int)Count; ++i )
            {
                ar >> pProp;
                AddCombination( pProp );
            }
        
            TRACE( _T( "ZBProcCombinations::Serialize : End Read\n" ) );
        }
    }
}
