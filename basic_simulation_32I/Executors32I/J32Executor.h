#ifndef J32EXECUTOR_H
#define J32EXECUTOR_H

#include "Include/Executor.h"

namespace risc
{
	
	template<typename FormatClass>
	struct J32Executor : public ExecutorBase<int, FormatClass, KEY_J32>
	{
		
		using Super = ExecutorBase<int, FormatClass, KEY_J32>;
		using Super::Super;
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int rd = instruction.instruction_part<7, 12>();
		
			int imm_12_19 = instruction.instruction_part<12, 20>();
			int imm_11 = instruction.instruction_part<20, 21>();
			int imm_1_10 = instruction.instruction_part<21, 31>();
			int imm_20 = instruction.instruction_part<31, 32>();
			
			int imm = (imm_20 << 20) | (imm_12_19 << 12) | (imm_11 << 11) | (imm_1_10 << 1);
			
			this->execute_instruction(this->key(opcode), rd, imm, memory, registers);
		}
		
	};
	
	template<>
	struct ExecutorFactory<KEY_J32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<J32Executor<FormatType>>();
		}	
	};

}

#endif
