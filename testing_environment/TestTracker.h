#ifndef TESTTRACKER_H
#define TESTTRACKER_H

#include <string>
#include <unordered_map>
#include <cstdint>
#include "TestResult.h"

struct TestTracker
{
	
	TestTracker() = default;
	TestTracker(TestTracker&& tracker) : results(std::move(tracker.results)), current_test(std::move(tracker.current_test)), passed_tests(tracker.passed_tests)
	{
		tracker.passed_tests = 0;
	}
	void set_current_test(const std::string_view& name) noexcept;
	void test_finished();
	void add_message(std::string&& message);
	void output_results() noexcept;
	private:
		std::vector<TestResult> results;
		TestResult current_test;
		std::size_t passed_tests = 0;
	
};

#endif
