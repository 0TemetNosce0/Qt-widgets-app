// DisplayNamesCtxMenuShellExt.h : Declaration of the CDisplayNamesCtxMenuShellExt

#pragma once
#include "resource.h"       // main symbols



#include "ContextMenuDemo_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CDisplayNamesCtxMenuShellExt

class ATL_NO_VTABLE CDisplayNamesCtxMenuShellExt :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CDisplayNamesCtxMenuShellExt, &CLSID_DisplayNamesCtxMenuShellExt>,
    public IShellExtInit,
    public IContextMenu
{
public:
    CDisplayNamesCtxMenuShellExt():
        _cmdDisplayFileNames(0),
        _helpText(L"(help) Display file names using IContextMenu"),
        _menuText(L"(menu) Display names using IContextMenu with ATL")
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_DISPLAYNAMESCTXMENUSHELLEXT)

DECLARE_NOT_AGGREGATABLE(CDisplayNamesCtxMenuShellExt)

BEGIN_COM_MAP(CDisplayNamesCtxMenuShellExt)
    COM_INTERFACE_ENTRY(IShellExtInit)
    COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()


    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

public:

    STDMETHODIMP Initialize(
        PCIDLIST_ABSOLUTE pidlFolder, 
        IDataObject *pdtobj, 
        HKEY hkeyProgID);

    STDMETHODIMP GetCommandString(
        UINT_PTR idCmd,
        UINT uFlags,
        UINT *pwReserved,
        LPSTR pszName,
        UINT cchMax);

    STDMETHODIMP InvokeCommand(
        LPCMINVOKECOMMANDINFO pici);

    STDMETHODIMP QueryContextMenu(
        HMENU hMenu,
        UINT indexMenu,
        UINT idCmdFirst,
        UINT idCmdLast,
        UINT uFlags);

private:
    std::vector<std::wstring> _selectedFiles;

    const UINT_PTR _cmdDisplayFileNames;

    std::wstring _helpText;

    std::wstring _menuText;

    void OutputFileNamesToDebugger();

};

OBJECT_ENTRY_AUTO(__uuidof(DisplayNamesCtxMenuShellExt), CDisplayNamesCtxMenuShellExt)
