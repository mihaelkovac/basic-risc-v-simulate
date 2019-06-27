#include <iostream>
#include <fstream>
#include <stdexcept>

#include "XPCTReader.h"
#include "OUTReader.h"
#include "TestComparator.h"
#include "DirectoryManager.h"
#include "TestTracker.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	if(!argv[1])
	{
		throw std::runtime_error("Cannot execute without parameters!");
	}
	
//	const std::string out_file_name{"D:/riscvprojekt/simulacije/test/Risc-v-32I-tests/add_large_overflow.out"};
//	const std::string xpct_file_name{"D:/riscvprojekt/simulacije/test/Risc-v-32I-tests/add_large_overflow.xpct"};
//	const std::string_view file_name{out_file_name.data(), out_file_name.length() - 4};
	
//	std::ifstream input_stream_out{out_file_name};
//	std::ifstream input_stream_xpct{xpct_file_name};
	
	DirectoryManager dir_manager{argv[1]};
	
	auto xpct_reader = make_xpct_reader();
	auto out_reader = make_out_reader();
	TestTracker tracker{};
	TestComparator comparator{tracker};
	
	auto test_file_pair = dir_manager.next_test_pair();
	while(test_file_pair != std::nullopt)
	{
		std::ifstream input_stream_out{test_file_pair->second.get_out_file()};
		std::ifstream input_stream_xpct{test_file_pair->second.get_xpct_file()};
		
		auto out_data = out_reader.read(input_stream_out, test_file_pair->first);
		auto xpct_data = xpct_reader.read(input_stream_xpct, test_file_pair->first);
		
		comparator.compare_out_and_xpct(out_data, xpct_data, test_file_pair->first);
		test_file_pair = dir_manager.next_test_pair();
	}
	tracker.output_results();
//	auto out_data = out_reader.read(input_stream_out, file_name);
//	auto xpct_data = xpct_reader.read(input_stream_xpct, file_name);
////
////	
//	TestComparator comparator{};
////	
//	bool result = comparator.comapre_out_and_xpct(out_data, xpct_data, file_name);
//	std::cout << result << std::flush;
	return 0;
}
