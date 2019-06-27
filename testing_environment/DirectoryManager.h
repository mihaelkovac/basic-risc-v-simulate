#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <string>
#include <string_view>
#include <vector>
#include <dirent.h>
#include <algorithm>
#include <map>
#include <utility>
#include <optional>
#include "TestFilePair.h"


struct DirectoryManager
{
	DirectoryManager(const char * dir_name);
	DirectoryManager(const std::string& dir_name) : DirectoryManager(dir_name.data()) { }
	std::optional<std::pair<std::string, TestFilePair>> next_test_pair();
	private:
		std::string dir_name;
		int current_sub_dir = -1;
		std::vector<DirectoryManager> sub_directory_managers{};
		std::map<std::string, TestFilePair> file_pairs{};
		std::map<std::string, TestFilePair>::const_iterator current;
		
		void map_file_names(DIR * dir);
		void clear_invalid_file_pairs();
		
		
		
		static constexpr std::string_view out_extension = ".out";
		static constexpr std::string_view xpct_extension = ".xpct";
		
		static inline bool ends_with(const std::string_view& value, const std::string_view& ending)
		{
			if(ending.length() > value.length())
				return false;
			return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
		}
};


DirectoryManager make_directory_manager(const char * dir_name);

#endif
