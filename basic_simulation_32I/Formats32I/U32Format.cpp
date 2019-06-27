#include "U32Format.h"
#include "Instructions32I/Instructions32I_U.h"

namespace risc
{
	
	void U32Format::init_functions()
	{
		
		this->functions[this->hash(BI("0110111"))] = instructions_32I::lui;
		this->functions[this->hash(BI("0010111"))] = instructions_32I::auipc;
	}
	
}
