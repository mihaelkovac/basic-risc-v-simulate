#include "I32Format.h"
#include "Instructions32I/Instructions32I_I.h"

namespace risc
{
	
	void I32Format::init_functions()
	{
		this->functions[this->hash(BI("000"), BI("0010011"))] = instructions_32I::addi;
		this->functions[this->hash(BI("010"), BI("0010011"))] = instructions_32I::slti;
		this->functions[this->hash(BI("011"), BI("0010011"))] = instructions_32I::sltiu;
		this->functions[this->hash(BI("111"), BI("0010011"))] = instructions_32I::andi;
		this->functions[this->hash(BI("110"), BI("0010011"))] = instructions_32I::ori;
		this->functions[this->hash(BI("100"), BI("0010011"))] = instructions_32I::xori;
		this->functions[this->hash(BI("001"), BI("0010011"))] = instructions_32I::slli;
		this->functions[this->hash(BI("101"), BI("0010011"))] = instructions_32I::sri;
		this->functions[this->hash(BI("000"), BI("1100111"))] = instructions_32I::jalr;
		this->functions[this->hash(BI("000"), BI("0000011"))] = instructions_32I::lb;
		this->functions[this->hash(BI("001"), BI("0000011"))] = instructions_32I::lh;
		this->functions[this->hash(BI("010"), BI("0000011"))] = instructions_32I::lw;
		this->functions[this->hash(BI("100"), BI("0000011"))] = instructions_32I::lbu;
		this->functions[this->hash(BI("101"), BI("0000011"))] = instructions_32I::lhu;
		this->functions[this->hash(BI("000"), BI("0001111"))] = instructions_32I::fence;
		this->functions[this->hash(BI("001"), BI("0001111"))] = instructions_32I::fence_i;
		this->functions[this->hash(BI("001"), BI("1110011"))] = instructions_32I::csrrw;
		this->functions[this->hash(BI("010"), BI("1110011"))] = instructions_32I::csrrs;
		this->functions[this->hash(BI("011"), BI("1110011"))] = instructions_32I::csrrc;
		this->functions[this->hash(BI("101"), BI("1110011"))] = instructions_32I::csrrwi;
		this->functions[this->hash(BI("110"), BI("1110011"))] = instructions_32I::csrrsi;
		this->functions[this->hash(BI("111"), BI("1110011"))] = instructions_32I::csrrci;
		this->functions[this->hash(BI("000"), BI("1110011"))] = instructions_32I::sys_call;
		
	}

}
