#include "J32Executor.h"

//namespace risc
//{
//	template<typename FormatClass>
//	void J32Executor<FormatClass>::execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers)
//	{
//		auto opcode = instruction.opcode();
//		auto rd = instruction.instruction_part<7, 12>();
//		auto imm_12_19 = instruction.instruction_part<12, 19>();
//		auto imm_11 = instruction.instruction_part<19, 20>();
//		auto imm_1_10 = instruction.instruction_part<20, 31>();
//		auto imm_20 = instruction.instruction_part<31, 32>();
//		
//		auto imm = (imm_20 << 19) | (imm_12_19 << 11) | (imm_11 << 10) | (imm_1_10 << 1);
//		
//		this->execute_instruction(this->key(opcode), rd, imm, memory, registers);
//	}
//
//}
