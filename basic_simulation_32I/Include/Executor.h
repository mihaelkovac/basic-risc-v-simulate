#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <tuple>
#include <functional>
#include <memory>

#include "InstructionBits.h"
#include "Memory.h"
#include "Registers.h"
#include "Format.h"
#include "ExecutorFactory.h"

namespace risc
{
	
	template<typename IntegralType>
	struct Executor
	{
		virtual void execute(InstructionBits& instruction, Memory& memory, Registers<IntegralType>& registers) = 0;
	};
	
	template<typename RegisterType, typename FormatClass, uint32_t FormatKey>
	struct ExecutorBase : public Executor<RegisterType>
	{
		static_assert(FormatKey == FormatClass::format_key, "Format with invalid key specified as template parameter for class derived from ExecutorBase\n");
		
		ExecutorBase(FormatClass&& format) : format_(format)
		{
			format_.init_functions();
		}
		
		ExecutorBase() : ExecutorBase(FormatClass{}) { }
		
		protected:
			FormatClass format_;
			
			using FunctionKey = typename FormatClass::key_type;
			
			template<typename ... Args>
			void execute_instruction(FunctionKey&& key, Args&&... args)
			{
				std::apply(format_.function(key), std::forward_as_tuple(args...));
			}
			
			template<typename ... Args>
			constexpr FunctionKey key(Args&&... args)
			{
				return std::apply(format_.hash, std::forward_as_tuple(args...));
			}
	};


}

#endif
