// dllmain.h : Declaration of module class.

class CContextMenuDemoModule : public ATL::CAtlDllModuleT< CContextMenuDemoModule >
{
public :
    DECLARE_LIBID(LIBID_ContextMenuDemoLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CONTEXTMENUDEMO, "{6A10AC17-C758-40D7-997A-134AB27EF319}")
};

extern class CContextMenuDemoModule _AtlModule;
