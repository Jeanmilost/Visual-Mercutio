/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:		 03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __PPUBLISHWORKGROUP_HDR_
#define __PPUBLISHWORKGROUP_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "pworkgroup.h"

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 septembre 2005 - Ajout de la d�coration Unicode _T( ) pour les cha�nes de caract�res de cette classe.

//Define serializers / soap mapping

/////////////////////////////////////////////
// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pworkgroup>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pworkgroup" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pworkgroup& val )
	{
		param.AddParameter( _T( "wkgid" ) )		<< val.wkgid.c_str();
		param.AddParameter( _T( "wkgparent" ) )	<< val.wkgparent.c_str();
		param.AddParameter( _T( "wkgname" ) )	<< val.wkgname.c_str();

		// JMR-MODIF - Le 29 mai 2006 - Ajout du param�tre "mission".
		param.AddParameter( _T( "mission" ) )	<< val.mission.c_str();

		// JMR-MODIF - Le 6 d�cembre 2006 - Ajout du param�tre "daycost".
		param.AddParameter( _T( "daycost" ) )	<< val.daycost.c_str();
		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pworkgroup& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "wkgid" ) )		>> tmp;
		val.wkgid		= tmp.Str();
		param.GetParameter( _T( "wkgparent" ) )	>> tmp;
		val.wkgparent	= tmp.Str();
		param.GetParameter( _T( "wkgname" ) )	>> tmp;
		val.wkgname		= tmp.Str();

		// JMR-MODIF - Le 29 mai 2006 - Ajout du param�tre "mission".
		param.GetParameter( _T( "mission" ) )	>> tmp;
		val.mission		= tmp.Str();

		// JMR-MODIF - Le 6 d�cembre 2006 - Ajout du param�tre "daycost".
		param.GetParameter( _T( "daycost" ) )	>> tmp;
		val.daycost		= tmp.Str();

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pworkgroup> > : public SOAPArrayTypeTraits
{
};

class AFX_EXT_CLASS pPublishWorkgroup
{
public:

	pPublishWorkgroup();
	~pPublishWorkgroup();

	void reset();
	void addWorkgroup( pworkgroup wkg );

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction addAlias.
	void addAlias( CString Alias );

	bool send();

private:

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_Alias.
	CString				m_Alias;

	list<pworkgroup>	m_workgroups;
};

END_EASYSOAP_NAMESPACE

#endif