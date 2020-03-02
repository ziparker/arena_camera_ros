#pragma once
#include "IChunkData.h"
#include "Buffer.h"
#include <GenApi/ChunkAdapterGEV.h>

namespace Arena
{
	class TLDataStream;
	class ARENA_TEST_API ChunkData : public IChunkData, virtual public Buffer
	{
	public:
		ChunkData(TLDataStream* pStream, GenTL::BUFFER_HANDLE hBuffer, GenApi::INodeMap* pChunkNodeMap);
		ChunkData(ChunkData* pChunkData);
		ChunkData();
		virtual ~ChunkData();

		//IBuffer methods
		virtual const uint8_t* GetData();
		virtual size_t GetSizeFilled();
		virtual size_t GetPayloadSize();
		virtual size_t GetSizeOfBuffer();
		virtual bool HasChunkData();
		virtual IChunkData* AsChunkData();
		virtual size_t GetPayloadType();
		virtual bool IsIncomplete();
		virtual uint64_t GetFrameId();
		virtual bool HasImageData();
		virtual IImage* AsImage();
		virtual bool DataLargerThanBuffer();
		virtual bool VerifyCRC();

		//IImage methods
		virtual GenApi::INode* GetChunk(GenICam::gcstring name);

		friend ImageFactory;

	protected:
		GenApi::CChunkAdapterGEV* m_pChunkAdapter;
		GenApi::INodeMap* m_pChunkNodeMap;
	};
}
