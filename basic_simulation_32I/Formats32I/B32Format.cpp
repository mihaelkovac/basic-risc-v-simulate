#include "B32Format.h"
#include "Instructions32I/Instructions32I_B.h"

namespace risc
{
	
	void B32Format::init_functions()
	{
		this->functions[this->hash(BI("000"), BI("1100011"))] = instructions_32I::beq;
		this->functions[this->hash(BI("001"), BI("1100011"))] = instructions_32I::bne;
		this->functions[this->hash(BI("100"), BI("1100011"))] = instructions_32I::blt;
		this->functions[this->hash(BI("110"), BI("1100011"))] = instructions_32I::bltu;
		this->functions[this->hash(BI("101"), BI("1100011"))] = instructions_32I::bge;
		this->functions[this->hash(BI("111"), BI("1100011"))] = instructions_32I::bgeu;
	}
	
}
