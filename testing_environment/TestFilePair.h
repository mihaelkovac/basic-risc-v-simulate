#ifndef TESTFILEPAIR_H
#define TESTFILEPAIR_H

#include <string>

struct TestFilePair
{
	void set_out_file(std::string&& out_file);
	void set_xpct_file(std::string&& xpct_file);
	void set_out_file(const char * out_file);
	void set_xpct_file(const char * xpct_file);
	bool has_both() const;
	std::string& get_out_file();
	std::string& get_xpct_file();
	private:
		std::string out_file_;
		std::string xpct_file_;
		bool out_was_set = false;
		bool xpct_was_set = false;
};

#endif
