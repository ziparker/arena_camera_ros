#include "stdafx.h"

namespace Arena
{
	template<class MODULE, typename CMD>
	size_t GetInfoSizeT(MODULE* pModule, CMD cmd)
	{
		if (!pDevice)
		{
			THROW_TYPE(
				InvalidArgumentException,
				"Device is null");
		}

		size_t value = 0;
		size_t valueLen = sizeof(value);
		GenTL::INFO_DATATYPE type;
		GenTL::GC_ERROR err = pModule->GetInfo(cmd, &type, &value, &valueLen);
		if (err != GenTL::GC_ERR_SUCCESS)
		{
			THROW_NO_GENTL(
				err,
				"Unable to get info");
		}

		if (type != GenTL::INFO_DATATYPE_PTR)
		{
			THROW_TYPE(
				LogicalErrorException,
				"Incorrect datatype returned (pointer expected)");
		}

		return value;
	}
}