// DisplayNamesCtxMenuShellExt.cpp : Implementation of CDisplayNamesCtxMenuShellExt

#include "stdafx.h"
#include "DisplayNamesCtxMenuShellExt.h"


// CDisplayNamesCtxMenuShellExt

#define COM_EXCEPTION_GUARD_BEGIN try {
#define COM_EXCEPTION_GUARD_END } catch (const CAtlException& ex) {		\
    return static_cast<HRESULT>(ex);	\
                                } catch (const std::bad_alloc &) {		\
                                return E_OUTOFMEMORY;				\
                                } catch (const std::exception &) {		\
                                return E_FAIL;						\
                                }

class FileEnumFromDataObject
{
public:

    explicit FileEnumFromDataObject(IDataObject* pdtobj): 
    _hDrop(nullptr),
        _fileCount(0)
    {
        // format to request hdrop data from the data object
        FORMATETC fmte = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

        memset(&_stgm, 0, sizeof(_stgm));
        _stgm.tymed = TYMED_HGLOBAL;

        // retrieve hdrop data from source data object
        if (FAILED( pdtobj->GetData(&fmte, &_stgm)))
        {
            AtlThrow(E_INVALIDARG);
        }

        // get point to the file names data
        _hDrop = reinterpret_cast<HDROP>(::GlobalLock(_stgm.hGlobal));
        if (! _hDrop) AtlThrow(E_INVALIDARG);

        _fileCount = ::DragQueryFile(_hDrop, 0xFFFFFFFF, nullptr, 0);
    }

    ~FileEnumFromDataObject()
    {
        if (_hDrop)
        {
            ::GlobalUnlock(_stgm.hGlobal);
            ::ReleaseStgMedium(&_stgm);
        }
    }

    UINT FileCount() const { return _fileCount; }

    std::wstring FileAt(UINT index) const 
    {
        wchar_t filenameBuffer[MAX_PATH];

        UINT copied = ::DragQueryFile(_hDrop, index, filenameBuffer, _countof(filenameBuffer));

        if ( copied > 0 && copied < MAX_PATH)
        {
            return std::wstring(filenameBuffer, copied);
        }

        return std::wstring();
    }

private:
    FileEnumFromDataObject(const FileEnumFromDataObject &);
    FileEnumFromDataObject& operator=(const FileEnumFromDataObject &);
    HDROP _hDrop;			// hdrop from IDataObject
    STGMEDIUM _stgm;		// storage medium (global memory handle)
    UINT _fileCount;
};


STDMETHODIMP CDisplayNamesCtxMenuShellExt::Initialize(
    PCIDLIST_ABSOLUTE pidlFolder,
    IDataObject* pdtobj,
    HKEY hkeyProgId)
{
    COM_EXCEPTION_GUARD_BEGIN

        ::MessageBox(NULL, L"DisplayNamesContextMenu initialize", L"IContextMenuDemo", MB_OK);

    FileEnumFromDataObject files(pdtobj);
    _selectedFiles.clear();

    for (auto i = 0u; i < files.FileCount(); ++i) {
        auto filename = files.FileAt(i);
        if (! filename.empty()) 
        {
            _selectedFiles.push_back(filename);
        }
    }
    return _selectedFiles.size() != 0 ? S_OK : E_INVALIDARG;

    COM_EXCEPTION_GUARD_END
}
STDMETHODIMP CDisplayNamesCtxMenuShellExt::GetCommandString(
    UINT_PTR idCmd,
    UINT uFlags,
    UINT *pwReserved,
    LPSTR pszName,
    UINT cchMax) 
{
    COM_EXCEPTION_GUARD_BEGIN

        if (idCmd != _cmdDisplayFileNames) return E_INVALIDARG;

    if (uFlags != GCS_HELPTEXTW) return E_INVALIDARG;

    auto hr = ::StringCchCopy(
        reinterpret_cast<PWSTR>(pszName), 
        cchMax, 
        _helpText.c_str());
    return hr;

    COM_EXCEPTION_GUARD_END
}

STDMETHODIMP CDisplayNamesCtxMenuShellExt::InvokeCommand(
    LPCMINVOKECOMMANDINFO pici)
{
    COM_EXCEPTION_GUARD_BEGIN

        // not using verbs here
        if (HIWORD(pici->lpVerb) != 0) return E_INVALIDARG;

    // extract command index from the low word
    const UINT_PTR cmdIndex = LOWORD(pici->lpVerb);

    // check the command index corresponds to our command ID
    if (cmdIndex != _cmdDisplayFileNames)
    {
        return E_INVALIDARG;
    }
    OutputFileNamesToDebugger();
    return S_OK;
    COM_EXCEPTION_GUARD_END

}

STDMETHODIMP CDisplayNamesCtxMenuShellExt::QueryContextMenu(
    HMENU hMenu,
    UINT indexMenu,
    UINT idCmdFirst,
    UINT idCmdLast,
    UINT uFlags)
{
    COM_EXCEPTION_GUARD_BEGIN

    if (uFlags & CMF_DEFAULTONLY) return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);

    ::InsertMenu(hMenu, 
        indexMenu, 
        MF_STRING | MF_BYPOSITION | MF_DISABLED,
        idCmdFirst + _cmdDisplayFileNames, 
        _menuText.c_str());

    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, static_cast<USHORT>(_cmdDisplayFileNames + 1));
    COM_EXCEPTION_GUARD_END
}


void CDisplayNamesCtxMenuShellExt::OutputFileNamesToDebugger() {
    std::wstring message;
    for (const auto& filename : _selectedFiles)
    {
        message += filename;
        message += L", ";
    }
    ::MessageBox(NULL, message.c_str(), L"(IContextMenuDemo) Selected files", MB_OK);
}