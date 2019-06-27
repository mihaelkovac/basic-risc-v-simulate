#include "OutputManager.h"



namespace risc
{
	OutputManager::~OutputManager()
	{
		if(is_owner_ && this->output_ != nullptr)
		{

			delete output_;
		}
	}
	
	void OutputManager::dump_memory(Memory& memory, std::size_t from)
	{
		dump_memory(memory, from, memory.size());		
	}
	
	void OutputManager::dump_memory(Memory& memory, std::size_t from, std::size_t to)
	{
		//Adjust to memory a 4-byte memory location
		from += from % 4;
		to += to % 4;
		
		for(; from < to; from+=4)
		{
            auto location_value = memory.from_location_as<uint32_t>(from);
			(*output_) << from << ':' << std::left << std::setw(16) << location_value << "hex:" << std::hex << location_value << '\n' << std::dec;
		}
	}

	void OutputManager::set_output_stream(std::ostream * output, bool is_owner)
	{
		if(this->is_owner_ && this->output_ != nullptr)
		{
			delete this->output_;
		}
		this->output_ = std::move(output);
		this->is_owner_ = is_owner;
	}
	
	void OutputManager::output_exception(ExecutionEnvironment& environment)
	{
		auto except_opt = environment.thrown_risc_v_exception();
		if(except_opt.has_value())
		{
			(*output_) << "thrown exception: " << except_opt.value() << '\n';
		} else 
		{
			std::cerr << "No exception was thrown\n";
		}
	}
	
	
}
