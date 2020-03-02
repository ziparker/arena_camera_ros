// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#if (defined _WIN32 || defined _WIN64)
#include <windows.h>
#include <ppl.h>
#endif



#include "Exceptions.h"
#include "GTestAPI.h"
#include "GenTL.h"
#include "GenTLCustom.h"
#include "ArenaApi.h"

// TODO: reference additional headers your program requires here
