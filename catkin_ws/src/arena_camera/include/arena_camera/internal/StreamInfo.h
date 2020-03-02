#pragma once
#include "TLDataStream.h"
#include "Port.h"

namespace Arena
{
	class ARENA_TEST_API StreamInfo
	{
	public:
		StreamInfo(TLDataStream* pStream);
		virtual ~StreamInfo();

		virtual TLDataStream* GetTLDataStream();
		virtual GenApi::INodeMap* GetNodeMap();

#if defined(_ARENA_UNIT_TEST_API)
		StreamInfo(TLDataStream* pStream, GenApi::INodeMap* pNodeMap) :
			m_pStream(pStream),
			m_port(pStream),
			m_pNodeMap(pNodeMap)
		{
		}

		void nullifyNodeMap()
		{
			m_pNodeMap = NULL;
		}
#endif

	private:
		TLDataStream* m_pStream;
		Port m_port;
		GenApi::INodeMap* m_pNodeMap;
	};
}
