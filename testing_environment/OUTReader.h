#ifndef OUTREADER_H
#define OUTREADER_H

#include "OutData.h"
#include "ReaderBase.h"
#include "ExpectedData.h"



struct OUTReader : public ReaderBase<OutData>
{
	
	using ReaderBase::ReaderBase;
	
	OutData read(std::ifstream& stream, const std::string_view& file_name) override;
	

};

static constexpr std::string_view out_register_regex_base()
{
	return "x(\\d{2,3})\\s*_VD_\\s*(_RVT_)";
}

static constexpr std::string_view out_mem_regex_base()
{
	return "(_MLT_)\\s*_VD_\\s*(_MVT_)";
}

static constexpr std::string_view out_pc_regex_base()
{
	return "pc\\s*_VD_\\s*(_PCT_)";
}

extern OUTReader make_out_reader(std::string_view&& value_delimiter = ":",
								 ReadMode register_read_mode = ReadMode::dec,
								 ReadMode memory_location_mode = ReadMode::hex,
								 ReadMode memory_value_mode = ReadMode::dec,
								 ReadMode pc_read_mode = ReadMode::dec);


#endif
