#ifndef U32EXECUTOR_H
#define U32EXECUTOR_H

#include "Include/Executor.h"

namespace risc
{
	
	template<typename FormatClass>
	struct U32Executor : public ExecutorBase<int, FormatClass, KEY_U32>
	{
		using Super = ExecutorBase<int, FormatClass, KEY_U32>;
		using Super::Super;
		void execute(InstructionBits& instruction, Memory& memory, Registers<int>& registers) override
		{
			int opcode = instruction.opcode();
			int rd = instruction.instruction_part<7, 12>();
			int imm = instruction.instruction_part<12, 32>() << 12;

			this->execute_instruction(this->key(opcode), rd, imm, memory, registers);
		}
		
	};
	
	template<>
	struct ExecutorFactory<KEY_U32>
	{
		template<typename FormatType>
		static auto make_executor()
		{
			return std::make_shared<U32Executor<FormatType>>();
		}	
	};

}

#endif
