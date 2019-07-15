#include "TestComparator.h"
#include <iostream>
#include <sstream>

void TestComparator::compare_out_and_xpct(OutData& out_data, ExpectedData& exp_data, const std::string& file_name)
{
	this->tracker_.set_current_test(file_name);
	std::cout << "Comparing .out and .xpct files: " << file_name << "\n\n";
	std::ostringstream string_builder{};
	for(unsigned int i = 0, n = exp_data.registers.size(); i < n; ++i)
	{
	    auto index = exp_data.registers[i].first;
		if(index >= out_data.registers.size())
		{
			string_builder << "No value specified for register x" << index << " in .out file, expected value x" << index << '=' << exp_data.registers[i].second;
			this->tracker_.add_message(string_builder.str());
			string_builder.str(std::string());
			continue;
//			std::cerr << file_name << " - Incompatible register number - .out = " << out_data.registers.size() << ", .xpct = " << n << '\n';
		}
		if(exp_data.registers[i].second != out_data.registers[index])
		{
			string_builder << "Register[" << index << "].xpct:" << exp_data.registers[i].second << " != Register[" << index << "].out:" << out_data.registers[index];
			this->tracker_.add_message(string_builder.str());
            string_builder.str(std::string());
//			std::cerr << file_name << " - Register[" << i << "].xpct:" << exp_data.registers[i] << " != Register[" << i << "].out:" << out_data.registers[i] << '\n';
		}
	}
	
	
	if(out_data.pc != exp_data.pc)
	{
		string_builder << "PC.xpct:" << exp_data.pc << " != PC.out:" << out_data.pc;
		this->tracker_.add_message(string_builder.str());
        string_builder.str(std::string());
	}
	
	for(auto& memory_pair : exp_data.memory_locations)
	{
		auto index = memory_pair.first / 4;
		if(index >= out_data.memory_values.size())
		{
			string_builder << "Expected memory location " << memory_pair.first << " is out of bounds";
			this->tracker_.add_message(string_builder.str());
            string_builder.str(std::string());
//			std::cerr << file_name << " - Expected memory location " << std::hex << memory_pair.first << " is out of bounds\n" << std::dec;
		}
		
		if(out_data.memory_values[index] != memory_pair.second)
		{
			string_builder << "Memory["
			               << memory_pair.first
						   << "].xpct:" 
						   << memory_pair.second
						   << " != Memory[" 
						   << memory_pair.first
						   << "].out:" 
						   << out_data.memory_values[index];
			this->tracker_.add_message(string_builder.str());
            string_builder.str(std::string());
		}
		
	}
	this->tracker_.test_finished();
	
}
