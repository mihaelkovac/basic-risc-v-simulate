#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ios>
#include <bitset>
#include <cstdint>
#include <string_view>
#include <regex>
#include "Include/Registers.h"
#include "Include/ExecutionEnvironment.h"
#include "Include/Memory.h"

namespace risc
{
	
	struct OutputManager
	{
		OutputManager(std::ostream * output, bool is_owner) : output_(output), is_owner_(is_owner) { }
		OutputManager(const char * file_name)
        {
		    this->output_ = new std::ofstream(file_name);
		    this->is_owner_ = true;
        }
		OutputManager(OutputManager&& manager)
		{
			this->output_ = std::move(manager.output_);
			this->is_owner_ = manager.is_owner_;
			
			manager.output_ = nullptr;
			manager.is_owner_ = false;
		}
		OutputManager()
		{
			this->is_owner_ = false;
		};
		~OutputManager();
		
		OutputManager& operator=(OutputManager&& manager)
		{
			if(this != &manager)
			this->output_ = std::move(manager.output_);
			this->is_owner_ = manager.is_owner_;
			
			manager.output_ = nullptr;
			manager.is_owner_ = false;
			return *this;
		}
		
		template<typename RegisterType>
		void output_registers(Registers<RegisterType>& registers, int from = 0)
        {
            for(int n = registers.size(); from < n; ++from)
            {
                output_register(registers, from);
            }
        }
		
		template<typename RegisterType>
		void output_register(Registers<RegisterType>& registers, int index)
        {
			if(index >= registers.size())
			{
				std::cerr << "Cannot output register x" << index << " as it does not exist!\n";
				return;
			}
            (*output_) << std::left << 'x' << index << ':' << std::setw(12) << registers[index] << "hex:0x" << std::setw(10) << std::hex << registers[index] << "binary:" << std::bitset<sizeof(RegisterType) * 8>(registers[index]) << '\n' << std::dec;
        }
		
		template<typename RegisterType>
		void output_register_range(Registers<RegisterType>& registers, int from, int to)
        {
        	
            while(from <= to)
            {
                output_register(registers, from++);
            }
        }
		
		template<typename RegisterType>
		void output_pc(Registers<RegisterType>& registers)
        {
            auto pc = registers.pc();
            (*output_) << std::left << "pc:" << std::setw(12) << pc << "hex:0x" << std::setw(10) << std::hex << pc << "binary:" << std::bitset<sizeof(decltype(pc)) * 8>(pc) << '\n' << std::dec;
        }
		
		void dump_memory(Memory& memory, std::size_t from = 0);
		
		void dump_memory(Memory& memory, std::size_t from, std::size_t to);

		void set_output_stream(std::ostream * output, bool is_owner);
		
		void output_exception(ExecutionEnvironment& environment);
		
		template<typename Registers>
		bool output_and_should_terminate(const std::string& input, Registers& registers, ExecutionEnvironment& environment)
		{
			std::smatch m;
			std::stringstream formatter{};
			if(std::regex_match(input, m, quit_rgx))
			{
				return true;
				
			} else if(std::regex_match(input, m, dump_registers_rgx))
			{
			    auto first_cpt_group = m.str(1);
			    auto sec_cpt_group = m.str(2);
			    if(first_cpt_group.empty())
                {
			        this->output_registers(registers);
                } else if(sec_cpt_group.empty())
                {
			        formatter << first_cpt_group;
			        int from;
			        formatter >> from;
			        this->output_registers(registers, from);
                } else
                {
			        formatter << first_cpt_group << ' ' << sec_cpt_group;
			        int from, to;
			        formatter >> from;
			        formatter >> to;
			        this->output_register_range(registers, from, to);
                }
			} else if(std::regex_match(input, m, dump_single_register_rgx))
			{
				if(m.size() == 2)
				{
					formatter << m.str(1);
					int index;
					formatter >> index;
					this->output_register(registers, index);
				} else 
				{
					std::cerr << "Error invalid input for dump_single_register command -- need to input a single integer\n";
				}
			} else if(std::regex_match(input, m, dump_memory_rgx))
			{
                auto first_cpt_group = m.str(1);
                auto sec_cpt_group = m.str(2);
                if(first_cpt_group.empty())
                {
                    this->dump_memory(environment.get_memory());
                } else if(sec_cpt_group.empty())
                {
                    std::size_t to;
                    formatter << first_cpt_group;
                    formatter >> to;
                    this->dump_memory(environment.get_memory(), 0, to);
                } else
                {
                    formatter << first_cpt_group << ' ' << sec_cpt_group;
                    std::size_t from, to;
                    formatter >> from >> to;
                    this->dump_memory(environment.get_memory(), from, to);
                }

			} else if(std::regex_match(input, dump_pc_rgx))
			{
				this->output_pc(registers);
			} else if(std::regex_match(input, dump_exception_rgx))
			{
				this->output_exception(environment);
			} else
			{
				std::cerr << "OutputManager could not determine the type of output specified according to the input command \"" << input << "\" ... input 'quit' or 'exit' for termination\n";
			}
			return false;
		}
		
		private:
			std::ostream * output_{nullptr};
			bool is_owner_;
			static inline const std::regex quit_rgx{"quit|exit", std::regex_constants::icase};
			static inline const std::regex dump_registers_rgx{"dump(?:\\s+|_)registers\\s*(\\d+)?\\s*(\\d+)?", std::regex_constants::icase};
			static inline const std::regex dump_single_register_rgx{"dump(?:\\s+|_)?(?:single)?(?:\\s+|_)register\\s+(\\d+)", std::regex_constants::icase};
			static inline const std::regex dump_memory_rgx{"dump(?:\\s+|_)memory\\s*(\\d+)?\\s*(\\d+)?", std::regex_constants::icase};
			static inline const std::regex dump_pc_rgx{"dump(?:\\s+|_)pc\\s*", std::regex_constants::icase};
			static inline const std::regex dump_exception_rgx{"dump(?:\\s+|_)exception\\s*", std::regex_constants::icase};
	};

}

#endif
