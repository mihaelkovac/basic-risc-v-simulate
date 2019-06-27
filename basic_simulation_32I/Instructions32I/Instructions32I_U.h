#ifndef INSTRUCTIONS32I_U_H
#define INSTRUCTIONS32I_U_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		void lui(int rd, int imm, Memory& memory, Registers<int>& registers);
		void auipc(int rd, int imm, Memory& memory, Registers<int>& registers);
	}
	
}

#endif
