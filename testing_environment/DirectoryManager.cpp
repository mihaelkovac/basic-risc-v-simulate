#include "DirectoryManager.h"
#include <dirent.h>
#include <stdexcept>
#include <iostream>

DirectoryManager::DirectoryManager(const char * dir_name)
{
	std::cout << "Preparing tests from directory: " << dir_name << '\n';
	DIR * dir_in = opendir(dir_name);
	if(!dir_in)
	{
		throw std::runtime_error("DirectoryManager could not open specified directory");
	}
	this->dir_name = std::string{dir_name};
	map_file_names(dir_in);
	closedir(dir_in);
	clear_invalid_file_pairs();
	this->current = this->file_pairs.cbegin();
}


#ifdef linux
#include <sys/stat.h>
#incldue <sys/types.h>
#include <unistd.h>

void DirectoryManager::map_file_names(DIR * dir)
{
	struct dirent * dp;
	while((dp = readdir(dir)))
	{

		struct stat statbuf;
		std::string_view file_name{this->dir_name + dp->d_name};
		if(stat(file_name.data(), &statbuf))
		{
			if(S_ISDIR(statbuf.st_mode))
			{
				this->sub_directory_managers.emplace_back(DirectoryManager(this->dir_name + '/' + dp->d_name));
				
			} else
			{
				
				if(ends_with(file_name, out_extension))
				{
					std::string name_without_extension{dp->d_name, file_name.length() - out_extension.length()};
					
					auto file_pair_it = this->file_pairs.find(name_without_extension);
					if(file_pair_it == this->file_pairs.end())
					{
						TestFilePair file_pair{};
						file_pair.set_out_file(this->dir_name + '/' + dp->d_name);
						this->file_pairs[name_without_extension] = file_pair;
					} else
					{
						file_pair_it->second.set_out_file(this->dir_name + '/' + dp->d_name);
					}
					
					
				} else if(ends_with(file_name, xpct_extension))
				{
					std::string name_without_extension{dp->d_name, file_name.length() - xpct_extension.length()};
					auto file_pair_it = this->file_pairs.find(name_without_extension);
					if(file_pair_it == this->file_pairs.end())
					{
						TestFilePair file_pair{};
						file_pair.set_xpct_file(this->dir_name + '/' + dp->d_name);
						this->file_pairs[name_without_extension] = file_pair;
					} else
					{
						file_pair_it->second.set_xpct_file(this->dir_name + '/' + dp->d_name);
					}
				}
				
			} 
			
			
		}
	}
	std::cout << std::endl;
}

#elif _WIN32
//#include <fileapi.h>
#include <windows.h>

void DirectoryManager::map_file_names(DIR * dir)
{
	struct dirent * dp;
	while((dp = readdir(dir)))
	{
		
		auto file_name_str = this->dir_name + '\\' + dp->d_name;
		std::string_view file_name{dp->d_name};
		if(ends_with(file_name, ".") || ends_with(file_name, ".."))
		{
			continue;
		}
		auto attributes = GetFileAttributes(file_name_str.c_str());
		if(attributes == INVALID_FILE_ATTRIBUTES)
		{
			std::cerr << "Invalid file " << file_name_str << '\n';
			continue;
		}

        if(attributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            this->sub_directory_managers.emplace_back(DirectoryManager(this->dir_name + '/' + dp->d_name));

        } else
		{
			if(ends_with(file_name, out_extension))
			{
				std::string name_without_extension{dp->d_name, file_name.length() - out_extension.length()};
				
				auto file_pair_it = this->file_pairs.find(name_without_extension);
				if(file_pair_it == this->file_pairs.end())
				{
					TestFilePair file_pair{};
					file_pair.set_out_file(std::move(file_name_str));
					this->file_pairs[name_without_extension] = file_pair;
				} else
				{
					file_pair_it->second.set_out_file(std::move(file_name_str));
				}
				
				
			} else if(ends_with(file_name, xpct_extension))
			{
				std::string name_without_extension{dp->d_name, file_name.length() - xpct_extension.length()};
				auto file_pair_it = this->file_pairs.find(name_without_extension);
				if(file_pair_it == this->file_pairs.end())
				{
					TestFilePair file_pair{};
					file_pair.set_xpct_file(std::move(file_name_str));
					this->file_pairs[name_without_extension] = file_pair;
				} else
				{
					file_pair_it->second.set_xpct_file(std::move(file_name_str));
				}
			}
			
		}
	}
	std::cout << std::endl;
}

#else
static_assert(1 == 0, "ERROR! - PLATFORM/OS NOT SUPPORTED!");
#endif

void DirectoryManager::clear_invalid_file_pairs()
{
	for(auto it = this->file_pairs.cbegin(); it != this->file_pairs.cend();)
	{
		if(!it->second.has_both())
		{
			it = this->file_pairs.erase(it);
		} else
		{
			++it;
		}
	}
	if(this->file_pairs.empty())
	{
		this->current_sub_dir++;
	}
}

std::optional<std::pair<std::string, TestFilePair>> DirectoryManager::next_test_pair()
{
	if(this->current_sub_dir != -1)
	{
		if(this->current_sub_dir >= this->sub_directory_managers.size())
		{
			return std::nullopt;
		}
		
		return this->sub_directory_managers[this->current_sub_dir].next_test_pair();
	}
	if(this->current == this->file_pairs.cend())
	{
		this->current_sub_dir++;
		return this->next_test_pair();
	}
	auto result = std::make_pair(this->dir_name + '\\' + this->current->first, std::move(this->current->second));
	this->current++;
	return {result};
	
}

DirectoryManager make_directory_manager(const char * dir_name)
{
	return DirectoryManager{dir_name};
}

