// ******************************************************************************************************
// *											  Classe Maths											*
// ******************************************************************************************************
// * JMR-MODIF - Le 18 janvier 2006 - Cr�ation de la nouvelle classe Maths.								*
// ******************************************************************************************************
// * Description	: Cette classe mets � disposition des outils math�matiques standards.				*
// * Cr�ateur		: Jean-Milost Reymond																*
// * Date			: Le 18 janvier 2006																*
// * Modification	:																					*
// * Date			:																					*
// ******************************************************************************************************

#include "stdafx.h"
#include "Maths.h"

// ******************************************************************************************************
// *										  Construction et destruction								*
// ******************************************************************************************************

// Constructeur par d�faut de la classe Maths.
Maths::Maths()
{
}

// Destructeur de la classe Maths.
Maths::~Maths()
{
}

// ******************************************************************************************************
// *							  Fonctions publiques de la classe ZVPublishReport						*
// ******************************************************************************************************

// Retourne le vecteur normalis�. L'utilisateur a la responsabilit� de d�truire le vecteur retourn� apr�s utilisation.
Vector2D* Maths::getNormalizedVector2D( Vector2D* toNormalize )
{
	float n = sqrt( ( toNormalize->getX() * toNormalize->getX() ) + ( toNormalize->getY() * toNormalize->getY() ) );

	return new Vector2D( toNormalize->getX() / n, toNormalize->getY() / n );
}

// Retourne le produit scalaire de deux vecteurs.
float Maths::getDotProduct( Vector2D* v1, Vector2D* v2 )
{
	return ( v1->getX() * v2->getX() + v1->getY() * v2->getY() );
}

// Teste si la coordonn�e d'un point donn� se trouve � l'int�rieur d'un triangle donn�.
BOOL Maths::IsTriPointCollision( Triangle* aTriangle, Vector2D* aPoint)
{
	BOOL myResult = FALSE;

	Vector2D* PToV1 = new Vector2D( aTriangle->getVertex1().getX() - aPoint->getX(),
									aTriangle->getVertex1().getY() - aPoint->getY() );
	Vector2D* PToV2 = new Vector2D( aTriangle->getVertex2().getX() - aPoint->getX(),
									aTriangle->getVertex2().getY() - aPoint->getY() );
	Vector2D* PToV3 = new Vector2D( aTriangle->getVertex3().getX() - aPoint->getX(),
									aTriangle->getVertex3().getY() - aPoint->getY() );

	Vector2D* NormalizedPToV1 = getNormalizedVector2D( PToV1 );
	Vector2D* NormalizedPToV2 = getNormalizedVector2D( PToV2 );
	Vector2D* NormalizedPToV3 = getNormalizedVector2D( PToV3 );

	// Obtient les trois produits vectoriels, afin de calculer l'angle total entre les 3 vecteurs.
	float A1 = getDotProduct( NormalizedPToV1, NormalizedPToV2 );
	float A2 = getDotProduct( NormalizedPToV2, NormalizedPToV3 );
	float A3 = getDotProduct( NormalizedPToV3, NormalizedPToV1 );

	// Corrige une erreur d'arrondi du processeur. Parfois, le r�sultat peut �tre de 1.0000000000000000000001f,
	// et cela suffit � faire �chouer les fonctions acosf ci-apr�s.
	if ( A1 < ( -1.0f ) )	A1 = -1.0f;
	if ( A2 < ( -1.0f ) )	A2 = -1.0f;
	if ( A3 < ( -1.0f ) )	A3 = -1.0f;

	if ( A1 > 1.0f )		A1 = 1.0f;
	if ( A2 > 1.0f )		A2 = 1.0f;
	if ( A3 > 1.0f )		A3 = 1.0f;

	// Calcule l'angle total.
	float AngleResult = acosf( A1 ) + acosf( A2 ) + acosf( A3 );

	// Si l'angle vaut 360 degr�s, on se trouve au centre du triangle. Sinon, tant pis...
	if ( AngleResult >= 6.28f )
	{
		myResult = TRUE;
	}

	// Nettoyage de la m�moire.
	delete PToV1;
	delete PToV2;
	delete PToV3;
	delete NormalizedPToV1;
	delete NormalizedPToV2;
	delete NormalizedPToV3;

	return myResult;
}
