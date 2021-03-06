// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLCOMMEM_H__
#define __ATLCOMMEM_H__

#pragma once

#ifndef __ATLMEM_H__
	#error ATLComMem.h requires atlmem.h to be included first
#endif	// __ATLMEM_H__

#include <atlcomcli.h>

#pragma pack(push,_ATL_PACKING)
namespace ATL
{

class CComHeap :
	public IAtlMemMgr
{
// IAtlMemMgr
public:
	_Ret_opt_bytecap_(nBytes) virtual void* Allocate(_In_ size_t nBytes) throw()
	{
#ifdef _WIN64
		if( nBytes > INT_MAX )
		{
			return( NULL );
		}
#endif
		return( ::CoTaskMemAlloc( ULONG( nBytes ) ) );
	}
	virtual void Free(_In_opt_ void* p) throw()
	{
		::CoTaskMemFree( p );
	}
	_Ret_opt_bytecap_(nBytes) virtual void* Reallocate(
		_In_opt_ void* p,
		_In_ size_t nBytes) throw()
	{
#ifdef _WIN64
		if( nBytes > INT_MAX )
		{
			return( NULL );
		}
#endif
		return( ::CoTaskMemRealloc( p, ULONG( nBytes ) ) );
	}
	virtual size_t GetSize(_In_opt_ void* p) throw()
	{
		CComPtr< IMalloc > pMalloc;

		HRESULT hr = ::CoGetMalloc( 1, &pMalloc );
		if (FAILED(hr))
			return 0;

		return( pMalloc->GetSize( p ) );
	}
};

/////////////////////////////////////////////////////////////////////////////
// OLE task memory allocation support

inline LPWSTR AtlAllocTaskWideString(
	_In_opt_z_ LPCWSTR lpszString) throw()
{
	if (lpszString == NULL)
	{
		return NULL;
	}
	UINT nSize = (UINT)((wcslen(lpszString)+1) * sizeof(WCHAR));
	LPWSTR lpszResult = (LPWSTR)CoTaskMemAlloc(nSize);
	if (lpszResult == NULL)
	{
		return NULL;
	}

	if(0 != memcpy_s(lpszResult, nSize, lpszString, nSize))
	{
		CoTaskMemFree(lpszResult);
		return NULL;
	}

	return lpszResult;
}

inline LPWSTR AtlAllocTaskWideString(
	_In_opt_z_ LPCSTR lpszString) throw()
{
	if (lpszString == NULL)
		return NULL;
	UINT nLen = lstrlenA(lpszString)+1;
	LPWSTR lpszResult = (LPWSTR)::ATL::AtlCoTaskMemCAlloc(nLen, static_cast<ULONG>(sizeof(WCHAR)));
	if (lpszResult != NULL)
	{
		int nRet = MultiByteToWideChar(CP_ACP, 0, lpszString, -1, lpszResult, nLen);
		ATLASSERT(nRet != 0);
		if (nRet == 0)
		{
			CoTaskMemFree(lpszResult);
			lpszResult = NULL;
		}
	}
	return lpszResult;
}

inline LPSTR AtlAllocTaskAnsiString(
	_In_opt_z_ LPCWSTR lpszString) throw()
{
	if (lpszString == NULL)
		return NULL;
	UINT nBytes = (UINT)((wcslen(lpszString)+1)*2);
	LPSTR lpszResult = (LPSTR)CoTaskMemAlloc(nBytes);
	if (lpszResult != NULL)
	{
		int nRet = WideCharToMultiByte(CP_ACP, 0, lpszString, -1, lpszResult, nBytes, NULL, NULL);
		ATLASSERT(nRet != 0);
		if (nRet == 0)
		{
			CoTaskMemFree(lpszResult);
			lpszResult = NULL;
		}
	}
	return lpszResult;
}

inline LPSTR AtlAllocTaskAnsiString(
	_In_opt_z_ LPCSTR lpszString) throw()
{
	if (lpszString == NULL)
	{
		return NULL;
	}
	UINT nSize = lstrlenA(lpszString)+1;
	LPSTR lpszResult = (LPSTR)CoTaskMemAlloc(nSize);
	if (lpszResult == NULL)
	{
		return NULL;
	}

	if(0 != memcpy_s(lpszResult, nSize, lpszString, nSize))
	{
		CoTaskMemFree(lpszResult);
		return NULL;
	}
	return lpszResult;
}

#ifdef _UNICODE
	#define AtlAllocTaskString(x) AtlAllocTaskWideString(x)
#else
	#define AtlAllocTaskString(x) AtlAllocTaskAnsiString(x)
#endif

#define AtlAllocTaskOleString(x) AtlAllocTaskWideString(x)

}	// namespace ATL
#pragma pack(pop)

#endif	// __ATLCOMMEM_H__
