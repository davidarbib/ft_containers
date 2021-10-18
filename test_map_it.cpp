#include "map.hpp"
#include <map>
#include <iostream>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

int main()
{
	TESTED_NS::map<int, int> mp;
	
	std::cout << mp.insert(TESTED_NS::make_pair(4, 42)).first->first << std::endl;
	mp.insert(TESTED_NS::make_pair(1, 42));
	TESTED_NS::map<int, int>::iterator mit = mp.begin();

	for (; mit != mp.end(); mit++)
		std::cout << mit->first << std::endl;
	
	std::cout << "---------------------------------------" << std::endl;

	for (mit = --mp.end(); mit != mp.begin(); mit--)
		std::cout << mit->first << std::endl;
	std::cout << mit->first << std::endl;

	return 0;
}
