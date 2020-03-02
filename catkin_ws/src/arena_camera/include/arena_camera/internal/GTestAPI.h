#pragma once

#if defined(_WIN32) || defined(WIN64)
// Windows 32-bit and 64-bit
#ifdef _ARENA_UNIT_TEST_API

#ifdef _EXPORT_ARENA_UNIT_TEST_API

#pragma warning(disable : 4251) //needs to have dll-interface to be used by clients of class

#define ARENA_TEST_API __declspec(dllexport)

#else //if not _EXPORT_ARENA_UNIT_TEST_API

#define ARENA_TEST_API __declspec(dllimport)

#endif // end _EXPORT_ARENA_UNIT_TEST_API

#else //_ARENA_UNIT_TEST_API

#define ARENA_TEST_API

#endif //_ARENA_UNIT_TEST_API

#else //if not _WIN32 and WIN64

#define ARENA_TEST_API

#endif // end defined(_WIN32) || defined(WIN64)