#ifndef INSTRUCTIONS32I_R_H
#define INSTRUCTIONS32I_R_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		

		void add(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void slt(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void sltu(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void _and(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void _or(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void _xor(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void sll(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void srl(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void sub(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
		void sra(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers);
	}
	
}

#endif
