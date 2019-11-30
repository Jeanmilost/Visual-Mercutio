// ZBBPPackageSymbol.h: interface for the ZBBPPackageSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPPackageSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPPackageSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Bitmap.h"
#include "zModel\ZBSymbol.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// Forward declaration
class PSS_ProcessModelDocTmpl;
class PSS_ProcessGraphModelDoc;
class ZDProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 3 mai 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBBPPackageSymbol : public ZBSymbol
{
    DECLARE_SERIAL(ZBBPPackageSymbol)

public:

    ZBBPPackageSymbol(const CString Name = _T(""), const CString fileName = _T(""));
    virtual ~ZBBPPackageSymbol();

    /* Copy constructor. */
    ZBBPPackageSymbol(const ZBBPPackageSymbol& src);

    /* Assignment operator. */
    ZBBPPackageSymbol& operator=(const ZBBPPackageSymbol& src);

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom(CODSymbolComponent& src);

    // Overloaded to be able to modify the activity name
    // and description
    virtual BOOL SetSymbolName(const CString value);

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const
    {
        return true;
    }

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool AcceptDynamicAttributes() const
    {
        // No dynamic attributes
        return false;
    }

    /**
    * Called when a tooltip is required
    *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
    *@param point - hit point
    *@param mode - tooltip mode
    *@return true if tooltip can be shown, otherwise false
    */
    virtual bool OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    // Drag and drop methods
    virtual bool AcceptDropItem(CObject* pObj, const CPoint& pt);
    virtual bool DropItem(CObject* pObj, const CPoint& pt);

    /* Creates the symbol component. */
    BOOL Create(const CString Name = _T(""), const CString fileName = _T(""));

    bool IsLoaded() const
    {
        return m_pPackageDoc != NULL;
    }

    PSS_ProcessGraphModelDoc* GetPackageDocumentPtr()
    {
        return m_pPackageDoc;
    }

    bool LoadPackage(PSS_ProcessModelDocTmpl* pDocTmpl, ZDProcessGraphModelMdl* pParent = NULL);
    bool UnloadPackage();

    bool IsLinkedToFileName() const
    {
        return !m_FileNameLinkedTo.IsEmpty();
    }

    CString GetFileNameLinkedTo() const
    {
        return m_FileNameLinkedTo;
    }

    void SetFileNameLinkedTo(CString value)
    {
        m_FileNameLinkedTo = value;
    }

    void ClearLinkedToFileName()
    {
        m_FileNameLinkedTo.Empty();
    }

    void SetPackageName(const CString value)
    {
        ZBSymbol::SetSymbolName(value);
    }

    const CString GetPackageName()
    {
        return ZBSymbol::GetSymbolName();
    }

    bool GetDisplayPreview() const
    {
        return m_DisplayPreview;
    }

    void SetDisplayPreview(bool value)
    {
        m_DisplayPreview = value;
    }

    virtual void OnDraw(CDC* pDC);

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return CODSymbolComponent::AddRef();
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        return CODSymbolComponent::Release();
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de d�finir si le symbole est un paquet.
    virtual BOOL IsPackage()
    {
        return TRUE;
    }

    // Creation of a new child model
    virtual BOOL CreateEmptyChildModel(CODModel* pParent);

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    virtual BOOL OnDoubleClick();

protected:

    virtual void AdjustElementPosition();

private:

    // The model for the canvas. The model holds all information about 
    // the canvas, while the viewport actually displays it.
    CRect                    m_CommentRect;
    CPoint                    m_LinkedToFileBitmapPosition;
    bool                    m_DisplayPreview;

    // Used to link the package to a file name
    CString                    m_FileNameLinkedTo;
    PSS_ProcessGraphModelDoc*    m_pPackageDoc;

    // Bitmap resource
    static PSS_Bitmap          m_LinkedToFileBitmap;
};

inline int ZBBPPackageSymbol::GetRightSubMenu() const
{
    return 9;
}

inline int ZBBPPackageSymbol::GetIconIndex() const
{
    return (IsLocal()) ? 11 : 19;
}

#endif
