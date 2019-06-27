#ifndef READERBASE_H
#define READERBASE_H

#include "ReadMode.h"
#include <regex>
#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <utility>
#include <tuple>

template <typename ReturnValue>
struct ReaderBase
{
	ReaderBase(std::string_view&& register_regex, std::string_view&& memory_regex, std::string_view&& pc_regex, ReadMode register_read_mode, ReadMode memory_location_mode, ReadMode memory_value_mode, ReadMode pc_read_mode)
	{
		this->register_rgx = std::regex(register_regex.data());
		this->mem_rgx = std::regex(memory_regex.data());
		this->mem_loc_rd_mode = memory_location_mode;
		this->mem_val_rd_mode = memory_value_mode;
		this->register_rd_mode = register_read_mode;
		this->pc_rd_mode = pc_read_mode;
		this->pc_rgx = std::regex(pc_regex.data());
	}
	
	ReaderBase(std::string& register_regex, std::string& memory_regex, std::string& pc_regex, ReadMode register_read_mode, ReadMode memory_location_mode, ReadMode memory_value_mode, ReadMode pc_read_mode)
	{
		this->register_rgx = std::regex{register_regex};
		this->mem_rgx = std::regex{memory_regex};
		this->mem_loc_rd_mode = memory_location_mode;
		this->mem_val_rd_mode = memory_value_mode;
		this->register_rd_mode = register_read_mode;
		this->pc_rd_mode = pc_read_mode;
		this->pc_rgx = std::regex{pc_regex};

	}
	
	virtual ReturnValue read(std::ifstream& stream, const std::string_view& file_name) = 0;
	
	protected:
		const std::regex comment_rgx{"\\/\\/.*"};
		std::regex register_rgx;
		std::regex mem_rgx;
		std::regex pc_rgx;
		
		ReadMode register_rd_mode;
		ReadMode mem_val_rd_mode;
		ReadMode mem_loc_rd_mode;
		ReadMode pc_rd_mode;
		bool pc_was_read = false;
};

//PLACEHOLDERS:
//VD = VALUE DELIMITER
//RVT = REGISTER VALUE TYPE (NUMBER TYPE -> hex, binary, dec)
//MD = MEMORY DELIMITER
//MVT = MEMORY VALUE TYPE (NUMBER TYPE)
//MLT = MEMORY LOCATION TYPE (NUMBER TYPE)

static constexpr std::string_view value_delimiter_ph()
{
	return "_VD_";
}

static constexpr std::string_view register_value_type_ph()
{
	return "_RVT_";
}

static constexpr std::string_view memory_delimiter_ph()
{
	return "_MD_";
}

static constexpr std::string_view memory_location_type_ph()
{
	return "_MLT_";
}

static constexpr std::string_view memory_value_type_ph()
{
	return "_MVT_";
}

static constexpr std::string_view pc_read_ph()
{
	return "_PCT_";
}

//template<unsigned int N>
//extern void iterate_and_replace_all_placeholders(std::string& iteratee, const std::pair<std::string_view&&, std::string_view&> (&place_holders)[N]);

template<unsigned int N>
void iterate_and_replace_all_placeholders(std::string& iteratee, const std::pair<std::string_view&&, std::string_view&> (&place_holders)[N])
{
	for(auto& place_holder_pair : place_holders)
	{
		auto pos = iteratee.find(place_holder_pair.first);
		if(pos != std::string::npos)
		{
			iteratee.replace(pos, place_holder_pair.first.length(), place_holder_pair.second);
		}
	}
	
}

#endif
