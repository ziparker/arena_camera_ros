#pragma once
#include "stdafx.h"
#include "TLBase.h"

namespace Arena
{
	class ARENA_TEST_API TLEvent : public TLBase
	{
	public:
		TLEvent(GenTL::EVENT_HANDLE hDevice);
		TLEvent();
		~TLEvent();

		virtual GenTL::GC_ERROR GetData(void* pBuffer, size_t* piSize, uint64_t iTimeout);
		virtual GenTL::GC_ERROR GetDataInfo(const void* pInBuffer, size_t iInSize, GenTL::EVENT_DATA_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pOutBuffer, size_t* piOutSize);
		virtual GenTL::GC_ERROR GetInfo(GenTL::EVENT_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR Flush();
		virtual GenTL::GC_ERROR Kill();
	};
}