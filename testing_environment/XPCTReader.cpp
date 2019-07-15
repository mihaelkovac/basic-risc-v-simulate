#include "XPCTReader.h"
#include <iomanip>

ExpectedData XPCTReader::read(std::ifstream& stream, const std::string_view& file_name)
{
	
	std::cout << "Reading .xpct file: " << file_name << ".xpct\n";
	ExpectedData data{};
	if(!stream.good())
	{
		return data;
	}
	
	this->pc_was_read = false;
	std::string line;
	unsigned long line_num = 0;
	while(stream.good())
	{
		
		stream >> line;
		++line_num;
//		std::cout << "Reading line number: " << line_num << " value: " << line << std::endl;
		if(line.empty() || std::regex_match(line, this->comment_rgx)) continue;
		
		std::stringstream formatter{};
		std::smatch m;
		if(std::regex_match(line, m, this->register_rgx))
		{
			int register_number, register_value;
			formatter << m.str(1) << ' ' << m.str(2);
			formatter >> register_number;
			if(this->register_rd_mode == ReadMode::hex)
			{
				formatter >> std::hex >> register_value;
			} 
			else 
			{
				formatter >> register_value;
			}

			data.registers.push_back({register_number, register_value});
		} 
		else if(std::regex_match(line, m, this->mem_rgx))
		{
			std::size_t location;
			unsigned int memory_value;
			formatter << m.str(1) << ' ' << m.str(2);
			if(this->mem_loc_rd_mode == ReadMode::hex)
			{
				formatter >> std::hex >> location;
			}
			else
			{
				formatter >> location;
			}			
			
			if(this->mem_val_rd_mode == ReadMode::hex)
			{
				formatter >> std::hex >> memory_value;
			}
			else 
			{
				formatter >> std::dec >> memory_value;
			}
			
//			formatter >> memory_value;
			
			data.memory_locations[location] = memory_value;
		}
		else if(std::regex_match(line, m, this->pc_rgx))
		{
			if(this->pc_was_read)
			{
				std::cerr << file_name << " - PC was already read -- multiple definitions of PC value in .xpct file\n";
				continue;
			}
			else
			{
				this->pc_was_read = true;
				std::size_t pc;
				formatter << m.str(1);
				if(this->pc_rd_mode == ReadMode::hex)
				{
					formatter >> std::hex;
				}
				formatter >> pc;
				data.pc = pc;
			}
		}
		else
		{
			std::cerr << file_name << " - Line " << line_num << " is not a comment, register entry, memory entry or pc entry\n";
		}
	}
	return data;
}

XPCTReader make_xpct_reader(std::string_view&& value_delimiter, std::string_view&& mem_delimiter, ReadMode register_read_mode, ReadMode memory_location_mode, ReadMode memory_value_mode, ReadMode pc_read_mode)
{
	std::string register_rgx{xpct_register_regex_base()};
	std::string_view register_read_rgx = ReadModeHolder::read_mode_rgxs[register_read_mode];
	iterate_and_replace_all_placeholders(register_rgx, {{value_delimiter_ph(), value_delimiter},
														{register_value_type_ph(), register_read_rgx}});
	
	std::string memory_rgx{xpct_mem_regex_base()};
	std::string_view memory_location_rgx = ReadModeHolder::read_mode_rgxs[memory_location_mode];
	std::string_view memory_value_rgx = ReadModeHolder::read_mode_rgxs[memory_value_mode];
	
	iterate_and_replace_all_placeholders(memory_rgx, {{memory_delimiter_ph(), mem_delimiter},
													  {memory_location_type_ph(), memory_location_rgx},
													  {value_delimiter_ph(), value_delimiter},
													  {memory_value_type_ph(), memory_value_rgx}});
													  
	std::string pc_rgx{xpct_pc_regex_base()};
	std::string_view pc_read_rgx = ReadModeHolder::read_mode_rgxs[pc_read_mode];
	iterate_and_replace_all_placeholders(pc_rgx, {{value_delimiter_ph(), value_delimiter},
												  {pc_read_ph(), pc_read_rgx}});
	
	return XPCTReader(register_rgx, memory_rgx, pc_rgx, register_read_mode, memory_location_mode, memory_value_mode, pc_read_mode);
	
}
