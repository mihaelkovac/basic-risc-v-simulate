#include "S32Format.h"
#include "Instructions32I/Instructions32I_S.h"

namespace risc
{
	
	void S32Format::init_functions()
	{
		this->functions[this->hash(BI("000"), BI("0100011"))] = instructions_32I::sb;
		this->functions[this->hash(BI("001"), BI("0100011"))] = instructions_32I::sh;
		this->functions[this->hash(BI("010"), BI("0100011"))] = instructions_32I::sw;
	}
	
}
