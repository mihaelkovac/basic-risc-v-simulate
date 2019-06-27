#include "TestComparator.h"
#include <iostream>
#include <sstream>

void TestComparator::compare_out_and_xpct(OutData& out_data, ExpectedData& exp_data, const std::string_view& file_name)
{
	this->tracker_.set_current_test(file_name);
	std::cout << "Comparing .out and .xpct files: " << file_name << "\n\n";
	std::ostringstream string_builder{};
	for(unsigned int i = 0, n = exp_data.registers.size(); i < n; ++i)
	{
		if(i >= out_data.registers.size())
		{
			string_builder << "Incompatible register number - .out = " << out_data.registers.size() << ", .xpct = " << n;
			this->tracker_.add_message(string_builder.str());
			string_builder.clear();
//			std::cerr << file_name << " - Incompatible register number - .out = " << out_data.registers.size() << ", .xpct = " << n << '\n';
			break;
		}
		if(exp_data.registers[i] != out_data.registers[i])
		{
			string_builder << "Register[" << i << "].xpct:" << exp_data.registers[i] << " != Register[" << i << "].out:" << out_data.registers[i];
			this->tracker_.add_message(string_builder.str());
			string_builder.clear();
//			std::cerr << file_name << " - Register[" << i << "].xpct:" << exp_data.registers[i] << " != Register[" << i << "].out:" << out_data.registers[i] << '\n';
		}
	}
	
	
	if(out_data.pc != exp_data.pc)
	{
		string_builder << "PC.xpct:" << exp_data.pc << " != PC.out:" << out_data.pc << '\n';
		this->tracker_.add_message(string_builder.str());
		string_builder.clear();
	}
	
	for(auto& memory_pair : exp_data.memory_locations)
	{
		auto index = memory_pair.first / 4;
		if(index >= out_data.memory_values.size())
		{
			string_builder << "Expected memory location " << std::hex << memory_pair.first << " is out of bounds";
			this->tracker_.add_message(string_builder.str());
			string_builder.clear();
//			std::cerr << file_name << " - Expected memory location " << std::hex << memory_pair.first << " is out of bounds\n" << std::dec;
		}
		
		if(out_data.memory_values[index] != memory_pair.second)
		{
			string_builder << "Memory[" 
						   << std::hex << memory_pair.first 
						   << "].xpct:" 
						   << std::dec << memory_pair.second 
						   << " != Memory[" 
						   << std::hex << memory_pair.first 
						   << "].out:" 
						   << out_data.memory_values[index] << '\n';
			this->tracker_.add_message(string_builder.str());
			string_builder.clear();
		}
		
	}
	this->tracker_.test_finished();
	
}
