#ifndef RISCVCORE_H
#define RISCVCORE_H

#include <array>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <vector>
#include <iostream>

#include "Include/Executor.h"
#include "RiscVException.h"

namespace risc
{
	
	template<typename IntegralType, typename ... Formats>
	struct RiscVCore
	{
		
		void execute_instruction(Memory& memory)
		{
			uint16_t length_encoding = memory.from_location_as<uint16_t>(this->registers.pc());
			int length = length_of_instruction(length_encoding);
			
			auto instruction = memory.get_instruction(length, this->registers.pc());
			if(instruction.empty())
            {
			    throw RiscVException("illegal instruction exception", "All bits of the instruction are 0");
            }
			const int opcode = instruction.opcode();
			this->instruction_count++;
            this->executor_impls.at(opcode)->execute(instruction, memory, this->registers);
		}
				
		RiscVCore()
		{
			(map_executors<Formats>(std::forward<decltype(Formats::opcodes)>(Formats::opcodes)),...);
		}
		RiscVCore(RiscVCore<IntegralType, Formats...>&& core) : executor_impls(std::move(core.executor_impls)), registers(std::move(core.registers))
		{}
		
		Registers<IntegralType>& get_registers()
		{
			return this->registers;
		}

		void init_stack_pointer(std::size_t stack_location)
        {
		    this->registers[2] = stack_location;
        }

        std::size_t executed_instructions()
        {
		    return this->instruction_count;
        }

		using register_type = IntegralType;

		private:
			using ExecutorPtr = std::shared_ptr<Executor<IntegralType>>;
			
			std::unordered_map<int, ExecutorPtr> executor_impls;
			Registers<IntegralType> registers{};
			std::size_t instruction_count = 0;
			
			template<typename Format, typename Array>
			void map_executors(Array&& opcodes)
			{

				auto executor_impl = ExecutorFactory<Format::format_key>::template make_executor<Format>();
				for(auto n = opcodes.size(), i = 0; i < n; ++i)
				{
					executor_impls[opcodes[i]] = executor_impl;
				}
			}
			
			static int length_of_instruction(uint16_t first_16_bits)
			{
				if((first_16_bits & 3) < 3)
				{
					return 16;
				}
				
				
				if((first_16_bits & 31) < 31)
				{
					return 32;
				}
				
			
				if((first_16_bits & 63) == 31)
				{
					return 48;
				}
				
				if((first_16_bits & 127) == 63)
				{
					return 64;
				}
				
				int factor = first_16_bits & (7 << 12);
				if(factor < 7)
				{
					return 80 + 16 * factor;
				}
				//else case reserved for instructions of length >= 192 which is not implemented yet
				throw std::runtime_error("Unimplemented or unknown instruction length encoding given");
			}
			
	};
	
	
	template<typename RegisterType, typename ... Formats>
	auto make_risc_v_core()
	{
		return RiscVCore<RegisterType, Formats...>{};
	}
	
//	template<typename RegisterType, typename ... Formats>
//	auto make_risc_v_core(Formats&&...)
//	{
//		return RiscVCore<RegisterType, Formats...>{};
//	}
	
}

#endif
