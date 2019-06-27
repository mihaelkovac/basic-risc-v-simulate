#ifndef I32FORMAT_H
#define I32FORMAT_H

#include "Include/Format.h"

namespace risc
{
	
	template<>
	struct FormatFunctionHash<KEY_I32>
	{
		constexpr int operator()(int fun3, int opcode) const
		{
			return (fun3 << 7) | opcode;
		}	
	};
	
	struct I32Format : public Format32Base<KEY_I32, int, int, int>
	{
		static constexpr auto opcodes = make_opcodes({BI("0000011"), BI("0010011"), BI("1100111"), BI("1110011")});
		
		void init_functions();
	};

}

#endif
