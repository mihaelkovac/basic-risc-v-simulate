#include "R32Format.h"
#include "Instructions32I/Instructions32I_R.h"

namespace risc
{
	
	void R32Format::init_functions()
	{
		this->functions[this->hash(BI("0000000"), BI("000"), BI("0110011"))] = instructions_32I::add;
		this->functions[this->hash(BI("0100000"), BI("000"), BI("0110011"))] = instructions_32I::sub;
		this->functions[this->hash(BI("0000000"), BI("001"), BI("0110011"))] = instructions_32I::sll;
		this->functions[this->hash(BI("0000000"), BI("010"), BI("0110011"))] = instructions_32I::slt;
		this->functions[this->hash(BI("0000000"), BI("011"), BI("0110011"))] = instructions_32I::sltu;
		this->functions[this->hash(BI("0000000"), BI("100"), BI("0110011"))] = instructions_32I::_xor;
		this->functions[this->hash(BI("0000000"), BI("101"), BI("0110011"))] = instructions_32I::srl;
		this->functions[this->hash(BI("0100000"), BI("101"), BI("0110011"))] = instructions_32I::sra;
		this->functions[this->hash(BI("0000000"), BI("110"), BI("0110011"))] = instructions_32I::_or;
		this->functions[this->hash(BI("0000000"), BI("111"), BI("0110011"))] = instructions_32I::_and;
	}
	
//	void add(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void slt(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void sltu(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void _and(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void _or(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void _xor(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void sll(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void srl(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void sub(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
//		void sra(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
	
}
