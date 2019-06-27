#ifndef S32EXECUTOR_H
#define S32EXECUTOR_H

#include "Include/Executor.h"

namespace risc
{
	
	template<typename FormatClass>
	struct S32Executor : public ExecutorBase<int, FormatClass, KEY_S32>
	{
		using Super = ExecutorBase<int, FormatClass, KEY_S32>;
		using Super::Super;
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int imm_0_4 = instruction.instruction_part<7, 12>();
			int funct3 = instruction.instruction_part<12, 15>();
			int rs1 = instruction.instruction_part<15, 20>();
			int rs2 = instruction.instruction_part<20, 25>();
			int imm_5_11 = instruction.instruction_part<25, 32>();
			
			int imm = (imm_5_11 << 5) | imm_0_4;
			
			this->execute_instruction(this->key(funct3, opcode), rs1, rs2, imm, memory, registers);
		}
		
	};
	
	template<>
	struct ExecutorFactory<KEY_S32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<S32Executor<FormatType>>();
		}	
	};

}

#endif
