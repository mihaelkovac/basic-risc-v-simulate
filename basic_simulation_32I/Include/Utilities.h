#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>

namespace risc
{
	
	
	constexpr uint32_t val_32_const = 0x811c9dc5;
	constexpr uint32_t prime_32_const = 0x1000193;
	
		
	inline constexpr uint32_t fnv_hash_32(const char * input, uint32_t result = val_32_const)
	{
		return input[0] == '\0' ? result : fnv_hash_32(&input[1], (result ^ input[0]) * prime_32_const);
	}
	
	#define FNV32(x) fnv_hash_32(x)
	
	int twos_complement(int num, int highest_bit_position);
	#define C2(x, y) twos_complement(x, y)
}

#endif
