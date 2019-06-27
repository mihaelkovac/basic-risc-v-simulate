#ifndef XPCTREADER_H
#define XPCTREADER_H

#include "ReaderBase.h"
#include <initializer_list>
#include <sstream>
#include "ExpectedData.h"
#include <regex>
#include <string>
#include <string_view>
#include <fstream>
#include <iostream>


struct XPCTReader : public ReaderBase<ExpectedData>
{

	using ReaderBase::ReaderBase;
	
	
	ExpectedData read(std::ifstream& stream, const std::string_view& file_name) override;
		
};

static constexpr std::string_view xpct_register_regex_base()
{
	return "x(\\d{1,3})_VD_(_RVT_)";
}

static constexpr std::string_view xpct_mem_regex_base()
{
	return "mem_MD_(_MLT_)_VD_(_MVT_)";
}

static constexpr std::string_view xpct_pc_regex_base()
{
	return "pc_VD_(_PCT_)";
}

extern XPCTReader make_xpct_reader(std::string_view&& value_delimiter = "=",
								   std::string_view&& mem_delimiter = "\\.",
								   ReadMode register_read_mode = ReadMode::dec,
								   ReadMode memory_location_mode = ReadMode::hex,
								   ReadMode memory_value_mode = ReadMode::hex,
								   ReadMode pc_read_mode = ReadMode::hex);




#endif
