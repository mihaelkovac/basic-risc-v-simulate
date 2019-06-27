#ifndef R32EXECUTOR_H
#define R32EXECUTOR_H

#include "Include/Executor.h"

namespace risc
{
	template<typename FormatClass>
	struct R32Executor : public ExecutorBase<int, FormatClass, KEY_R32>
	{
		
		using Super = ExecutorBase<int, FormatClass, KEY_R32>;
		using Super::Super;
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int rd = instruction.instruction_part<7, 12>();
			int funct3 = instruction.instruction_part<12, 15>();
			int rs1 = instruction.instruction_part<15, 20>();
			int rs2 = instruction.instruction_part<20, 25>();
			int funct7 = instruction.instruction_part<25, 32>();
			
			this->execute_instruction(this->key(funct7, funct3, opcode), rd, rs1, rs2, memory, registers);
		}
		
	};
	
	template<>
	struct ExecutorFactory<KEY_R32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<R32Executor<FormatType>>();
		}	
	};

}
#endif
