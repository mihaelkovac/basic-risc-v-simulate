#ifndef B32FORMAT_H
#define B32FORMAT_H

#include "Include/Format.h"

namespace risc
{
		
	template<>
	struct FormatFunctionHash<KEY_B32>
	{
		constexpr int operator()(int fun3, int opcode) const
		{
			return (fun3 << 7) | opcode;
		}	
	};
	
	struct B32Format : public Format32Base<KEY_B32, int, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("1100011")});
		
		void init_functions();
	};

}


#endif
