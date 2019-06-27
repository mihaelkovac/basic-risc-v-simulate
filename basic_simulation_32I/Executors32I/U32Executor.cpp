#include "U32Executor.h"

//namespace risc
//{
//	
//	template<typename FormatClass>
//	void U32Executor<FormatClass>::execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers)
//	{
//		auto opcode = instruction.opcode();
//		auto rd = instruction.instruction_part<7, 12>();
//		auto imm = instruction.instruction_part<12, 32>() << 12;
//		
//		this->execute_instruction(this->key(opcode), rd, imm, memory, registers);
//	}
//	
//}
