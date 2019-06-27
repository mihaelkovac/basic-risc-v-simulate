#include "Memory.h"
#include "Include/BinaryUtils.h"
#include "Utilities.h"

#include <cstdint>

namespace risc
{
	
	InstructionBits Memory::get_instruction(uint16_t& first_two_bytes, int& size_in_bits, std::size_t& pc) const
	{
		
		int size_in_bytes = size_in_bits / 8;

		std::vector<unsigned char> bytes(size_in_bytes);
		for(int i = size_in_bytes - 1; i >= 2; --i)
		{
//			instruction |= mem[pc + i];
//			instruction <<= 8;
			bytes[i] = mem[pc + i];
		}
		
//		instruction |= first_two_bytes;
		bytes[1] = first_two_bytes >> 8;
		bytes[0] = first_two_bytes & Binary::B11111111;
		
//		return {instruction, size_in_bytes};
		return InstructionBits{std::move(bytes)};
	}
	
	InstructionBits Memory::get_instruction(int& size_in_bits, std::size_t& pc) const
	{
		
		int size_in_bytes = size_in_bits / 8;
		
//		unsigned long long instruction = 0;
		std::vector<unsigned char> bytes(size_in_bytes);
		for(int i = size_in_bytes - 1; i >= 0; --i)
		{
//			instruction |= mem[pc + i];
//			instruction <<= 8;
			bytes[i] = mem[pc + i];
		}
		
//		return {instruction, size_in_bytes};
		return InstructionBits{std::move(bytes)};
	}
	
	std::size_t Memory::size() const noexcept
	{
		return this->size_in_bytes; 
	}
	
//	template <typename Number>
//	void Memory::fill_at(size_t location, Number bytes, unsigned int num_of_bytes)
//	{
//
//		if(location + num_of_bytes >= this->size_in_bytes)
//		{
//			throw std::runtime_error("Cannot fill memory at specified location -- MEMORY OVERFLOW\n");
//		}
//		
//		for(int i = 0; i < num_of_bytes; ++i)
//		{
//			mem[location + i] = bytes & (Binary::B11111111 << i * 8);
//		}
//		
//	}
	
}
