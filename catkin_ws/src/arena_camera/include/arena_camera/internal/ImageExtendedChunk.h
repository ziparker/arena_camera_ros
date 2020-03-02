#pragma once
#include "IChunkData.h"
#include "Image.h"
#include "ChunkData.h"

namespace Arena
{
	class TLDataStream;
	class ARENA_TEST_API ImageExtendedChunk : virtual public Image, virtual public ChunkData
	{
	public:
		ImageExtendedChunk(TLDataStream* pStream, GenTL::BUFFER_HANDLE hBuffer, GenApi::INodeMap* pChunkNodeMap);
		ImageExtendedChunk(ImageExtendedChunk* pImageExt);
		ImageExtendedChunk();
		virtual ~ImageExtendedChunk();

		//IBuffer methods
		virtual const uint8_t* GetData();
		virtual size_t GetSizeFilled();
		virtual size_t GetPayloadSize();
		virtual size_t GetSizeOfBuffer();
		virtual bool HasChunkData();
		virtual size_t GetPayloadType();
		virtual bool IsIncomplete();
		virtual uint64_t GetFrameId();
		virtual bool HasImageData();
		virtual bool DataLargerThanBuffer();
		virtual bool VerifyCRC();
		//IImage methods
		virtual size_t GetWidth();
		virtual size_t GetHeight();
		virtual size_t GetOffsetX();
		virtual size_t GetOffsetY();
		virtual uint64_t GetPixelFormat();
		virtual uint64_t GetTimestamp();
		virtual size_t GetPaddingX();
		virtual size_t GetPaddingY();
		virtual int32_t GetPixelEndianness();
		virtual uint64_t GetTimestampNs();
		virtual IChunkData* AsChunkData();

		//ChunkData methods
		virtual GenApi::INode* GetChunk(GenICam::gcstring name);
		virtual IImage* AsImage();
	};
}
