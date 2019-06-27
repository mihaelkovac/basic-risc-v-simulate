#include "ExecutionEnvironment.h"

namespace risc
{
	ExecutionEnvironment::ExecutionEnvironment(std::size_t stack_location)
	{
	    this->stack_loc = stack_location;
	}

	bool ExecutionEnvironment::is_terminated() const noexcept
	{
		return this->terminate_;
	}
	
	Memory& ExecutionEnvironment::get_memory() noexcept
	{
		return this->memory;
    }

    std::optional<std::string> ExecutionEnvironment::thrown_risc_v_exception() noexcept
    {
	    return this->handler.get_thrown_risc_v_exception();
    }

    std::size_t ExecutionEnvironment::get_stack_location() noexcept
    {
	    return this->stack_loc;
    }

    void ExecutionEnvironment::set_stack_location(std::size_t stack_location) noexcept
    {
	    this->stack_loc = stack_location;
	}

	std::size_t ExecutionEnvironment::memory_size() const noexcept
    {
	    return this->memory.size();
    }

}
