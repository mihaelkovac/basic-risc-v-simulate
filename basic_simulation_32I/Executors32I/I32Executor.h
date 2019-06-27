#ifndef I32EXECUTOR_H
#define I32EXECUTOR_H

#include "Include/Executor.h"
#include "Include/Format.h"


namespace risc
{
	
	template<typename FormatClass>
	struct I32Executor : public ExecutorBase<int, FormatClass, KEY_I32>
	{
		using Super = ExecutorBase<int, FormatClass, KEY_I32>;
		using Super::Super;
		
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int rd = instruction.instruction_part<7, 12>();
			int funct3 = instruction.instruction_part<12, 15>();
			int rs1 = instruction.instruction_part<15, 20>();
			int imm = instruction.instruction_part<20, 32>();
			
			this->execute_instruction(this->key(funct3, opcode), rd, rs1, imm, memory, registers);
	
	
		}
		
	
	};
	
	template<>
	struct ExecutorFactory<KEY_I32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<I32Executor<FormatType>>();
		}	
	};
}

#endif
