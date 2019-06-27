#ifndef RISC_V_TRAPHANDLER_H
#define RISC_V_TRAPHANDLER_H

#include <type_traits>
#include <optional>
#include "RiscVException.h"
#include <iostream>

namespace risc
{
	
	struct TrapHandler
	{
	    void handle_trap(RiscVException& exception)
	    {
	    	std::cerr << exception.what() << '\n';
	    	this->risc_exception_was_thrown = true;
            thrown_risc_v_exception = std::move(exception.risc_exception_type());
		}
		
	    void handle_trap(std::exception& exception)
	    {
	    	std::cerr << "Non-RISC-V exception thrown -- there is probably an error in the code\n" << exception.what() << "\nTerminating simulation\n";
	    	exit(5);
		}

		std::optional<std::string> get_thrown_risc_v_exception() noexcept;

	private:
	    std::string thrown_risc_v_exception;
	    bool risc_exception_was_thrown = false;
	};
	
}


#endif //RISC_V_TRAPHANDLER_H
