#ifndef J32FORMAT_H
#define J32FORMAT_H

#include "Include/Format.h"

namespace risc
{
		
	template<>
	struct FormatFunctionHash<KEY_J32>
	{
		constexpr int operator()(int opcode) const
		{
			return opcode;
		}	
	};
	
	struct J32Format : public Format32Base<KEY_J32, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("1101111")});
		
		void init_functions();
	};
	

}

#endif
