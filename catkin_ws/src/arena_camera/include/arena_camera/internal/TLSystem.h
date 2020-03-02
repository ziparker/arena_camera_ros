#pragma once
#include "stdafx.h"
#include "TLBase.h"

namespace Arena
{
	class ARENA_TEST_API TLSystem : public TLBase
	{
	public:
		TLSystem(GenTL::TL_HANDLE hSystem);
		TLSystem();
		virtual ~TLSystem();

		virtual GenTL::GC_ERROR Open();
		virtual GenTL::GC_ERROR Close();
		virtual GenTL::GC_ERROR GetInfo(GenTL::TL_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR GetNumInterfaces(uint32_t* piNumIfaces);
		virtual GenTL::GC_ERROR GetInterfaceID(uint32_t iIndex, char* sID, size_t* piSize);
		virtual GenTL::GC_ERROR GetInterfaceInfo(const char* sIfaceID, GenTL::INTERFACE_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR OpenInterface(const char* sIfaceID, GenTL::IF_HANDLE* phIface);
		virtual GenTL::GC_ERROR UpdateInterfaceList(bool8_t* pbChanged, uint64_t iTimeout);
	};
}