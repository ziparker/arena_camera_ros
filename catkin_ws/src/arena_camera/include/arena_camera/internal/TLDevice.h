#pragma once
#include "stdafx.h"
#include "TLBase.h"

namespace Arena
{
	class ARENA_TEST_API TLDevice : public TLBase
	{
	public:
		TLDevice(GenTL::DEV_HANDLE hDevice);
		TLDevice();
		~TLDevice();

		virtual GenTL::GC_ERROR Close();
		virtual GenTL::GC_ERROR GetInfo(GenTL::DEVICE_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR GetPort(GenTL::PORT_HANDLE* phRemoteDevice);
		virtual GenTL::GC_ERROR GetNumDataStreams(uint32_t* piNumDataStreams);
		virtual GenTL::GC_ERROR GetDataStreamID(uint32_t iIndex, char* sDataStreamID, size_t* piSize);
		virtual GenTL::GC_ERROR OpenDataStream(const char* sDataStreamID, GenTL::DS_HANDLE* phDataStream);

        virtual GenTL::GC_ERROR SendActionCommand(uint32_t deviceKey, uint32_t groupKey, uint32_t groupMask, uint64_t actionTime);
	};
}