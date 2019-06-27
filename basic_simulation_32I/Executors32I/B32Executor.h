#ifndef B32EXECUTOR_H
#define B32EXECUTOR_H

#include "Include/Executor.h"

#include <memory>
#include <type_traits>

namespace risc
{
	
	template<typename FormatClass>
	struct B32Executor : public ExecutorBase<int, FormatClass, KEY_B32>
	{
		using ExecutorBase<int, FormatClass, KEY_B32>::ExecutorBase;
		
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int funct3 = instruction.instruction_part<12, 15>();
			int rs1 = instruction.instruction_part<15, 20>();
			int rs2 = instruction.instruction_part<20, 25>();
			
			int imm_11 = instruction.instruction_part<7, 8>();
			int imm_1_4 = instruction.instruction_part<8, 12>();
			int imm_5_10 = instruction.instruction_part<25, 31>();
			int imm_12 = instruction.instruction_part<31, 32>();
			
			int imm = (imm_12 << 12) | (imm_11 << 11) | (imm_5_10 << 5) | (imm_1_4 << 1);
			
			this->execute_instruction(this->key(funct3, opcode), rs1, rs2, imm, memory, registers);
		}
		
	};
	
	template<>
	struct ExecutorFactory<KEY_B32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<B32Executor<FormatType>>();
		}	
	};
}

#endif
