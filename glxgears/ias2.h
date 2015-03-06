// INTEL CONFIDENTIAL
// Copyright 2013-2015 Intel Corporation All Rights Reserved.
//
// The source code contained or described herein and all documents related to the 
// source code ("Material") are owned by Intel Corporation or its suppliers or 
// licensors. Title to the Material remains with Intel Corporation or its 
// suppliers and licensors. The Material may contain trade secrets and 
// proprietary and confidential information of Intel Corporation and its 
// suppliers and licensors, and is protected by worldwide copyright and trade 
// secret laws and treaty provisions. No part of the Material may be used, copied,
// reproduced, modified, published, uploaded, posted, transmitted, distributed, or
// disclosed in any way without Intel’s prior express written permission. 
//
// No license under any patent, copyright, trade secret or other intellectual 
// property right is granted to or conferred upon you by disclosure or delivery of
// the Materials, either expressly, by implication, inducement, estoppel or 
// otherwise. Any license under such intellectual property rights must be express 
// and approved by Intel in writing.
//
// Unless otherwise agreed by Intel in writing, you may not remove or alter this 
// notice or any other notice embedded in Materials by Intel or Intel’s suppliers 
// or licensors in any way.

#pragma once

#ifdef IAS2_EXPORTS
	#define IAS2_API  extern "C" __declspec(dllexport)
#else
	#define IAS2_API  extern "C" __declspec(dllimport)
	#ifndef IAS2_NOLIB
		#pragma comment(lib, "ias2.lib")
	#endif
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define IAS_ERROR_BASE 0x200

#define IAS_NO_OPTIN (IAS_ERROR_BASE+1)
#define S_NO_OPTIN MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_ITF,IAS_NO_OPTIN)

#define IAS_OPTOUT (IAS_ERROR_BASE+2)
#define S_OPTOUT MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_ITF,IAS_OPTOUT)

#define IAS_DISABLED_BY_POLICY (IAS_ERROR_BASE+10)
#define E_DISABLED_BY_POLICY MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,IAS_DISABLED_BY_POLICY)

#define IAS_DISABLED (IAS_ERROR_BASE+11)
#define E_DISABLED MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,IAS_DISABLED)

#define IAS_INFINITE INT_MAX

typedef void* ias_session_t;
typedef HRESULT ias_error_t;

IAS2_API ias_error_t HasSystemConsentFeature(BOOL *consent_feature);

IAS2_API ias_error_t Initialize(
	const wchar_t* app_name, 
	const wchar_t* app_version, 
	const wchar_t* telemetry_id,
	const wchar_t* options,			// nullptr ok
	const wchar_t* store_folder);	// nullptr ok

IAS2_API ias_error_t InitializeEx(
	const wchar_t* app_name,
	const wchar_t* app_version,
	const wchar_t* telemetry_id,
	const wchar_t* options,					// nullptr ok
	const wchar_t* store_folder,			// nullptr ok
	const wchar_t* const * const keys,		// nullptr ok
	const wchar_t* const * const values,	// nullptr ok
	size_t segs);

IAS2_API ias_error_t Deinitialize();

IAS2_API ias_error_t BeginSession(
	ias_session_t* session_handle,
	const wchar_t *name);					// nullptr ok

IAS2_API ias_error_t BeginSessionEx(
	ias_session_t* session_handle,
	const wchar_t *name,
	const wchar_t* const * const keys,
	const wchar_t* const * const values,
	size_t segs);

IAS2_API ias_error_t EndSession(
	ias_session_t session_handle);

IAS2_API ias_error_t RecordEvent(
	ias_session_t session_handle,
	const wchar_t* const name, 
	int count, 
	double sum);

IAS2_API ias_error_t RecordEventEx(
	ias_session_t session_handle,
	const wchar_t* const name, 
	int count, 
	double sum, 
	const wchar_t* const * const keys, 
	const wchar_t* const * const values, 
	size_t segs);
