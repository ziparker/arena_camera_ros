#pragma once

#include "stdafx.h"

namespace Arena
{
	class ARENA_TEST_API DeviceInfo_t
	{

	public:
		DeviceInfo_t(){};
		~DeviceInfo_t(){};

		GenICam::gcstring m_modelName;
		GenICam::gcstring m_vendorName;
		GenICam::gcstring m_serialNumber;
		GenICam::gcstring m_id;
		GenICam::gcstring m_userDefName;

		uint32_t m_ip;
		uint32_t m_mask;
		uint64_t m_mac;
		uint32_t m_gateway;

		bool m_dhcpEnabled;
		bool m_persistentIpEnabled;
		bool m_llaEnabled;

		uint64_t m_ifaceMac;
		GenICam::gcstring m_deviceVersion;
	};
} // namespace Arena
