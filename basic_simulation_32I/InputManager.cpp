#include "InputManager.h"
#include <string>
#include <stdexcept>
#include <optional>
#include <vector>
#include <iostream>

namespace risc
{
	
	InputManager::~InputManager()
	{
		if(input_stream.is_open())
        {
		    input_stream.close();
        }
	}

	void InputManager::open_test(const char * file_location)
    {
        this->input_stream.open(file_location);
    }

    void InputManager::close_test_file()
    {
	    if(input_stream)
        {
	        this->input_stream.close();
        }
    }

    std::optional<std::pair<std::size_t, std::vector<byte>>> InputManager::next_line()
	{
		std::string line;
		if(this->input_stream.good() && std::getline(this->input_stream, line))
		{
		    if(std::regex_match(line, comment_rgx) || line.empty())
            {
		        return std::nullopt;
            }
		    std::smatch m;
            if(std::regex_match(line, m, mem_rgx))
            {
                std::stringstream formatter{};
                formatter << m.str(1);
                std::size_t location;
                formatter >> location;
                auto binary = m.str(2);
                auto n = binary.size();
//                if(n % 8)
//                {
//                    throw std::runtime_error("Invalid size of line, has to be divisible by 8");
//                }
                unsigned int size = n / 8;

                std::vector<byte> bytes(size);

                for(int i = 0; i < n; ++i)
                {
                    bytes[i / 8] |= (binary.at(n - i - 1) - '0') << (i % 8);
                }
                return std::make_optional(std::make_pair(location, std::move(bytes)));
            } else
            {
                std::cerr << "Skipping line \"" << line << "\" --> doesn't match the required format 'mem_location:binary_value'\n";
            }
		}
		return std::nullopt;
	}
	
	std::optional<std::string> InputManager::read_input() const
	{
		std::string line;
		if(std::getline(std::cin, line))
		{
			return std::make_optional(line);
		}
		
		return std::nullopt;
		
	}
	
	bool InputManager::input_is_good() const
	{
		return this->input_stream.good();
	}

}
