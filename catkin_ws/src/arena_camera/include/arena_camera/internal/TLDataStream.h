#pragma once
#include "stdafx.h"
#include "TLBase.h"

namespace Arena
{
	class ARENA_TEST_API TLDataStream : public TLBase
	{
	public:
		TLDataStream(GenTL::DS_HANDLE hDataStream);
		TLDataStream();
		~TLDataStream();

		virtual GenTL::GC_ERROR Close();
		virtual GenTL::GC_ERROR AnnounceBuffer(void* pBuffer, size_t iSize, void* pPrivate, GenTL::BUFFER_HANDLE* phBuffer);
		virtual GenTL::GC_ERROR AllocAndAnnounceBuffer(size_t iSize, void* pPrivate, GenTL::BUFFER_HANDLE* phBuffer);
		virtual GenTL::GC_ERROR QueueBuffer(GenTL::BUFFER_HANDLE hBuffer);
		virtual GenTL::GC_ERROR RevokeBuffer(GenTL::BUFFER_HANDLE hBuffer, void** pBuffer, void** pPrivate);
		virtual GenTL::GC_ERROR FlushQueue(GenTL::ACQ_QUEUE_TYPE iOperation);
		virtual GenTL::GC_ERROR GetInfo(GenTL::STREAM_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR GetBufferID(uint32_t iIndex, GenTL::BUFFER_HANDLE* phBuffer);
		virtual GenTL::GC_ERROR GetBufferInfo(GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR StartAcquisition(GenTL::ACQ_START_FLAGS iStartFlags, uint64_t iNumToAcquire);
		virtual GenTL::GC_ERROR StopAcquisition(GenTL::ACQ_STOP_FLAGS iStopFlags);
		virtual GenTL::GC_ERROR GetBufferChunkData(GenTL::BUFFER_HANDLE hBuffer, GenTL::SINGLE_CHUNK_DATA* pChunkData, size_t* piNumChunks);
	};
}