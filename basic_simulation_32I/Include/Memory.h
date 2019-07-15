#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <type_traits>
#include <cstdint>
#include <iostream>
#include <vector>

#include "InstructionBits.h"
#include "Include/BinaryUtils.h"

#define BYTES_OF_MEM 64000

namespace risc
{
	using byte = unsigned char;
	
	struct Memory
	{
		Memory() = default;
		
		template<typename T, int Bytes = sizeof(T)>
		constexpr typename std::enable_if_t<std::is_integral<T>::value && Bytes <= sizeof(T), T> from_location_as(std::size_t location)
		{
			if(location + Bytes > this->size_in_bytes)
			{
				throw std::runtime_error("Cannot get memory at specified location -- MEMORY OVERFLOW\n");
			}
			
			T result{};

			for(auto i = Bytes - 1; i >= 1; --i)
			{
				result |= mem[location + i];
				result <<= 8;
			}
			//zeroth location must not be shifted
			result |= mem[location];
			
			return result;
			
		}
		
		InstructionBits get_instruction(uint16_t& first_two_bytes, int& size_in_bits, std::size_t& pc) const;
		InstructionBits get_instruction(int& size_in_bits, std::size_t& pc) const;
		
		template <typename Number>
		void fill_at(std::size_t location, Number bytes, unsigned int num_of_bytes = sizeof(Number))
		{

			if(location + num_of_bytes > this->size_in_bytes)
			{
				throw std::runtime_error("Cannot fill memory at specified location -- MEMORY OVERFLOW\n");
			}
			
			for(auto i = 0; i < num_of_bytes; ++i)
			{

                mem[location + i] = bytes >> i * 8;
			}
			
		}

		void fill_at(std::size_t location, std::vector<byte>& bytes)
        {
		    if(location + bytes.size() >= this->size_in_bytes)
            {
                throw std::runtime_error("Cannot fill memory at specified location -- MEMORY OVERFLOW\n");
            }

		    for(int i = 0, n = bytes.size(); i < n; ++i)
            {
		        mem[location + i] = std::move(bytes[i]);
            }
        }
		
		std::size_t size() const noexcept;
		
		
		private:
			byte mem[BYTES_OF_MEM]{0};
			size_t size_in_bytes = BYTES_OF_MEM;
			
//			int bit_size(size_t& pc);
			

	};

}
#endif
