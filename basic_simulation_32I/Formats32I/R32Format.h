#ifndef R32FORMAT_H
#define R32FORMAT_H

#include "Include/Format.h"

namespace risc
{
	
	template<>
	struct FormatFunctionHash<KEY_R32>
	{
		constexpr int operator()(int fun7, int fun3, int opcode) const
		{
			return (((fun7 << 3) | fun3) << 7) | opcode;
		}
	};
	struct R32Format : public Format32Base<KEY_R32, int, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("0110011")});
		
		void init_functions();
	};
	
	
}

#endif
