#include "map.hpp"
#include "map_iterator.hpp"
#include <map>
#include <iostream>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

int main()
{
	TESTED_NS::map<int, int> mp;
	
	mp.insert(TESTED_NS::make_pair(4, 42));
	TESTED_NS::map<int, int>::iterator mit = mp.begin();
	TESTED_NS::map<int, int>::value_type pair = *mit;
	std::cout << pair.first << std::endl;

	/*
	for (; mit != mp.end(); mit++)
		std::cout << mit->nb << std::endl;
	
	std::cout << "---------------------------------------" << std::endl;

	for (mit = --mp.end(); mit != mp.begin(); mit--)
		std::cout << mit->nb << std::endl;
	*/

	return 0;
}
