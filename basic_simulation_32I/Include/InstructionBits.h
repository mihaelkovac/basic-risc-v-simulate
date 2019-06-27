#ifndef INSTRUCTIONBITS_H
#define INSTRUCTIONBITS_H
#include <stdexcept>
#include <vector>
#include <type_traits>

#include "Include/BinaryUtils.h"

namespace risc
{
	
	struct InstructionBits
	{
		
		InstructionBits(InstructionBits&& instruction);
		
//		template<typename Number>
//		InstructionBits(typename std::enable_if<std::is_integral_v<Number>, Number>::type&& number) noexcept
//		{
//			InstructionBits(number, sizeof(number));
//		}
		
		template <typename Number>
		InstructionBits(typename std::enable_if<std::is_integral_v<Number>, Number>::type&& number, int byte_num = sizeof(Number)) : storage(byte_num)
		{
			if(byte_num > sizeof(Number)) throw std::runtime_error("The number of bits to take from the given number can not be higher than the number of bits the number contains");

			for(int i = 0; i < byte_num; ++i)
			{
				storage[i] = number >> (i * 8);
			}
		}
		
		explicit InstructionBits(std::vector<byte>&& data)
		{
			this->storage = std::move(data);
		}
		
		InstructionBits& operator=(InstructionBits&& other);
		
		template <unsigned int from_bit, unsigned int to_position>
		int instruction_part() const
		{
			
			static_assert(from_bit < to_position, "The first template argument has to be lower than the second one");
			
			if(to_position > this->size())
			{
				throw std::runtime_error("Invalid number of bits specified in template instruction_part::to_position -- The position is bigger than the amount of bits the instruction contains");
			}
			
			constexpr int to_bit_at = to_position - 1;
			constexpr int start = from_bit / 8;
			constexpr int end = to_bit_at / 8;

            //handle the last element of the byte array
            int result = storage[end] & BinaryUtils::get_binary((to_bit_at % 8) + 1);

			if constexpr (start != end)
            {

                for(int i = end - 1; i > start; --i)
                {
                    result <<= 8;
                    result += storage[i];
                }
                //handle the first element of the byte array
                result <<= 8 - (from_bit % 8);
                result += (storage[start] & BinaryUtils::get_binary_zeros_from_start((from_bit % 8))) >> (from_bit % 8);
            } else
            {
			    result >>= from_bit % 8;
            }


			
			return result;
		}
		
		int opcode() const noexcept;
		
		int size() const noexcept;
		
		int size_in_bytes() const noexcept;
		
		std::vector<byte>& bytes();
		
		void clear();

		bool empty() const noexcept;
		
		private:
			std::vector<byte> storage;
	};
	
}
#endif
