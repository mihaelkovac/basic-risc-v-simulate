#include "BinaryUtils.h"
#include <stdexcept>

namespace risc
{
	
	Binary BinaryUtils::get_binary(int num)
	{
		if(num > 8 || num < 0)
		{
			throw std::runtime_error("Invalid number specified for get_binary");
		}
		return BinaryUtils::binaries_storage[num];
	}
	
	Binary BinaryUtils::get_binary_zeros_from_start(int num)
	{
		if(num > 8 || num < 0)
		{
			throw std::runtime_error("Invalid number specified for get_binary");
		}
		return BinaryUtils::binaries_storage[8 + num];
	}
	
}
