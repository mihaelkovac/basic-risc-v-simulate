#ifndef RISC_V_EXECUTIONENVIRONMENT_H
#define RISC_V_EXECUTIONENVIRONMENT_H

#include <cstdint>
#include "TrapHandler.h"
#include "Memory.h"


namespace risc
{
	
//	enum PrivilegeMode
//	{
//
//	};
	
	struct ExecutionEnvironment
	{
	    ExecutionEnvironment(std::size_t stack_location = 63996);
//	    ExecutionEnvironment() = default;
	    template<typename Exception>
	    void handle_exception(Exception& exception)
	    {
	    	this->terminate_ = true;
	    	this->handler.handle_trap(exception);
		}
	    
		bool is_terminated() const noexcept;
	    
		Memory& get_memory() noexcept;

        std::optional<std::string> thrown_risc_v_exception() noexcept;

        std::size_t get_stack_location() noexcept;

        void set_stack_location(std::size_t stack_location) noexcept;

        std::size_t memory_size() const noexcept;

	private:
	    TrapHandler handler;
	    Memory memory{};
	    bool terminate_;
	    std::size_t stack_loc;
	};

}

#endif 
