#pragma once
#include "TLInterface.h"
#include "Port.h"
#include "IDevice.h"
#include <mutex>
#include <algorithm>

namespace Arena
{
	class ARENA_TEST_API Interface
	{
	public:
		Interface(TLInterface* pInterface, GenICam::gcstring id);
		virtual ~Interface();

		virtual TLInterface* GetTLInterface();
		virtual GenApi::INodeMap* GetNodeMap();
		virtual GenICam::gcstring GetId();

#if defined(_ARENA_UNIT_TEST_API)
		Interface(TLInterface* pInterface, GenApi::INodeMap* pNodeMap) :
			m_pInterface(pInterface),
			m_port(pInterface),
			m_pNodeMap(pNodeMap)
		{
		}

		void nullifyNodeMap()
		{
			m_pNodeMap = NULL;
		}
#endif

		void AddDevice(IDevice* pDevice)
		{
			std::unique_lock<std::mutex> l(m_mtxDev);
			m_pDevices.push_back(pDevice);
		}

		void RemoveDevice(IDevice* pDevice)
		{
			std::unique_lock<std::mutex> l(m_mtxDev);
			auto it = std::find(m_pDevices.begin(), m_pDevices.end(), pDevice);
			if (it != m_pDevices.end())
			{
				m_pDevices.erase(it);
			}
		}

	private:
		TLInterface* m_pInterface;
		Port m_port;
		GenApi::INodeMap* m_pNodeMap;
		GenICam::gcstring m_id;
		std::vector<IDevice*> m_pDevices;
		std::mutex m_mtxDev;
	};
} // namespace Arena
