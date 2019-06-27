#ifndef U32FORMAT_H
#define U32FORMAT_H

#include "Include/Format.h"

namespace risc
{
		
	template<>
	struct FormatFunctionHash<KEY_U32>
	{
		constexpr int operator()(int opcode) const
		{
			return opcode;
		}	
	};
	
	struct U32Format : public Format32Base<KEY_U32, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("0110111"), BI("0010111")});
		
		void init_functions();
	};

}

#endif
