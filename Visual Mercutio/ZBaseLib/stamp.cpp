/****************************************************************************
 * ==> PSS_Stamp -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file stamp generated by ProcessSoft             *
 *               applications                                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "Stamp.h"

 //---------------------------------------------------------------------------
 // PSS_Stamp
 //---------------------------------------------------------------------------
PSS_Stamp::PSS_Stamp() :
    m_DocumentFileType(IE_FT_FormDocument),
    m_FileType(IE_FD_DocumentType),
    m_DocumentDataType(IE_DT_Form),
    m_Stamp("ADSoft"),
    m_PublishVersion(0),
    m_InternalVersion(-1),
    m_ReadOnly(FALSE)
{}
//---------------------------------------------------------------------------
PSS_Stamp::PSS_Stamp(const PSS_Stamp& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Stamp::~PSS_Stamp()
{}
//---------------------------------------------------------------------------
const PSS_Stamp& PSS_Stamp::operator = (const PSS_Stamp& other)
{
    m_DocumentFileType      = other.m_DocumentFileType;
    m_FileType              = other.m_FileType;
    m_DocumentDataType      = other.m_DocumentDataType;
    m_Stamp                 = other.m_Stamp;
    m_Title                 = other.m_Title;
    m_Description           = other.m_Description;
    m_Template              = other.m_Template;
    m_AppModifier           = other.m_AppModifier;
    m_PublishUser           = other.m_PublishUser;
    m_InternalKey           = other.m_InternalKey;
    m_StampCreationDate     = other.m_StampCreationDate;
    m_StampModificationDate = other.m_StampModificationDate;
    m_PublishDate           = other.m_PublishDate;
    m_PublishVersion        = other.m_PublishVersion;
    m_InternalVersion       = other.m_InternalVersion;
    m_ReadOnly              = other.m_ReadOnly;
    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_Stamp& stamp)
{
    CString dummy;

    ar >> stamp.m_Stamp;
    ar >> stamp.m_InternalVersion;
    ar >> stamp.m_Title;
    ar >> stamp.m_Description;

    // in place of formula template
    if (Stamp.m_InternalVersion <= 11)
        ar >> dummy;

    ar >> stamp.m_Template;

    CTime time;

    // not yet in ZBDate
    if (stamp.m_InternalVersion < 14)
    {
        ar >> time;

        if (time.GetTime() >= 0)
            stamp.SetStampCreationDate(time);

        ar >> time;

        if (time.GetTime() >= 0)
            stamp.SetStampModificationDate(time);
    }
    else
    {
        ar >> stamp.m_StampCreationDate;
        ar >> stamp.m_StampModificationDate;
    }

    if (stamp.m_InternalVersion <= 11)
    {
        // in place of reserved 1 & 2
        ar >> dummy;
        ar >> dummy;
    }

    ar >> stamp.m_ProgramGenerator;

    WORD value;
    ar >> value;
    stamp.m_FileType = PSS_Stamp::IEFileTypeDefinition(value);

    if (stamp.m_InternalVersion >= 13)
    {
        ar >> stamp.m_PublishVersion;

        // not yet in ZBDate
        if (stamp.m_InternalVersion < 14)
        {
            ar >> time;

            if (time.GetTime() >= 0)
                stamp.SetPublishDate(time);
        }
        else
            ar >> stamp.m_PublishDate;

        ar >> stamp.m_PublishUser;
    }

    if (stamp.m_InternalVersion >= 14)
    {
        ar >> value;
        stamp.m_ReadOnly = BOOL(value);

        ar >> stamp.m_InternalKey;
        ar >> value;
        stamp.m_DocumentDataType = PSS_Stamp::IEDocumentDataType(value);
    }
    else
        stamp.m_ReadOnly = FALSE;

    if (stamp.m_InternalVersion >= 15)
    {
        ar >> value;
        stamp.m_DocumentFileType = PSS_Stamp::IEDocumentFileType(value);
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_Stamp& stamp)
{
    ar << stamp.m_Stamp;
    ar << stamp.m_InternalVersion;
    ar << stamp.m_Title;
    ar << stamp.m_Explanation;
    ar << stamp.m_Template;
    ar << stamp.m_StampCreationDate;
    ar << stamp.m_StampModificationDate;
    ar << stamp.m_ProgramGenerator;
    ar << WORD(stamp.m_FileType);
    ar << stamp.m_PublishVersion;
    ar << stamp.m_PublishDate;
    ar << stamp.m_PublishUser;
    ar << WORD(stamp.m_ReadOnly);
    ar << stamp.m_InternalKey;
    ar << WORD(stamp.m_DocumentDataType);
    ar << WORD(stamp.m_DocumentFileType);
    return ar;
}
//---------------------------------------------------------------------------
PSS_Stamp* PSS_Stamp::Clone() const
{
    std::unique_ptr<PSS_Stamp> pNewStamp(new PSS_Stamp(*this));
    return pNewStamp.release();
}
//---------------------------------------------------------------------------
BOOL PSS_Stamp::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    // create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    WORD stamp = 0;

    TRY
    {
        loadArchive >> stamp;
    }
    CATCH (CArchiveException, e)
    {
        return FALSE;
    }
    END_CATCH

    BOOL result = FALSE;

    // check if the stamp has been set correctly for next file generation
    if (stamp == 0xFFFF)
    {
        loadArchive >> *this;
        result = TRUE;
    }

    // close the archive
    loadArchive.Close();
    file.Close();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Stamp::WriteToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CFileStatus rStatus;

    // file is now opened, read the status
    if (!file.GetStatus(rStatus))
        return FALSE;

    // create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    WORD stamp = 0;

    TRY
    {
        loadArchive >> stamp;
    }
    CATCH(CArchiveException, e)
    {
        return FALSE;
    }
    END_CATCH

    BOOL result = FALSE;

    // check if the stamp has been set correctly for next file generation
    if (stamp == 0xFFFF)
    {
        PSS_Stamp dummyStamp;
        loadArchive >> dummyStamp;
        result = TRUE;
    }

    // allocate a new buffer with the file size
    void* pFileBuffer = std::malloc(std::size_t(rStatus.m_size));

    if (!pFileBuffer)
        return FALSE;

    // Clear the buffer
    std::memset(pFileBuffer, 0, std::size_t(rStatus.m_size));

    UINT effectiveSize = 0;

    TRY
    {
        // read the remaining information
        effectiveSize = loadArchive.Read(pFileBuffer, UINT(rStatus.m_size));
    }
    CATCH (CFileException, e)
    {
        if (pFileBuffer)
            delete pFileBuffer;

        // close the file and the archive
        loadArchive.Close();
        file.Close();

        return FALSE;
    }
    END_CATCH

    // close the file and the archive
    loadArchive.Close();
    file.Close();

    // write the new stamp
    if (!file.Open(fileName, CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    // create the save archive
    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument  = NULL;
    saveArchive.m_bForceFlat = FALSE;

    TRY
    {
        saveArchive << stamp;
    }
    CATCH (CArchiveException, e)
    {
        return FALSE;
    }
    END_CATCH

    // check if the stamp has been set correctly for next file generation
    if (stamp == 0xFFFF)
    {
        saveArchive << *this;
        result = TRUE;
    }

    TRY
    {
        // save the information
        saveArchive.Write(pFileBuffer, EffectiveSize);
    }
    CATCH (CFileException, e)
    {
        if (pFileBuffer)
            delete pFileBuffer;

        // close the file and the archive
        saveArchive.Close();
        file.Close();

        return FALSE;
    }
    END_CATCH

    saveArchive.Flush();

    // close the file and the archive
    saveArchive.Close();
    file.Close();

    // free the buffer
    if (pFileBuffer)
        std::free(pFileBuffer);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Stamp::IsInternalKeyEqualTo(const CString& key) const
{
    return m_InternalKey == Key;
}
//---------------------------------------------------------------------------
LONG PSS_Stamp::IncrementPublishVersionOfFile(const CString& fileName)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return -1;

    // increment the version
    ++m_PublishVersion;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return -1;

    return m_PublishVersion;
}
//---------------------------------------------------------------------------
LONG PSS_Stamp::DecrementPublishVersionOfFile(const CString& fileName)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return -1;

    // decrement the file version
    --m_PublishVersion;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return -1;

    return m_PublishVersion;
}
//---------------------------------------------------------------------------
LONG PSS_Stamp::GetPublishVersionOfFile(const CString fileName)
{
    // if file was read successfully, return the publish version
    if (ReadFromFile(fileName))
        return m_PublishVersion;

    // return an error
    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_Stamp::SetPublishVersionOfFile(const CString& fileName, LONG version)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return FALSE;

    // change version
    m_PublishVersion = Version;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return FALSE;

    return m_PublishVersion;
}
//---------------------------------------------------------------------------
