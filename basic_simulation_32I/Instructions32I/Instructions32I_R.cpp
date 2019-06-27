#include "Instructions32I_R.h"
#include "Include/BinaryUtils.h"

namespace risc
{
	namespace instructions_32I
	{
		

		void add(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] + registers[rs2];
			registers.add_to_pc(4);
		}
		
		void slt(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			if(registers[rs1] < registers[rs2])
			{
				registers[rd] = 1;
			} else
			{
				registers[rd] = 0;
			}
			
			registers.add_to_pc(4);
		}
		
		void sltu(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{	
			
			if((unsigned int)registers[rs1] < (unsigned int)registers[rs2])
			{
				registers[rd] = 1;
			} else
			{
				registers[rd] = 0;
			}
			
			registers.add_to_pc(4);
		}
		
		void _and(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] & registers[rs2];
			registers.add_to_pc(4);
		}
		
		void _or(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] | registers[rs2];
			registers.add_to_pc(4);
		}
		
		void _xor(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] ^ registers[rs2];
			registers.add_to_pc(4);
		}
		
		void sll(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] << (registers[rs2] & Binary::B00011111);
			registers.add_to_pc(4);
		}
		
		void srl(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = (unsigned)registers[rs1] >> (registers[rs2] & Binary::B00011111);
			registers.add_to_pc(4);
		}
		
		void sub(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] - registers[rs2];
			registers.add_to_pc(4);
		}
		
		void sra(int rd, int rs1, int rs2, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] >> (registers[rs2] & Binary::B00011111);
			registers.add_to_pc(4);
		}
		
	}
	
}
