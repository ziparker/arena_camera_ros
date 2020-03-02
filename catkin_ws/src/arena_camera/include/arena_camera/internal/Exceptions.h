#pragma once

#include "Base/GCException.h"

inline const char* __str(const char* str)
{
	return str;
}

inline const char* __str(std::string str)
{
	return str.c_str();
}

#define GEN_ERR "Unable to get error from GenTL layer."
#define GEN_SIZE 2048

// message strings
#define MSG(type, code, message, file, function) \
	(std::string(#type) + " (" + #code "): " + message + " (" + file + ", " + function + ")").c_str()

#define MSG_GENTL(type, code, message, file, function, gentl, gentlMessage) \
	(std::string(#type) + " (" + #code + "): " + __str(message) + " (" + file + ", " + function + "; GenTL::" + gentl + "); " + gentlMessage).c_str()

#define MSG_NO_CODE(type, message, file, function) \
	(std::string(#type) + ": " + __str(message) + " (" + file + ", " + function + ")").c_str()

// case statements
#define CASE(code, type, message, gentl, gentlMessage)                                                                                                      \
	case GenTL::code:                                                                                                                                       \
		throw GenICam::type(                                                                                                                                \
			(strcmp(gentl,"") == 0 ? MSG(type, code, message, __FILE__, __FUNCTION__) : MSG_GENTL(type, code, message, __FILE__, __FUNCTION__, gentl, gentlMessage)), \
			__FILE__,                                                                                                                                       \
			__LINE__);

#define GENTL_MSG                                                                \
	std::string gentlStr = "";                                                   \
	{                                                                            \
		size_t size = GEN_SIZE;                                                  \
		char pGentlMsg[GEN_SIZE];                                                \
		GenTL::GC_ERROR lastErr = GenTL::GC_ERR_SUCCESS;                         \
		GenTL::GC_ERROR err = GenTL::GCGetLastError(&lastErr, pGentlMsg, &size); \
		gentlStr = pGentlMsg;                                                    \
		if (err != GenTL::GC_ERR_SUCCESS)                                        \
		{                                                                        \
			gentlStr = GEN_ERR;                                                  \
		}                                                                        \
	}

// throws
#define THROW_DEFAULT(err, message, gentl)                                                                                                                        \
	GENTL_MSG;                                                                                                                                                    \
	switch (err)                                                                                                                                                  \
	{                                                                                                                                                             \
		CASE(GC_ERR_NOT_INITIALIZED, LogicalErrorException, message, gentl, gentlStr);                                                                            \
		CASE(GC_ERR_NOT_IMPLEMENTED, LogicalErrorException, message, gentl, gentlStr);                                                                            \
		CASE(GC_ERR_RESOURCE_IN_USE, LogicalErrorException, message, gentl, gentlStr);                                                                            \
		CASE(GC_ERR_ACCESS_DENIED, AccessException, message, gentl, gentlStr);                                                                                    \
		CASE(GC_ERR_INVALID_HANDLE, InvalidArgumentException, message, gentl, gentlStr);                                                                          \
		CASE(GC_ERR_INVALID_ID, InvalidArgumentException, message, gentl, gentlStr);                                                                              \
		CASE(GC_ERR_NO_DATA, RuntimeException, message, gentl, gentlStr);                                                                                         \
		CASE(GC_ERR_INVALID_PARAMETER, InvalidArgumentException, message, gentl, gentlStr);                                                                       \
		CASE(GC_ERR_IO, RuntimeException, message, gentl, gentlStr);                                                                                              \
		CASE(GC_ERR_TIMEOUT, TimeoutException, message, gentl, gentlStr);                                                                                         \
		CASE(GC_ERR_ABORT, RuntimeException, message, gentl, gentlStr);                                                                                           \
		CASE(GC_ERR_INVALID_BUFFER, InvalidArgumentException, message, gentl, gentlStr);                                                                          \
		CASE(GC_ERR_NOT_AVAILABLE, LogicalErrorException, message, gentl, gentlStr);                                                                              \
		CASE(GC_ERR_INVALID_ADDRESS, InvalidArgumentException, message, gentl, gentlStr);                                                                         \
		CASE(GC_ERR_BUFFER_TOO_SMALL, InvalidArgumentException, message, gentl, gentlStr);                                                                        \
		CASE(GC_ERR_INVALID_INDEX, OutOfRangeException, message, gentl, gentlStr);                                                                                \
		CASE(GC_ERR_PARSING_CHUNK_DATA, RuntimeException, message, gentl, gentlStr);                                                                              \
		CASE(GC_ERR_INVALID_VALUE, InvalidArgumentException, message, gentl, gentlStr);                                                                           \
		CASE(GC_ERR_RESOURCE_EXHAUSTED, RuntimeException, message, gentl, gentlStr);                                                                              \
		CASE(GC_ERR_OUT_OF_MEMORY, RuntimeException, message, gentl, gentlStr);                                                                                   \
		CASE(GC_ERR_BUSY, RuntimeException, message, gentl, gentlStr);                                                                                            \
		default:                                                                                                                                                  \
			if (strcmp(gentl,"") == 0)                                                                                                                                      \
				throw GenICam::GenericException(MSG(GenericException, GC_ERR_ERROR, message, __FILE__, __FUNCTION__), __FILE__, __LINE__);                        \
			else                                                                                                                                                  \
				throw GenICam::GenericException(MSG_GENTL(GenericException, GC_ERR_ERROR, message, __FILE__, __FUNCTION__, gentl, gentlStr), __FILE__, __LINE__); \
	}

// throw special instruction
#define THROW_IF(err, code, type, message, gentl)                                    \
	if (err == code)                                                                 \
	{                                                                                \
		GENTL_MSG;                                                                   \
		throw GenICam::type(                                                         \
			MSG_GENTL(type, code, message, __FILE__, __FUNCTION__, gentl, gentlStr), \
			__FILE__,                                                                \
			__LINE__);                                                               \
	}

// throw non-gentl
#define THROW_TYPE(type, message)                           \
	throw GenICam::type(                                    \
		MSG_NO_CODE(type, message, __FILE__, __FUNCTION__), \
		__FILE__,                                           \
		__LINE__);

#define THROW_NO_GENTL(err, message) \
	THROW_DEFAULT(err, message, "");
