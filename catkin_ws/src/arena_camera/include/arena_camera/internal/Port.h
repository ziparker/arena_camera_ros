#pragma once

#include "GTestAPI.h"

namespace Arena
{
	class TLBase;
	class ARENA_TEST_API Port : public GenApi::IPort
	{
	public:
		Port(TLBase* pPort);
		virtual ~Port();
		Port();

		//! Reads a chunk of bytes from the port
		virtual void Read(void* pBuffer, int64_t Address, int64_t Length);

		//! Writes a chunk of bytes to the port
		virtual void Write(const void* pBuffer, int64_t Address, int64_t Length);

		virtual GenApi::EAccessMode GetAccessMode() const;

	private:
		TLBase* m_pPort;
	};
}
