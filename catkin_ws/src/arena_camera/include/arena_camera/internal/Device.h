#pragma once
#include "IDevice.h"
#include "Port.h"
#include "TLDevice.h"
#include "TLDataStream.h"
#include "TLEvent.h"
#include "StreamInfo.h"
#include "Interface.h"
#include <GenApi/EventAdapter.h>
#include <GenApi/ChunkAdapterGEV.h>

#include <mutex>

namespace Arena
{
	class ARENA_TEST_API Device : public IDevice
	{
	public:
		Device(TLDevice* pDevice, Interface* pIfInfo);
		virtual ~Device();

		virtual GenApi::INodeMap* GetNodeMap();
		virtual GenApi::INodeMap* GetTLDeviceNodeMap();
		virtual GenApi::INodeMap* GetTLStreamNodeMap();
		virtual GenApi::INodeMap* GetTLStreamNodeMap(int streamNumber = 0);
		virtual GenApi::INodeMap* GetTLInterfaceNodeMap();

		virtual void StartStream(size_t numBuffers = 10);
		virtual void StopStream();
		virtual IImage* GetImage(uint64_t timeout);
		virtual IBuffer* GetBuffer(uint64_t timeout);
		virtual void RequeueBuffer(IBuffer* pImage);

		virtual void StartStream(int streamNumber, size_t numBuffers);
		virtual void StopStream(int streamNumber);
		virtual IImage* GetImage(int streamNumber, uint64_t timeout);
		virtual IBuffer* GetBuffer(int streamNumber, uint64_t timeout);
		virtual void RequeueBuffer(int streamNumber, IBuffer* pImage);

		virtual void InitializeEvents();
		virtual void DeinitializeEvents();
		virtual void WaitOnEvent(uint64_t timeout);

        virtual void SendActionCommand(uint32_t deviceKey, uint32_t groupKey, uint32_t groupMask, uint64_t actionTime);

		virtual bool IsConnected();

		virtual void ResetInterface()
		{
			std::unique_lock<std::mutex> l(m_interfaceMtx);
			m_pIfInfo = nullptr;
		}

		virtual Interface* GetInterface()
		{
			std::unique_lock<std::mutex> l(m_interfaceMtx);
			return m_pIfInfo;
		}

#if defined(_ARENA_UNIT_TEST_API)
		Device(TLDevice* pDevice, TLBase* pDeviceRemote, Interface* pifInfo, std::vector<StreamInfo*> streams, std::vector<TLEvent*> hEventNewBuffers, GenApi::INodeMap* pNodeMap, GenApi::INodeMap* pDeviceNodeMap, GenApi::CChunkAdapterGEV* pChunkAdapter, GenApi::CNodeMapFactory& chunkDataNodeMapFactory) :
			m_pDevice(pDevice),
			m_pDeviceRemote(pDeviceRemote),
			m_pIfInfo(pifInfo),
            m_pTLDeviceNodeMap(pDeviceNodeMap),
            m_pDeviceNodeMap(pNodeMap),
			m_pTLDevicePort(pDevice),
			m_pDevicePort(pDeviceRemote),
			m_streams(streams),
			m_hEventNewBuffers(hEventNewBuffers),
			m_pChunkAdapter(pChunkAdapter),
			m_chunkDataNodeMapFactory(chunkDataNodeMapFactory)
		{
		}

		void nullifyNodeMap()
		{
			m_pTLDeviceNodeMap = NULL;
			m_pDeviceNodeMap = NULL;
		}
#endif

	protected:
		Device();

		TLDevice* m_pDevice;
		TLBase* m_pDeviceRemote;
		Interface* m_pIfInfo;

		GenApi::INodeMap* m_pTLDeviceNodeMap;
		GenApi::INodeMap* m_pDeviceNodeMap;

		Port m_pTLDevicePort;
		Port m_pDevicePort;

		std::vector<StreamInfo*> m_streams;
		std::vector<TLEvent*> m_hEventNewBuffers;

		TLEvent* m_hEventRemoteDevice;
		GenApi::CEventAdapter* m_pEventAdapter;

		GenApi::CChunkAdapterGEV* m_pChunkAdapter;
		GenApi::CNodeMapFactory m_chunkDataNodeMapFactory;

		std::mutex m_interfaceMtx;
		std::mutex m_streamMutex;
	};
} // namespace Arena
