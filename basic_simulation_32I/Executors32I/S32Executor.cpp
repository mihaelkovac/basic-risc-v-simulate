#include "S32Executor.h"

//namespace risc
//{
//	
//	template<typename FormatClass>
//	void S32Executor<FormatClass>::execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers)
//	{
//		auto opcode = instruction.opcode();
//		auto imm_0_4 = instruction.instruction_part<7, 12>();
//		auto funct3 = instruction.instruction_part<12, 15>();
//		auto rs1 = instruction.instruction_part<15, 20>();
//		auto rs2 = instruction.instruction_part<20, 25>();
//		auto imm_5_11 = instruction.instruction_part<25, 32>();
//		
//		auto imm = (imm_5_11 << 5) | imm_0_4;
//		
//		this->execute_instruction(this->key(funct3, opcode), rs1, rs2, imm, memory, registers);
//	}
//	
//}
