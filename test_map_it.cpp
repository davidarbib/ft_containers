#include "map.hpp"
#include "map_iterator.hpp"
#include <map>
#include <iostream>

int main()
{
	ft::map<int, int> mp;
	ft::map<int, int>::iterator mit = mp.begin();
	
	for (; mit != mp.end(); mit++)
		std::cout << mit->nb << std::endl;
	
	std::cout << "---------------------------------------" << std::endl;

	for (mit = --mp.end(); mit != mp.begin(); mit--)
		std::cout << mit->nb << std::endl;

	return 0;
}
