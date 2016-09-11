

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sun Sep 11 17:09:14 2016
 */
/* Compiler settings for .\BeholdService.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __BeholdService_i_h__
#define __BeholdService_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBeholderRC_FWD_DEFINED__
#define __IBeholderRC_FWD_DEFINED__
typedef interface IBeholderRC IBeholderRC;
#endif 	/* __IBeholderRC_FWD_DEFINED__ */


#ifndef __BeholderRC_FWD_DEFINED__
#define __BeholderRC_FWD_DEFINED__

#ifdef __cplusplus
typedef class BeholderRC BeholderRC;
#else
typedef struct BeholderRC BeholderRC;
#endif /* __cplusplus */

#endif 	/* __BeholderRC_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBeholderRC_INTERFACE_DEFINED__
#define __IBeholderRC_INTERFACE_DEFINED__

/* interface IBeholderRC */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBeholderRC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("274A76A7-C5D9-4BE8-9327-6D56F25D5AAB")
    IBeholderRC : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsInit( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ ULONG index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemote( 
            /* [retval][out] */ ULONG *code) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemoteEx( 
            /* [retval][out] */ ULONG *code) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR *bcstr,
            /* [retval][out] */ VARIANT_BOOL *succes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectCard( 
            /* [in] */ ULONG index,
            /* [retval][out] */ VARIANT_BOOL *succes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBeholderRCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBeholderRC * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBeholderRC * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBeholderRC * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBeholderRC * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBeholderRC * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBeholderRC * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBeholderRC * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IBeholderRC * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsInit )( 
            IBeholderRC * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IBeholderRC * This,
            /* [in] */ ULONG index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRemote )( 
            IBeholderRC * This,
            /* [retval][out] */ ULONG *code);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRemoteEx )( 
            IBeholderRC * This,
            /* [retval][out] */ ULONG *code);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            IBeholderRC * This,
            /* [in] */ BSTR *bcstr,
            /* [retval][out] */ VARIANT_BOOL *succes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectCard )( 
            IBeholderRC * This,
            /* [in] */ ULONG index,
            /* [retval][out] */ VARIANT_BOOL *succes);
        
        END_INTERFACE
    } IBeholderRCVtbl;

    interface IBeholderRC
    {
        CONST_VTBL struct IBeholderRCVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBeholderRC_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBeholderRC_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBeholderRC_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBeholderRC_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBeholderRC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBeholderRC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBeholderRC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBeholderRC_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IBeholderRC_get_IsInit(This,pVal)	\
    ( (This)->lpVtbl -> get_IsInit(This,pVal) ) 

#define IBeholderRC_get_Name(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,index,pVal) ) 

#define IBeholderRC_GetRemote(This,code)	\
    ( (This)->lpVtbl -> GetRemote(This,code) ) 

#define IBeholderRC_GetRemoteEx(This,code)	\
    ( (This)->lpVtbl -> GetRemoteEx(This,code) ) 

#define IBeholderRC_Run(This,bcstr,succes)	\
    ( (This)->lpVtbl -> Run(This,bcstr,succes) ) 

#define IBeholderRC_SelectCard(This,index,succes)	\
    ( (This)->lpVtbl -> SelectCard(This,index,succes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBeholderRC_INTERFACE_DEFINED__ */



#ifndef __BEHOLDSERVICELib_LIBRARY_DEFINED__
#define __BEHOLDSERVICELib_LIBRARY_DEFINED__

/* library BEHOLDSERVICELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BEHOLDSERVICELib;

EXTERN_C const CLSID CLSID_BeholderRC;

#ifdef __cplusplus

class DECLSPEC_UUID("1929458C-10F9-4E69-9679-6F9E1273ABE5")
BeholderRC;
#endif
#endif /* __BEHOLDSERVICELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


