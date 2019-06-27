#include "InstructionBits.h"

namespace risc
{
	
	InstructionBits::InstructionBits(InstructionBits&& instruction)
	{
		this->storage = std::move(instruction.storage);
		
	}
	
	InstructionBits& InstructionBits::operator=(InstructionBits&& instruction)
	{
		if(this != &instruction)
		{
			storage = std::move(instruction.storage);
		}
		return *this;
	}
	
	int InstructionBits::opcode() const noexcept
	{
		return this->storage[0] & Binary::B01111111;
	}
	
	int InstructionBits::size() const noexcept
	{
		return this->storage.size() * 8;
	}
	
	int InstructionBits::size_in_bytes() const noexcept
	{
		return this->storage.size();
	}
	
	std::vector<byte>& InstructionBits::bytes()
	{
		return storage;
	}
	
	void InstructionBits::clear()
	{
		this->storage.clear();
	}

	bool InstructionBits::empty() const noexcept
    {
	    for(auto& b : this->storage)
        {
	        if(b)
	            return false;
        }
	    return true;
    }
}
