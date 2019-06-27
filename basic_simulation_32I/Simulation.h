#ifndef SIMULATION_H
#define SIMULATION_H

#include "Include/Memory.h"
#include "Include/Registers.h"
#include "InputManager.h"
#include "OutputManager.h"
#include "Include/Utilities.h"
#include "Include/BinaryUtils.h"
#include "Include/ExecutionEnvironment.h"

#include <tuple>
#include <iostream>
#include <optional>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace risc
{
//	enum SimulationMode
//	{
//		NOT_STARTED, RUNNING, PAUSED, STOPPED
//	};
	
	template<typename Core>
	struct Simulation
	{
		Simulation(Core&& execution, OutputManager&& output_manager) : core(std::move(execution)), output_manager_(std::move(output_manager)), input_manager_(InputManager{}){ }
		
		Simulation(Core&& execution) : core(std::move(execution)), input_manager_(InputManager{}) { }
		
//		template<typename std::enable_if<std::is_default_constructible<Core>::value, int>::type = 0>
		Simulation(OutputManager&& output_manager) : core(Core{}), output_manager_(std::move(output_manager)), input_manager_(InputManager{}) { }
		
		void set_output_manager(OutputManager&& output_manager)
		{
			this->output_manager_ = std::move(output_manager);
		}
		
		virtual void setup_test(const char * file_name)
        {
		    try
			{
		    	
		    	this->input_manager_.open_test(file_name);
			} catch(const std::exception& exception)
			{
				std::cerr << "Provided invalid file path as .in file\nException thrown: " << exception.what();
				exit(4);
			}
		    while(this->input_manager_.input_is_good())
            {
		    	auto line_bytes_opt = this->input_manager_.next_line();
		    	if(line_bytes_opt.has_value())
		    	{
			        auto location_bytes_pair = line_bytes_opt.value();
			        auto location = location_bytes_pair.first;
			        auto bytes = location_bytes_pair.second;
			        this->environment_.get_memory().fill_at(location, bytes);
				}
            }
		    this->input_manager_.close_test_file();
            this->core.init_stack_pointer(this->environment_.get_stack_location());
        }

		virtual void simulate()
		{
            try
            {
                while(!this->environment_.is_terminated())
                {

                    this->core.execute_instruction(this->environment_.get_memory());
                }

            } catch(RiscVException& exception)
			{
				this->environment_.handle_exception(exception);
			} catch(std::exception& exception)
            {
                this->environment_.handle_exception(exception);
            } catch(...)
            {
            	std::cerr << "Exception not inherited from std::exception thrown!\n";
            	throw;
			}

            std::cout << "\nSimulation finished, executed " << this->core.executed_instructions() << " instructions\nWaiting for user input..." << std::endl;
            std::string line;
            while(std::getline(std::cin, line))
            {
                if(this->output_manager_.output_and_should_terminate(line, this->core.get_registers(), this->environment_))
                {
                    std::cout << "Exiting...\n";
                    return;
                }
            }

			
		}
		protected:
			Core core;
			OutputManager output_manager_;
			InputManager input_manager_;
			ExecutionEnvironment environment_;
			
			
	};
	

	template<typename CoreType>
	auto make_simulation(CoreType&& core, OutputManager&& output_manager)
	{
		return Simulation<CoreType>{std::move(core), std::move(output_manager)};
	}
	
	template<typename CoreType>
	auto make_simulation(CoreType&& core)
	{
		return Simulation<CoreType>{std::move(core)};
	}
	
//	template<typename Execution>
//	auto make_simulation(Execution&& execution, std::ostream * output_stream = &std::cout, bool owner = false)
//	{
//		return std::apply(Simulation::Simulation, std::forward_as_tuple(execution, OutputManager{output_stream, owner}));
//	}
}


#endif
