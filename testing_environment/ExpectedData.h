#ifndef EXPECTEDDATA_H
#define EXPECTEDDATA_H

#include <unordered_map>
#include <vector>
#include <utility>

struct ExpectedData
{
	std::vector<std::pair<int, int>> registers{};
	std::size_t pc = 0;
	std::unordered_map<std::size_t, unsigned int> memory_locations{};
	
	bool empty() const noexcept;
};

#endif
