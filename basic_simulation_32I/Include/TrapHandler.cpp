#include "TrapHandler.h"

namespace risc
{

    std::optional<std::string> TrapHandler::get_thrown_risc_v_exception() noexcept
    {
    	if(this->risc_exception_was_thrown)
    	{
        	return std::make_optional(this->thrown_risc_v_exception);
		}
		return std::nullopt;
    }


}
