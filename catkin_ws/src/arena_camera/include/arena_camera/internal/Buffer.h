#pragma once
#include "IBuffer.h"
#include "TLDataStream.h"

namespace Arena
{
	template<typename T>
	T GetInfo(TLDataStream* pDataStream, GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD cmd)
	{
		// check for logical errors
		if (!pDataStream)
		{
			THROW_TYPE(
				InvalidArgumentException,
				"DataStream is null");
		}

		if (!hBuffer)
		{
			THROW_TYPE(
				InvalidArgumentException,
				"Buffer is null");
		}

		// get uint64_t value
		T value = 0;
		size_t valueLen = sizeof(value);
		GenTL::INFO_DATATYPE type;

		GenTL::GC_ERROR err = pDataStream->GetBufferInfo(hBuffer, cmd, &type, &value, &valueLen);
		if (err != GenTL::GC_ERR_SUCCESS)
		{
			THROW_DEFAULT(
				err,
				"Unable to get buffer information",
				"DSGetBufferInfo");
		}

		return value;
	}

	template<typename T>
	void Cleanup(T*& pVal)
	{
		if (pVal != NULL)
		{
			delete pVal;
			pVal = NULL;
		}
	}

	class ARENA_TEST_API Buffer : public IBuffer
	{
	public:
		Buffer(TLDataStream* pStream, GenTL::BUFFER_HANDLE hBuffer);
		Buffer(Buffer* pBuffer);
		Buffer();
		virtual ~Buffer();

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
		virtual IChunkData* AsChunkData();
		virtual IImage* AsImage();
		virtual bool DataLargerThanBuffer();
		virtual bool VerifyCRC();

		virtual GenTL::BUFFER_HANDLE
			GetBufferHandle();
		friend ImageFactory;

	protected:
		TLDataStream* m_pStream;
		GenTL::BUFFER_HANDLE m_hBuffer;

		// TODO:  These should all be GenApi::CPtr types once we implement a GenTL nodemap
		uint8_t* m_pData;
		size_t* m_pSizeFilled;
		size_t* m_pPayloadSize;
		size_t* m_pSizeOfBuffer;
		bool8_t* m_pHasChunkData;
		size_t* m_pPayloadType;
		bool8_t* m_pIsIncomplete;
		uint64_t* m_pFrameId;
		bool8_t* m_pHasImageData;
		bool8_t* m_pDataLargerThanBuffer;
	};
}
