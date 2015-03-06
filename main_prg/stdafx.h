// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

/* Disable warnings related to the use of inet_ntoa() and friends */
#if defined(_MSC_PT_VER) && (_MSC_PT_VER >= 120)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <stdlib.h>


// TODO: reference additional headers your program requires here
