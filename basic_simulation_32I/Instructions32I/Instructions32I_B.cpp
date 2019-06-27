#include "Instructions32I_B.h"
#include "Include/Utilities.h"

namespace risc
{
	
	namespace instructions_32I
	{
		
		void beq(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if(registers[rs1] == registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			} else
            {
			    registers.add_to_pc(4);
            }
		}
		
		void bne(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if(registers[rs1] != registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			} else
            {
                registers.add_to_pc(4);
            }
		}
		
		void blt(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if(registers[rs1] < registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			} else
            {
                registers.add_to_pc(4);
            }
		}
		
		void bltu(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if((unsigned)registers[rs1] < (unsigned)registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			}
		}
		
		void bge(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if(registers[rs1] >= registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			} else
            {
                registers.add_to_pc(4);
            }
		}
		
		void bgeu(int rs1, int rs2, int imm, Memory& memory, Registers<int>& registers)
		{
			if((unsigned)registers[rs1] >= (unsigned)registers[rs2])
			{
				registers.add_to_pc(C2(imm, 13));
			} else
            {
                registers.add_to_pc(4);
            }
		}
		
		
		
	}
}
