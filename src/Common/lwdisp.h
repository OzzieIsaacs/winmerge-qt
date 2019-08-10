/* File:	lwdisp.h - light weight dispatch API
 * Author:	Jochen Tucht 2003/01/09
 *			Copyright (C) 2003 herbert dahm datensysteme GmbH
 *
 * Declaration file for lwdisp.c
 *
 * Purpose:	- Create windows scripting objects (scriptlets)
 *			- Invoke methods and access properties
 *			- Implement callback interfaces to be invoked by scriptlets
 *
 * License:	THIS FILE CONTAINS FREE SOURCE CODE. IT IS PROVIDED *AS IS*, WITHOUT
 *			WARRANTY OF ANY KIND. YOU MAY USE IT AT YOUR OWN RISK, AS LONG AS
 *			YOU KEEP IT IN A SEPARATE FILE AND PRESERVE THIS COMMENT.
 *			CHANGES MUST BE RECORDED IN THE MODIFICATION HISTORY BELOW SO THERE
 *			IS EVIDENCE THAT THE FILE DIFFERS FROM EARLIER RELEASES. THE LEVEL
 *			OF DETAIL IS UP TO YOU. YOU MAY SET THE BY: ENTRY TO "NOBODY@ALL"
 *			IF YOU DON'T WANT TO EXPOSE YOUR NAME. SUBSEQUENT CHANGES MAY BE
 *			REFLECTED BY A SINGLE RECORD CARRYING THE DATE OF THE LATEST CHANGE.
 *

DATE:		BY:					DESCRIPTION:
==========	==================	================================================
2003/11/28	Laoran 				      header and RCS ID
*/
#pragma once

#ifdef __cplusplus
extern "C"{
#endif 

#ifdef _MSC_VER
#define UNUSED_ARG(ARG) ARG
#elif defined(__GNUC__)
#define UNUSED_ARG(ARG) ARG
#else
#define UNUSED_ARG(ARG)
#endif

// macros for use with ValidateArgs()

// parameter types: by value VTs
#define VTS_I2              "\x02"      // a 'short'
#define VTS_I4              "\x03"      // a 'long'
#define VTS_R4              "\x04"      // a 'float'
#define VTS_R8              "\x05"      // a 'double'
#define VTS_CY              "\x06"      // a 'CY' or 'CY*'
#define VTS_DATE            "\x07"      // a 'DATE'
#define VTS_WBSTR           "\x08"      // an 'LPCOLESTR'
#define VTS_DISPATCH        "\x09"      // an 'IDispatch*'
#define VTS_SCODE           "\x0A"      // an 'SCODE'
#define VTS_BOOL            "\x0B"      // a 'BOOL'
#define VTS_VARIANT         "\x0C"      // a 'const VARIANT&' or 'VARIANT*'
#define VTS_UNKNOWN         "\x0D"      // an 'IUnknown*'
#if defined(_UNICODE) || defined(OLE2ANSI)
	#define VTS_BSTR            VTS_WBSTR// an 'LPCOLESTR'
	#define VT_BSTRT            VT_BSTR
#else
	#define VTS_BSTR            "\x0E"  // an 'LPCSTR'
	#define VT_BSTRA            14
	#define VT_BSTRT            VT_BSTRA
#endif
#ifndef VTS_UI1
#define VTS_UI1             "\x0F"      // a 'BYTE'
#endif

// parameter types: by reference VTs
#define VTS_PI2             "\x42"      // a 'short*'
#define VTS_PI4             "\x43"      // a 'long*'
#define VTS_PR4             "\x44"      // a 'float*'
#define VTS_PR8             "\x45"      // a 'double*'
#define VTS_PCY             "\x46"      // a 'CY*'
#define VTS_PDATE           "\x47"      // a 'DATE*'
#define VTS_PBSTR           "\x48"      // a 'BSTR*'
#define VTS_PDISPATCH       "\x49"      // an 'IDispatch**'
#define VTS_PSCODE          "\x4A"      // an 'SCODE*'
#define VTS_PBOOL           "\x4B"      // a 'VARIANT_BOOL*'
#define VTS_PVARIANT        "\x4C"      // a 'VARIANT*'
#define VTS_PUNKNOWN        "\x4D"      // an 'IUnknown**'

// special VT_ and VTS_ values
#define VTS_NONE            NULL        // used for members with 0 params

// macros for use with wsprintfA(), wsprintfW()

#ifdef _UNICODE
#define WVA_TSTR L"%s"
#define AVA_TSTR "%S"
#define TVA_BSTR L"%s"
#else
#define WVA_TSTR L"%S"
#define AVA_TSTR "%s"
#define TVA_BSTR "%S"
#endif

// misc. macros

#define DIMOF(a) (sizeof(a)/sizeof(*a))


/**
 * @param source : if 0, create an object of the class registered as *progid*
 * @param progid : if 0, create an object from file *source*
 * If both source and progid defined, ask *source* to create an object of class *progid*
 */
LPDISPATCH NTAPI CreateDispatchBySource(LPCTSTR source, LPCWSTR progid);

/**
 * @brief invoke helper (__stdcall)
 *
 * @note Free all variants passed to it (except ByRef ones) 
 */
STDAPI invokeV(LPDISPATCH, VARIANT *, DISPID, LPCCH, VARIANT *);
/**
 * @brief invoke helper (by ordinal)
 *
 * @note Free all variants passed to it (except ByRef ones) 
 */
STDAPIV invokeA(LPDISPATCH, VARIANT *, DISPID, LPCCH, VARIANT *);
/**
 * @brief invoke helper (by function name)
 *
 * @note Free all variants passed to it (except ByRef ones) 
 */
STDAPIV invokeW(LPDISPATCH, VARIANT *, LPCOLESTR, LPCCH, VARIANT *);

// macros for use with invoke*()
#define opFxn &((PCH)(DISPATCH_METHOD<<8))
#define opPut &((PCH)(DISPATCH_PROPERTYPUT<<8))
#define opGet &((PCH)(DISPATCH_PROPERTYGET<<8))
#define opSet &((PCH)(DISPATCH_PROPERTYPUTREF<<8))

// ::invokeW(piDispatch, LODD(Foo), ...) will fail silently if the interface
// lacks the requested method or property
#define LODD(NAME) ((BSTR)((PCH)L###NAME+1))

// convert given arguments to requested types
STDAPI ValidateArgs(VARIANT *argv, UINT argc, LPCCH pvt);

// in place conversion of BSTR to LPCCH
// IN PLACE TRANSFORMATION OF WCHAR TO CHAR IS NOT CORRECT
/*
PCH NTAPI B2A(BSTR);
LPCTSTR NTAPI B2T(BSTR);
*/

// callback interface related declarations

typedef HRESULT(NTAPI*LWDispFxn)
		(PVOID, HRESULT, VARIANT *, VARIANT *, UINT, EXCEPINFO *);

STDAPI	LWDefProc
		(PVOID, HRESULT, VARIANT *, VARIANT *, UINT, EXCEPINFO *);

struct LWDispRef
{
	LPCWSTR pwcName;
	LWDispFxn pfnProc;
};

struct LWDispatch;

struct LWDispVtbl
{
	HRESULT(STDMETHODCALLTYPE*QueryInterface)( 
		struct LWDispatch *This,
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void **ppvObject);
	ULONG(STDMETHODCALLTYPE*AddRef)(struct LWDispatch *This);
	ULONG(STDMETHODCALLTYPE*Release)(struct LWDispatch *This);
	HRESULT(STDMETHODCALLTYPE*GetTypeInfoCount)( 
		struct LWDispatch *This,
		/* [out] */ UINT *pctinfo);
	HRESULT(STDMETHODCALLTYPE*GetTypeInfo)( 
		struct LWDispatch *This,
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ ITypeInfo **ppTInfo);
	HRESULT(STDMETHODCALLTYPE*GetIDsOfNames)( 
		struct LWDispatch *This,
		/* [in] */ REFIID riid,
		/* [size_is][in] */ LPOLESTR *rgszNames,
		/* [in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ DISPID *rgDispId);
	HRESULT(STDMETHODCALLTYPE*Invoke)( 
		struct LWDispatch *This,
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS *pDispParams,
		/* [out] */ VARIANT *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);
};

struct LWDispatch
{
	const struct LWDispVtbl *lpVtbl;
	void *target;
	const struct LWDispMap *map;
	ULONG refc;
};

const struct LWDispVtbl *NTAPI LWDispSubclass(struct LWDispVtbl *);

IDispatch *NTAPI LWDispatch(void *target, const void *disp_map,
							const struct LWDispVtbl *, struct LWDispatch *);

// functions to build VARIANT arguments from various data types

// LWArg for objects
VARIANT NTAPI LWArg(LPDISPATCH);

// LWArg for wide and ansi character strings
VARIANT NTAPI LWArgW(LPCWSTR);
VARIANT NTAPI LWArgA(LPCSTR);

#ifdef _UNICODE
#define LWArgT LWArgW
#else
#define LWArgT LWArgA
#endif
// Generic LWArg for everything that does not involve dynamic allocation or
// reference counting. Use LWVT macro to compute the UINT argument.

VARIANT NTAPI LWArgV(UINT, ...);
#define LWVT(t) (sizeof(V_##t((VARIANT*)0)) << 8 | VT_##t)

// assign variant type and data in one statement
#define V_VAR(r,t) V_VT(r)=VT_##t,V_##t(r)

#ifdef __cplusplus
}
#endif 

#ifdef __cplusplus

// LWDispMap implementation macros for C++

#define	DISPMAP_FXN(NAME) \
	HRESULT *_##NAME, NAME(HRESULT, VARIANT *, VARIANT *, UINT, EXCEPINFO *); \
	static HRESULT NTAPI NAME##_(PVOID p, HRESULT sc, VARIANT *ret, VARIANT *argv, UINT argc, EXCEPINFO *e) \
	{ return ((P*)p)->NAME(sc, ret, argv, argc, e); }

#define	DISPMAP_REF(NAME) {L###NAME,NAME##_}

#define DISPMAP(T) \
	enum {COUNT = (sizeof(P) - sizeof(T)) / sizeof(HRESULT*)}; \
	static const struct\
	{ \
		LWDispFxn pfnProc; \
		int count; \
		struct LWDispRef ref[COUNT]; \
	} map =

// VARIANT derivative to hold a result value

struct LWRet: public VARIANT
{
	LWRet() {VariantInit(this);}
~	LWRet() {VariantClear(this);}
};

#else

// Sorry, no extra support for plain old C...

#endif
