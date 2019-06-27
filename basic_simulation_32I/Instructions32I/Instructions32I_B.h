#ifndef INSTRUCTIONS32I_B_H
#define INSTRUCTIONS32I_B_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		
		void beq(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void bne(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void blt(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void bltu(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void bge(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void bgeu(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		
	}
}

#endif
