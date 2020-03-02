#pragma once
#include "ISystem.h"
#include "TLSystem.h"
#include "TLInterface.h"
#include "Interface.h"
#include "Port.h"
#include "PrivateGlobals.h"

#include <mutex>

namespace Arena
{
	class ARENA_TEST_API System : public ISystem
	{
	public:
		static ISystem* Open();
		static void Close();

		System(TLSystem* system);

		virtual ~System();

		virtual bool UpdateDevices(uint64_t timeout = 100);

		virtual bool UpdateDevices(InterfaceInfo ifaceInfo, uint64_t timeout = 100);

		virtual std::vector<DeviceInfo> GetDevices();

		virtual std::vector<InterfaceInfo> GetInterfaces();

		virtual IDevice* CreateDevice(DeviceInfo info);

		virtual void DestroyDevice(IDevice* pDevice);

		virtual GenApi::INodeMap* GetTLSystemNodeMap();

		virtual GenApi::INodeMap* GetTLInterfaceNodeMap(DeviceInfo devInfo);

		virtual void ForceIp(uint64_t macAddress, uint64_t ipAddress, uint64_t subnetMask, uint64_t defaultGateway);

		// used in testing
#if defined(_ARENA_UNIT_TEST_API)
		System(TLSystem* system, std::vector<Interface*> interfaces, GenApi::INodeMap* pNodeMap) :
			m_pSystem(system),
			m_interfaces(interfaces),
			m_pSystemNodeMap(pNodeMap),
            m_pPort(system)
		{
			OpenImageFactory();
		}

		void nullifyNodeMap()
		{
			m_pSystemNodeMap = NULL;
		}
#endif

	private:
		System();

		TLSystem* m_pSystem;
		std::vector<Interface*> m_interfaces;

		GenApi::INodeMap* m_pSystemNodeMap;
		Port m_pPort;

		//protects interface list from changing while accessing it
		std::mutex m_ifaceListMtx;

		// protects updated devices from being called from two threads at same time
		std::mutex m_updateDevsMtx;

	};
} // namespace Arena
