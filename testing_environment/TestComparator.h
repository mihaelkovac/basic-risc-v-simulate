#ifndef TESTCOMPARATOR_H
#define TESTCOMPARATOR_H

#include "ExpectedData.h"
#include "OutData.h"
#include "TestTracker.h"
#include <string_view>

struct TestComparator
{
	TestComparator(TestTracker& tracker) : tracker_(tracker) { }
	virtual void compare_out_and_xpct(OutData& out_data, ExpectedData& exp_data, const std::string& file_name);
	private:
		TestTracker& tracker_;
};

#endif
