#ifndef OUTDATA_H
#define OUTDATA_H

#include <vector>
#include <cstdint>

struct OutData
{
	std::vector<int> registers{};
	std::size_t pc = 0;
	std::vector<unsigned int> memory_values{};
};

#endif
