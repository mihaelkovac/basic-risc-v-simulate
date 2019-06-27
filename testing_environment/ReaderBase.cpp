#include "ReaderBase.h"

//template<unsigned int N>
//void iterate_and_replace_all_placeholders(std::string& iteratee, const std::pair<std::string_view&&, std::string_view&> (&place_holders)[N])
//{
//	for(auto& place_holder_pair : place_holders)
//	{
//		auto pos = iteratee.find(place_holder_pair.first);
//		if(pos != std::string::npos)
//		{
//			iteratee.replace(pos, place_holder_pair.first.length(), place_holder_pair.second);
//		}
//	}
//	
//}
