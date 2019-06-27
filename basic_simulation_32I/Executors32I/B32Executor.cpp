#include "B32Executor.h"

//namespace risc
//{
//	
//	template<typename FormatClass>
//	void B32Executor<FormatClass>::execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers)
//	{
//		auto opcode = instruction.opcode();
//		auto imm_11 = instruction.instruction_part<7, 8>();
//		auto imm_1_4 = instruction.instruction_part<8, 12>();
//		auto funct3 = instruction.instruction_part<12, 15>();
//		auto rs1 = instruction.instruction_part<15, 20>();
//		auto rs2 = instruction.instruction_part<20, 25>();
//		auto imm_5_10 = instruction.instruction_part<25, 31>();
//		auto imm_12 = instruction.instruction_part<31, 32>();
//		
//		auto imm = (imm_12 << 11) | (imm_11 << 10) | (imm_5_10 << 4) | (imm_1_4 << 1);
//		
//		this->execute_instruction(this->key(funct3, opcode), rs1, rs2, imm, memory, registers);
//	}
//	
//}
