#include "Instructions32I_U.h"

namespace risc
{
	
	namespace instructions_32I
	{
		void lui(int rd, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = imm;
			registers.add_to_pc(4);
		}
		
		void auipc(int rd, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers.pc() + imm;
			registers.add_to_pc(4);
		}
	}
	
}
