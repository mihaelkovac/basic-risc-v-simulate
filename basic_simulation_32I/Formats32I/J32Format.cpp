#include "J32Format.h"
#include "Instructions32I/Instructions32I_J.h"

namespace risc
{
	
	
	void J32Format::init_functions()
	{
		this->functions[this->hash(BI("1101111"))] = instructions_32I::jal;
	}
	
}
