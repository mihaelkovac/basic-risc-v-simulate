#include "Instructions32I_I.h"
#include "Include/Utilities.h"
#include "Include/BinaryUtils.h"
#include "Include/RiscVException.h"

#include <cstdint>
#include <stdexcept>
#include <sstream>

namespace risc
{
	
	namespace instructions_32I
	{
		
		void addi(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] + C2(imm, 12);
			registers.add_to_pc(4);
		}
		
		void slti(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			if(C2(imm, 12) > registers[rs1])
			{
				registers[rd] = 1;
			} else
			{
				registers[rd] = 0;
			}
			
			registers.add_to_pc(4);
		}
		
		void sltiu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			if((unsigned int)registers[rs1] < imm)
			{
				registers[rd] = 1;
			} else
			{
				registers[rd] = 0;
			}
			
			registers.add_to_pc(4);
		}
		
		void andi(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] & C2(imm, 12);
			registers.add_to_pc(4);
		}
		
		void ori(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] | C2(imm, 12);
			registers.add_to_pc(4);
		}
		
		void xori(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] ^ C2(imm, 12);
			registers.add_to_pc(4);
		}
		
		void slli(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers[rs1] << (imm & Binary::B00011111);
			registers.add_to_pc(4);
		}
		
		void sri(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			if(imm & (1024)) // imm & 010000000000 to get type of shift
			{
				registers[rd] = registers[rs1] >> (imm & Binary::B00011111);
			} else
			{
				registers[rd] = (unsigned int)registers[rs1] >> (imm & Binary::B00011111);
			}
			registers.add_to_pc(4);
		}
		
		void jalr(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers.pc() + 4;
			auto imm_2c = (registers[rs1] + C2(imm, 12));
            if(imm_2c % 4)
            {
                std::ostringstream stream{};
                stream << "The immediate value was not 4-byte aligned -- JALR instruction at: " << registers.pc();
                throw RiscVException("misaligned instruction fetch exception", std::move(stream.str()));
            }
			registers.set_pc(imm_2c);
			
		}
		
		void lb(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = memory.from_location_as<int8_t>(registers[rs1] + C2(imm, 12));
            registers.add_to_pc(4);
		}
		
		void lh(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = memory.from_location_as<int16_t>(registers[rs1] + C2(imm, 12));
            registers.add_to_pc(4);
		}
		
		void lw(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = memory.from_location_as<int>(registers[rs1] + C2(imm, 12));
            registers.add_to_pc(4);
		}
		
		void lbu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = memory.from_location_as<uint8_t>(registers[rs1] + C2(imm, 12));
            registers.add_to_pc(4);
		}
		
		void lhu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = memory.from_location_as<uint16_t>(registers[rs1] + C2(imm, 12));
            registers.add_to_pc(4);
		}
		
		void fence(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The FENCE instruction has not yet been implemented!\n");
		}
		
		void fence_i(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The FENCE.I instruction has not yet been implemented!\n");
		}
		
		void csrrw(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The CSSRW instruction has not yet been implemented!\n");
		}
		
		void csrrs(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The CSSRS instruction has not yet been implemented!\n");
		}
		
		void csrrc(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The CSSRC instruction has not yet been implemented!\n");
		}
		
		void csrrwi(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The CSSRWI instruction has not yet been implemented!\n");
		}
		
		void csrrsi(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The CSSRSI instruction has not yet been implemented!\n");
		}
		
		void csrrci(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers)
		{
			throw std::runtime_error("The FENCE.I instruction has not yet been implemented!\n");
		}

        void sys_call(int rd, int rs1, int func12, Memory& memory, Registers<int>& registers)
        {
		    if(rd || rs1)
            {
		        throw std::runtime_error("The SYSTEM instructions (ECALL, EBREAK) must have rd and rs1 fields set to 0\n");
            }
		    switch(func12)
            {
                case 0:
                    throw RiscVException("environment-call-from-U-mode exception", "ECALL was executed!");
                default:
                    throw std::runtime_error("Only the ECALL instruction with the SYSTEM opcode has been implemented -- the fun12 field should be 0!");
            }
        }
		
		
		
	}
}
