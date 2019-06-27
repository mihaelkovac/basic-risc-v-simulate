#ifndef READMODE_H
#define READMODE_H

#include <array>

enum ReadMode
{
	hex = 0,
	dec = 1
};


struct ReadModeHolder
{
	ReadModeHolder() = delete;
	static constexpr std::array<std::string_view, 2> read_mode_rgxs = {"[0-9a-fA-F]+", "-?\\d+"};
};

#endif
