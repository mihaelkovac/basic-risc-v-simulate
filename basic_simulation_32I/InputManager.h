#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <regex>
#include <utility>

#include "Include/BinaryUtils.h"

namespace risc 
{
	
	struct InputManager
	{
		InputManager() = default;
		InputManager(std::ifstream&& input_file_stream) : input_stream(std::move(input_file_stream)) {}
		InputManager(InputManager&& manager)
		{
			this->input_stream = std::move(manager.input_stream);
		}
		~InputManager();
		std::optional<std::pair<std::size_t, std::vector<byte>>> next_line();
		void open_test(const char * file_location);
		std::optional<std::string> read_input() const;
		void close_test_file();
		bool input_is_good() const;
		
		private:
			std::ifstream input_stream{};
			static inline const std::regex mem_rgx{"(\\d+):([0-1]+)"};
            static inline const std::regex comment_rgx{"\\/\\/.*"};

	};


}



#endif
