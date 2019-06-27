#include "Utilities.h"
#include <stdexcept>

namespace risc
{
	
	
	int twos_complement(int num, int highest_bit_position)
	{
		return ((num >> (highest_bit_position - 1)) & 1) ? num - (1 << highest_bit_position) : num;
	}
	
}
