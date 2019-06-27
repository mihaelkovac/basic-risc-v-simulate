#ifndef INSTRUCTIONS32I_J_H
#define INSTRUCTIONS32I_J_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		
		void jal(int rd, int imm, Memory& memory, Registers<int>& registers);
		
	}
}

#endif
