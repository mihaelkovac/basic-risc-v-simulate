#ifndef S32FORMAT_H
#define S32FORMAT_H

#include "Include/Format.h"

namespace risc
{
	
	
	template<>
	struct FormatFunctionHash<KEY_S32>
	{
		constexpr int operator()(int fun3, int opcode) const
		{
			return (fun3 << 7) | opcode;
		}	
	};
	
	struct S32Format : public Format32Base<KEY_S32, int, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("0100011")});
		
		void init_functions();
	};

}

#endif
