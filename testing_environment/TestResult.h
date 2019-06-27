#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <string>
#include <string_view>
#include <vector>

struct TestResult
{
	
	TestResult() = default;
	TestResult(TestResult&& result);
	TestResult(const std::string_view& test_name) : test_name_(test_name) {}
	bool has_passed() const noexcept;
	std::vector<std::string>& fail_messages() noexcept;
	std::string_view& name_of_test() noexcept;
	bool empty() noexcept;
	TestResult& operator=(TestResult&& result) noexcept
	{
		this->failure_messages = std::move(result.failure_messages);
		this->test_name_ = std::move(result.test_name_);
		return *this;
	}
	private:
		std::vector<std::string> failure_messages{};
		std::string_view test_name_{};
};

#endif
