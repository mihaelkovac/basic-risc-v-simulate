#include <iostream>
#include <bitset>
#include <fstream>
#include <string_view>
#include <algorithm>

#include "RISC_V_32I.h"
#include "Include/RiscVCore.h"
#include "Simulation.h"
#include "InputManager.h"
#include "OutputManager.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool ends_with(std::string_view&& str, std::string_view&& ending)
{
	if(str.length() < ending.length()) return false;
	
	return std::equal(ending.rbegin(), ending.rend(), str.rbegin());
}

int main(int argc, char** argv) 
{
	using namespace risc;
	if(!argv[1])
	{
		std::cerr << "No .in file provided as input paramater for program -- Exiting...\n";
		exit(1);
	} else if(!ends_with(std::string_view(argv[1]), ".in"))
	{
		std::cerr << "The provided file has to be an .in file -- Exiting...\n";
		exit(2);
	}
	
	auto execution = make_risc_v_core<int, R32Format, I32Format, S32Format, B32Format, U32Format, J32Format>();
	auto simulation = make_simulation(std::move(execution));
	if(argv[2])
	{
		if(!ends_with(std::string_view{argv[2]}, ".out"))
		{
			std::cerr << "The second provided argument has to be an .out file -- Exiting...\n";
			exit(3);
		}
		simulation.set_output_manager(OutputManager{argv[2]});
		
	} else 
	{
		simulation.set_output_manager(OutputManager{&std::cout, false});
	}


	simulation.setup_test(argv[1]);
	simulation.simulate();

//	system("pause");
	return 0;
}
