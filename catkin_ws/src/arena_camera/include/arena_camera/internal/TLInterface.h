#pragma once
#include "stdafx.h"
#include "TLBase.h"

namespace Arena
{
	class ARENA_TEST_API TLInterface : public TLBase
	{
	public:
		TLInterface(GenTL::IF_HANDLE hInterface);
		TLInterface();
		virtual ~TLInterface();

		//Interface operations
		virtual GenTL::GC_ERROR Close();
		virtual GenTL::GC_ERROR UpdateDeviceList(bool8_t *pbChanged, uint64_t iTimeout);
		virtual GenTL::GC_ERROR GetInfo(GenTL::INTERFACE_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE *piType, void *pBuffer, size_t *piSize);
		virtual GenTL::GC_ERROR GetNumDevices(uint32_t *piNumDevices);
		virtual GenTL::GC_ERROR GetDeviceID(uint32_t iIndex, char *sIDeviceID, size_t *piSize);
		virtual GenTL::GC_ERROR GetDeviceInfo(const char *sDeviceID, GenTL::DEVICE_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE *piType, void *pBuffer, size_t *piSize);
		virtual GenTL::GC_ERROR OpenDevice(const char *sDeviceID, GenTL::DEVICE_ACCESS_FLAGS iOpenFlags, GenTL::DEV_HANDLE *phDevice);
		virtual GenTL::GC_ERROR ForceIp(uint64_t mac, uint32_t ip, uint32_t subnet, uint32_t gateway);

	};
}