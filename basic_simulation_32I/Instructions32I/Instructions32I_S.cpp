#include "Instructions32I_S.h"
#include "Include/Utilities.h"

namespace risc
{
	
	namespace instructions_32I
	{
		
		void sb(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			memory.fill_at(registers[rs1] + C2(imm, 12), (int)registers[rs2], 1);
			registers.add_to_pc(4);
		}
		
		void sh(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			memory.fill_at(registers[rs1] + C2(imm, 12), (int)registers[rs2], 2);
			registers.add_to_pc(4);
		}
		
		void sw(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			memory.fill_at(registers[rs1] + C2(imm, 12), (int)registers[rs2]);
			registers.add_to_pc(4);
		}
		
		
	}
}
