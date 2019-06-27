#include "I32Executor.h"

//namespace risc
//{
//	template<typename FormatClass>
//	void I32Executor<FormatClass>::execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers)
//	{
//		auto opcode = instruction.opcode();
//		auto rd = instruction.instruction_part<7, 12>();
//		auto funct3 = instruction.instruction_part<12, 15>();
//		auto rs1 = instruction.instruction_part<15, 20>();
//		auto imm = instruction.instruction_part<20, 32>();
//		
//		this->execute_instruction(this->key(funct3, opcode), rd, rs1, imm, memory, registers);
//
//
//	}
//}
