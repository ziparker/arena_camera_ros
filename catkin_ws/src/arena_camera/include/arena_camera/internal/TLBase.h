#pragma once

#include "stdafx.h"

namespace Arena
{
	class ARENA_TEST_API TLBase
	{
	public:
		TLBase();
		TLBase(GenTL::PORT_HANDLE hModule);
		virtual ~TLBase();

		virtual GenTL::GC_ERROR ReadPort(uint64_t iAddress, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR WritePort(uint64_t iAddress, const void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR GetPortURL(char* sURL, size_t* piSize);
		virtual GenTL::GC_ERROR GetPortInfo(GenTL::PORT_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR RegisterEvent(GenTL::EVENT_TYPE iEventID, GenTL::EVENT_HANDLE* phEvent);
		virtual GenTL::GC_ERROR UnregisterEvent(GenTL::EVENT_TYPE iEventID);
		virtual GenTL::GC_ERROR GetNumPortURLs(uint32_t* piNumURLs);
		virtual GenTL::GC_ERROR GetPortURLInfo(uint32_t iURLIndex, GenTL::URL_INFO_CMD iInfoCmd, GenTL::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize);
		virtual GenTL::GC_ERROR ReadPortStacked(GenTL::PORT_REGISTER_STACK_ENTRY* pEntries, size_t* piNumEntries);
		virtual GenTL::GC_ERROR WritePortStacked(GenTL::PORT_REGISTER_STACK_ENTRY* pEntries, size_t* piNumEntries);

		virtual GenTL::PORT_HANDLE GetHandle();

	protected:
		GenTL::PORT_HANDLE m_hModule;
	};
}