#ifndef EXECUTORFACTORY_H
#define EXECUTORFACTORY_H

#include <cstdint>

namespace risc
{
	
	template<uint32_t FormatKey>
	struct ExecutorFactory
	{
		ExecutorFactory() = delete;
	};

}

#endif
