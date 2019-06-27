#include "Instructions32I_J.h"
#include "Include/Utilities.h"
#include "Include/RiscVException.h"
#include <sstream>

namespace risc
{
	
	namespace instructions_32I
	{
		
		void jal(int rd, int imm, Memory& memory, Registers<int>& registers)
		{
			registers[rd] = registers.pc() + 4;
			auto imm_2c = C2(imm, 20);
			if(imm_2c % 4)
            {
			    std::ostringstream stream{};
			    stream << "The immediate value was not 4-byte aligned -- JAL instruction at: " << registers.pc();
			    throw RiscVException("misaligned instruction fetch exception", std::move(stream.str()));
            }
			registers.add_to_pc(C2(imm, 20));
			
		}
		
	}
}
