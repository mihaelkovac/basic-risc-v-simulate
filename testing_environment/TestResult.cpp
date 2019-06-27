#include "TestResult.h"

TestResult::TestResult(TestResult&& result)
{
	this->failure_messages = std::move(result.failure_messages);
	this->test_name_ = std::move(result.test_name_);
}

bool TestResult::has_passed() const noexcept
{
	return this->failure_messages.empty();
}

std::vector<std::string>& TestResult::fail_messages() noexcept
{
	return this->failure_messages;
}

std::string_view& TestResult::name_of_test() noexcept
{
	return this->test_name_;
}

bool TestResult::empty() noexcept
{
	return this->test_name_.empty() && this->fail_messages().empty();
}

