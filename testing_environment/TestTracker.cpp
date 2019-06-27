#include "TestTracker.h"
#include <iostream>

void TestTracker::set_current_test(const std::string_view& name) noexcept
{
	
	this->current_test = TestResult{name};
}

void TestTracker::test_finished()
{
	if(this->current_test.has_passed())
	{
		this->passed_tests++;
	}
	
	this->results.push_back(std::move(this->current_test));
}

void TestTracker::add_message(std::string&& message)
{
	this->current_test.fail_messages().push_back(std::move(message));
}

void TestTracker::output_results() noexcept
{
	std::cout << "Passed tests " << this->passed_tests << '/' << this->results.size();
	if(this->passed_tests == this->results.size())
	{
		return;
	}
	
	std::cout << "\nFailed tests:\n";
	for(auto& result : results)
	{
		if(result.has_passed()) continue;
		
		std::cout << '\t' << result.name_of_test() << ":\n";
		for(auto& message : result.fail_messages())
		{
			std::cout << "\t\t" << message << '\n';
		}
	}
}
