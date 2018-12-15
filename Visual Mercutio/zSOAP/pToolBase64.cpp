/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.cpp | Implementation of the <c XXXClass> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 03/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// BASE 64 Encoder

#include <stdio.h>

// JMR-MODIF - Le 14 septembre 2005 - Ajout des d�corations Unicode _T(), nettoyage du code inutile.(En commentaires)

// JMR-MODIF - Le 14 septembre 2005 - Suppression de la macro b64pitchar : Identique � b64putchar et jamais utilis�e.
#define b64putchar( xxx ) outbuf[outpos++] = xxx;

unsigned char alphabet[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Cette fonction permet de d�crypter une cha�ne de caract�res.
string b64decode( unsigned char* pstr, int len )
{
    static char inalphabet[256];
    static char decoder[256];

    int bits        = 0;
    int char_count    = 0;
    int errors        = 0;
    int pos            = 0;
    int outpos        = 0;
    int i;
    int c;

    // JMR-MODIF - Le 14 septembre 2005 - Correction de l'allocation m�moire du buffer outbuf.
    // La cha�ne d�crypt�e est plus courte que la cha�ne crypt�e, on peut utiliser la longeur de la cha�ne
    // crypt�e pour allouer la m�moire. On ajoute 1 par s�curit�.
//    unsigned char* outbuf = new unsigned char[len];
    unsigned char* outbuf = new unsigned char[len + 1];

    // Remplit les buffers de codage.
    for ( i = ( sizeof alphabet ) - 1; i >= 0 ; i-- )
    {
        inalphabet[alphabet[i]]    = 1;
        decoder[alphabet[i]]    = i;
    }

    while ( 1 )
    {
        // Si la position courante est sup�rieure ou �gale � la longeur de la cha�ne d'entr�e, arr�te.
        if ( pos >= len )
        {
            break;
        }

        // R�cup�re la valeur num�rique du caract�re courant de la cha�ne � d�crypter.
        c = pstr[pos++];

        if ( c == '=' )
        {
            break;
        }

        if ( c > 255 || !inalphabet[c] )
        {
            continue;
        }

        // D�crypte la cha�ne : On d�code 3 blocs par 3 blocs. Les blocs d'entr�e sont combin�s dans un type int,
        // dont chaque octet contient un caract�re d�crypt�. Lorsque trois blocs de la cha�ne d'entr�e ont �t�
        // combin�s, on �crit chacun des trois octets dans la cha�ne de caract�res de sortie, en s�lectionnant le bon
        // octet par d�calage (op�rateur >>) et en masquant les donn�es superflues (bits and 0xff).
        bits += decoder[c];
        char_count++;

        if ( char_count == 4 )
        {
            b64putchar( bits >> 16 );
            b64putchar( ( bits >> 8 ) & 0xff );
            b64putchar( bits & 0xff );

            bits        = 0;
            char_count    = 0;
        }
        else
        {
            bits <<= 6;
        }
    }

    // Lorsque la cha�ne est arriv�e � la fin, on teste s'il reste des blocs encore non d�crypt�s. Si c'est le cas,
    // on les d�crypte.
    if ( c > len )
    {
        if ( char_count )
        {
            errors++;
        }
    }
    else
    {
        /* c == '=' */
        switch ( char_count )
        {
            case 1:
            {
                errors++;
                break;
            }

            case 2:
            {
                b64putchar( bits >> 10 );
                break;
            }

            case 3:
            {
                b64putchar( bits >> 16 );
                b64putchar( ( bits >> 8 ) & 0xff );
                break;
            }
        }
    }

    if ( errors > 0 )
    {
        TRACE( _T( "Base 64 decoding error\n" ) );
    }

    outbuf[outpos]    = 0;
    string tmpret    = (char*)outbuf;
    delete [] outbuf;

    return tmpret;
}

// Cette fonction permet de crypter une cha�ne de caract�res.
string b64encode( unsigned char* pstr, int len )
{
    int c;
    int char_count    = 0;
    int bits        = 0;
    int cols        = 0;
    int pos            = 0;
    int outpos        = 0;
    int bufsize        = 0;

    // ***************************************************************************************
    // JMR-MODIF - Le 14 septembre 2005 - Correction de l'allocation m�moire du buffer outbuf.

    // Calcule la longeur du buffer � assigner.
    while ( 1 )
    {
        if ( pos >= len )
        {
            break;
        }

        pos++;
        char_count++;

        if ( char_count == 3 )
        {
            bufsize    += 4;
            cols    += 4;

            if ( cols == 72 )
            {
                bufsize++;
                cols = 0;
            }

            char_count = 0;
        }
    }

    // Tient compte du marquage de fin de cha�ne.
    bufsize += 6;

//    unsigned char* outbuf = new unsigned char[len * 2];
    unsigned char* outbuf = new unsigned char[bufsize + 1];
    // ***************************************************************************************

    char_count    = 0;
    cols        = 0;
    pos            = 0;

    while ( 1 )
    {
        if ( pos >= len )
        {
            break;
        }

        c = pstr[pos++];

        if ( c > 255 )
        {
            TRACE( _T( "Base 64 encoding encountered char > 255\n" ) );
        }

        // On crypte la cha�ne. On utilise ici une valeur de 6 bits pour les caract�res. La cha�ne est d�crypt�e de
        // fa�on asym�trique. On inscrit 4 caract�res crypt�s pour 3 caract�res d�crypt�s. Pour le cryptage, un
        // caract�re est consid�r� comme valant 6 bits. On peut remarquer ici la correspondance entre le cryptage et
        // le d�cryptage : En effet, 4 caract�res de 6 bits = 24 bits, et 3 caract�res de 8 bits = 24 bits. Mais
        // attention : cela signifie aussi que la cha�ne crypt�e sera plus longue d'un caract�re tous les 3 caract�res.
        // Il faut en tenir compte lors du calcul de l'allocation m�moire pour le buffer de sortie (outbuf).
        bits += c;
        char_count++;

        if ( char_count == 3 )
        {
            // JMR-MODIF - Le 14 septembre 2005 - Ajout du masque de bits pour le premier caract�re.
//            b64putchar( alphabet[bits >> 18] );
            b64putchar( alphabet[( bits >> 18 ) & 0x3f] );
            b64putchar( alphabet[( bits >> 12 ) & 0x3f] );
            b64putchar( alphabet[( bits >> 6 )  & 0x3f] );
            b64putchar( alphabet[bits & 0x3f] );

            cols += 4;

            if ( cols == 72 )
            {
                b64putchar( '\n' );
                cols = 0;
            }

            bits        = 0;
            char_count    = 0;
        }
        else
        {
            bits <<= 8;
        }
    }

    // On crypte ici les derniers caract�res restants, non trait�s ci-dessus. On ajoute aussi le marquage
    // de fin de ligne.
    if ( char_count != 0 )
    {
        bits <<= 16 - ( 8 * char_count );
        // JMR-MODIF - Le 14 septembre 2005 - Ajout du masque de bits pour le premier caract�re.
//        b64putchar( alphabet[bits >> 18] );
        b64putchar( alphabet[( bits >> 18 ) & 0x3f] );
        b64putchar( alphabet[( bits >> 12 ) & 0x3f] );

        if ( char_count == 1 )
        {
            b64putchar( '=' );
            b64putchar( '=' );
        }
        else
        {
            b64putchar( alphabet[( bits >> 6 ) & 0x3f] );
            b64putchar( '=' );
        }

        if ( cols > 0 )
        {
            b64putchar( '\n' );
        }
    }

    b64putchar( '\0' );
    string tmpret = (char*)outbuf;
    //JMR-MODIF - Le 14 septembre 2005 - Ajout� la ligne permettant le nettoyage des ressources de outbuf.
    delete [] outbuf;

    return tmpret;
}

string base64encode( const unsigned char *pcBuffIn, long nLenIn )
{
    string ret = b64encode( (unsigned char*)pcBuffIn, nLenIn );

    return ret;
}
