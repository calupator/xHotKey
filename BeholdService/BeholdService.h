/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 05 17:59:10 2016
 */
/* Compiler settings for D:\Projects\BeholdService\BeholdService.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __BeholdService_h__
#define __BeholdService_h__

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBeholderRC_INTERFACE_DEFINED__
#define __IBeholderRC_INTERFACE_DEFINED__

/* interface IBeholderRC */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBeholderRC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3CABF23-7E52-4995-9927-605B1E8DB0E5")
    IBeholderRC : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /*[in]*/ ULONG index,
			/* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG __RPC_FAR *count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run(
            /*[in]*/ BSTR *bcstr,
            /* [out, retval] */ VARIANT_BOOL __RPC_FAR *succes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectCard( 
            /* [in] */ ULONG __RPC_FAR *index,
            /* [out, retval] */ VARIANT_BOOL __RPC_FAR *succes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemote( 
            /* [retval][out] */ ULONG __RPC_FAR *code) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRemoteEx( 
            /* [retval][out] */ ULONG __RPC_FAR *code) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBeholderRCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBeholderRC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBeholderRC __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBeholderRC __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBeholderRC __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBeholderRC __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBeholderRC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBeholderRC __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IBeholderRC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IBeholderRC __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IBeholderRC __RPC_FAR * This,
            BSTR bcstr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectCard )( 
            IBeholderRC __RPC_FAR * This,
            /* [in] */ long __RPC_FAR *index,
            /* [out] */ long __RPC_FAR *succes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRemote )( 
            IBeholderRC __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *code);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRemoteEx )( 
            IBeholderRC __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *code);
        
        END_INTERFACE
    } IBeholderRCVtbl;

    interface IBeholderRC
    {
        CONST_VTBL struct IBeholderRCVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBeholderRC_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBeholderRC_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBeholderRC_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBeholderRC_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBeholderRC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBeholderRC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBeholderRC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBeholderRC_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IBeholderRC_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IBeholderRC_Run(This,bcstr)	\
    (This)->lpVtbl -> Run(This,bcstr)

#define IBeholderRC_SelectCard(This,index,succes)	\
    (This)->lpVtbl -> SelectCard(This,index,succes)

#define IBeholderRC_GetRemote(This,code)	\
    (This)->lpVtbl -> GetRemote(This,code)

#define IBeholderRC_GetRemoteEx(This,code)	\
    (This)->lpVtbl -> GetRemoteEx(This,code)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBeholderRC_get_Name_Proxy( 
    IBeholderRC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBeholderRC_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBeholderRC_get_Count_Proxy( 
    IBeholderRC __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBeholderRC_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBeholderRC_Run_Proxy( 
    IBeholderRC __RPC_FAR * This,
    BSTR bcstr);


void __RPC_STUB IBeholderRC_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBeholderRC_SelectCard_Proxy( 
    IBeholderRC __RPC_FAR * This,
    /* [in] */ long __RPC_FAR *index,
    /* [out] */ long __RPC_FAR *succes);


void __RPC_STUB IBeholderRC_SelectCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBeholderRC_GetRemote_Proxy( 
    IBeholderRC __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *code);


void __RPC_STUB IBeholderRC_GetRemote_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBeholderRC_GetRemoteEx_Proxy( 
    IBeholderRC __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *code);


void __RPC_STUB IBeholderRC_GetRemoteEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBeholderRC_INTERFACE_DEFINED__ */



#ifndef __BEHOLDSERVICELib_LIBRARY_DEFINED__
#define __BEHOLDSERVICELib_LIBRARY_DEFINED__

/* library BEHOLDSERVICELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BEHOLDSERVICELib;

EXTERN_C const CLSID CLSID_BeholderRC;

#ifdef __cplusplus

class DECLSPEC_UUID("BF7C066C-904C-447E-A457-48B43F9D7959")
BeholderRC;
#endif
#endif /* __BEHOLDSERVICELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
