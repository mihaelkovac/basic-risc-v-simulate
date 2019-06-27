#ifndef RISCVEXCEPTION_H
#define RISCVEXCEPTION_H

#include <stdexcept>
#include <string_view>

namespace risc
{
	
	struct RiscVException : public std::exception
	{
		
		virtual const char * what() const throw()
		{
			return message_.c_str();
		}

		virtual std::string_view risc_exception_type()
        {
		    return std::string_view(message_.c_str(), type_position);
        }
		

        RiscVException(std::string&& type, std::string&& message)
        {
            this->type_position = type.length();
            this->message_ = std::move(std::move(type) + " -- " + std::move(message));
        }
		
		private:
			std::string message_;
		    int type_position;

	};


}

#endif
