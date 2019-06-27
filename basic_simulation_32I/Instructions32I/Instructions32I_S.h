#ifndef INSTRUCTIONS32I_S_H
#define INSTRUCTIONS32I_S_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		
		void sb(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void sh(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		void sw(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers);
		
	}
}

#endif
