#pragma once
#include "IImage.h"
#include "Buffer.h"

namespace Arena
{
	class TLDataStream;
	class ARENA_TEST_API Image : public IImage, virtual public Buffer
	{
	public:
		Image(TLDataStream* pStream, GenTL::BUFFER_HANDLE hBuffer);
		Image(Image* pImage);
		Image();
		virtual ~Image();

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
		virtual size_t GetBitsPerPixel();

		friend ImageFactory;

	protected:
		// TODO These should all be GenApi::CPtr types once we implement a GenTL nodemap
		size_t* m_pWidth;
		size_t* m_pHeight;
		size_t* m_pOffsetX;
		size_t* m_pOffsetY;
		uint64_t* m_pPixelFormat;
		uint64_t* m_pTimestamp;
		size_t* m_pPaddingX;
		size_t* m_pPaddingY;
		int32_t* m_pPixelEndianness;
		uint64_t* m_pTimestampNs;
	};
}
