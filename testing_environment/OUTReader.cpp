#include "OUTReader.h"



OutData OUTReader::read(std::ifstream& stream, const std::string_view& file_name)
{
	std::cout << "Reading .out file: "  << file_name << ".out\n";
	OutData data{};
	if(!stream.good())
	{
		return data;
	}
	
	this->pc_was_read = false;
	std::string line;
	std::size_t line_num = 0;
	while(std::getline(stream, line))
	{
		line_num++;
		if(line.empty() || std::regex_match(line, this->comment_rgx)) continue;
		
		std::stringstream formatter{};
		std::smatch m;
		if(std::regex_search(line, m, this->register_rgx))
		{
			int register_index, register_value;
			formatter << m.str(1) << ' ' << m.str(2);
			formatter >> register_index;
			if(this->register_rd_mode == ReadMode::hex)
			{
				formatter >> std::hex;
			}
			formatter >> register_value;
			
			if(register_index >= data.registers.size())
			{
				data.registers.resize(register_index + 1);
			}
			data.registers[register_index] = register_value;
		} else if(std::regex_search(line, m, this->pc_rgx))
		{
			if(this->pc_was_read)
			{
				std::cerr << file_name << " - PC was already read -- multiple definitions of PC value in .out file\n";
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
		} else if(std::regex_search(line, m, this->mem_rgx))
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
			auto index = location / 4;
			if(index >= data.memory_values.size())
			{
				data.memory_values.resize(index + 1);
			}
			data.memory_values[location / 4] = memory_value;
		} else
		{
			std::cerr << file_name << " - Line " << line_num << " is not a comment, register entry, memory entry or pc_registry\n";
		}
		
	}
	return data;
}

OUTReader make_out_reader(std::string_view&& value_delimiter,
						  ReadMode register_read_mode,
						  ReadMode memory_location_mode,
						  ReadMode memory_value_mode,
						  ReadMode pc_read_mode)
{
	
	std::string register_rgx{out_register_regex_base()};
	std::string_view register_read_rgx = ReadModeHolder::read_mode_rgxs[register_read_mode];
	iterate_and_replace_all_placeholders(register_rgx, {{value_delimiter_ph(), value_delimiter},
														{register_value_type_ph(), register_read_rgx}});
	
	std::string memory_rgx{out_mem_regex_base()};
	std::string_view memory_location_rgx = ReadModeHolder::read_mode_rgxs[memory_location_mode];
	std::string_view memory_value_rgx = ReadModeHolder::read_mode_rgxs[memory_value_mode];
	
	iterate_and_replace_all_placeholders(memory_rgx, {{memory_location_type_ph(), memory_location_rgx},
													  {value_delimiter_ph(), value_delimiter},
													  {memory_value_type_ph(), memory_value_rgx}});
													  
	std::string pc_rgx{out_pc_regex_base()};
	std::string_view pc_value_rgx = ReadModeHolder::read_mode_rgxs[pc_read_mode];
	iterate_and_replace_all_placeholders(pc_rgx, {{value_delimiter_ph(), value_delimiter},
												  {pc_read_ph(), pc_value_rgx}});
	
	return OUTReader(register_rgx, memory_rgx, pc_rgx, register_read_mode, memory_location_mode, memory_value_mode, pc_read_mode);
	
}
