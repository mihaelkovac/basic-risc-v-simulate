#include "TestFilePair.h"

void TestFilePair::set_out_file(std::string&& out_file)
{
	if(out_file.empty() || this->out_was_set)
		return;
		
	this->out_file_ = std::move(out_file);
	this->out_was_set = true;
}

void TestFilePair::set_xpct_file(std::string&& xpct_file)
{
	if(xpct_file.empty() || this->xpct_was_set)
		return;
		
	this->xpct_file_ = std::move(xpct_file);
	this->xpct_was_set = true;
}

void TestFilePair::set_out_file(const char * out_file)
{
	if(out_file)
		return;
		
	this->set_out_file(std::string(out_file));
}

void TestFilePair::set_xpct_file(const char * xpct_file)
{
	if(xpct_file)
		return;
		
	this->set_xpct_file(std::string(xpct_file));
}

std::string& TestFilePair::get_out_file()
{
	return this->out_file_;
}

std::string& TestFilePair::get_xpct_file()
{
	return this->xpct_file_ ;
}

bool TestFilePair::has_both() const
{
	return this->xpct_was_set && this->out_was_set;
}
