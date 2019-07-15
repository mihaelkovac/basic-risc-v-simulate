#include "TestTracker.h"
#include <iostream>

void TestTracker::set_current_test(const std::string& name) noexcept
{
	
	this->current_test = TestResult{name};
}

void TestTracker::test_finished()
{
	if(this->current_test.has_passed())
	{
		this->passed_tests++;
	}
	
	this->results.insert({this->current_test.name_of_test().substr(this->current_test.name_of_test().find_last_of('\\') + 1, this->current_test.name_of_test().length()), std::move(this->current_test)});
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
	std::cout << "\nPassed tests:\n";
	for(auto& passed : results)
    {
	    if(!passed.second.has_passed()) continue;

	    std::cout << '\t' << passed.second.name_of_test() << '\n';
    }

	std::cout << "\nFailed tests:\n";
	for(auto& result : results)
	{
		if(result.second.has_passed()) continue;
		
		std::cout << '\t' << result.second.name_of_test() << '\n';
	}
}

void TestTracker::output_single_test_result(const std::string& test_name) noexcept
{
    auto found = this->results.find(test_name);
    if(found == this->results.end())
    {
        std::cout << "No test with the specified name" << '\n';
    } else if(found->second.has_passed()) {
        std::cout << "\n\tTest " << found->first << " has passed" << '\n';
    } else
    {
        auto& messages = found->second.fail_messages();
        std::cout << '\n';
        for(auto& message : messages)
        {
            std::cout << '\t' << message << '\n';
        }
    }
    std::cout << std::endl;
}

bool TestTracker::all_success() noexcept
{
    return this->passed_tests == this->results.size();
}
