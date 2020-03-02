#pragma once

#include "stdafx.h"

namespace Arena
{
	class Interface;
	class ARENA_TEST_API InterfaceInfo_t
	{

	public:
		InterfaceInfo_t(){};
		~InterfaceInfo_t(){};

		uint32_t m_ip;
		uint32_t m_mask;
		uint64_t m_mac;
		uint32_t m_gateway;
	};
} // namespace Arena
