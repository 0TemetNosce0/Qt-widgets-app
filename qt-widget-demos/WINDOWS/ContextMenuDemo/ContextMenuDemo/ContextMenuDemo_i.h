

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Apr 28 16:55:18 2015
 */
/* Compiler settings for ContextMenuDemo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ContextMenuDemo_i_h__
#define __ContextMenuDemo_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDisplayNamesCtxMenuShellExt_FWD_DEFINED__
#define __IDisplayNamesCtxMenuShellExt_FWD_DEFINED__
typedef interface IDisplayNamesCtxMenuShellExt IDisplayNamesCtxMenuShellExt;
#endif 	/* __IDisplayNamesCtxMenuShellExt_FWD_DEFINED__ */


#ifndef __DisplayNamesCtxMenuShellExt_FWD_DEFINED__
#define __DisplayNamesCtxMenuShellExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayNamesCtxMenuShellExt DisplayNamesCtxMenuShellExt;
#else
typedef struct DisplayNamesCtxMenuShellExt DisplayNamesCtxMenuShellExt;
#endif /* __cplusplus */

#endif 	/* __DisplayNamesCtxMenuShellExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDisplayNamesCtxMenuShellExt_INTERFACE_DEFINED__
#define __IDisplayNamesCtxMenuShellExt_INTERFACE_DEFINED__

/* interface IDisplayNamesCtxMenuShellExt */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDisplayNamesCtxMenuShellExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE48C9C2-D068-40F2-9C9E-EB5DB709A092")
    IDisplayNamesCtxMenuShellExt : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDisplayNamesCtxMenuShellExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayNamesCtxMenuShellExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayNamesCtxMenuShellExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayNamesCtxMenuShellExt * This);
        
        END_INTERFACE
    } IDisplayNamesCtxMenuShellExtVtbl;

    interface IDisplayNamesCtxMenuShellExt
    {
        CONST_VTBL struct IDisplayNamesCtxMenuShellExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayNamesCtxMenuShellExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayNamesCtxMenuShellExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayNamesCtxMenuShellExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayNamesCtxMenuShellExt_INTERFACE_DEFINED__ */



#ifndef __ContextMenuDemoLib_LIBRARY_DEFINED__
#define __ContextMenuDemoLib_LIBRARY_DEFINED__

/* library ContextMenuDemoLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ContextMenuDemoLib;

EXTERN_C const CLSID CLSID_DisplayNamesCtxMenuShellExt;

#ifdef __cplusplus

class DECLSPEC_UUID("09EC6C12-BF1B-4B30-A304-8F7EED67CB71")
DisplayNamesCtxMenuShellExt;
#endif
#endif /* __ContextMenuDemoLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


