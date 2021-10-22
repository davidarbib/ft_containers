#include "map.hpp"
#include <map>
#include <iostream>
#include "print_pair.hpp" //TODO delete before evaluation

#ifndef TESTED_NS
# define TESTED_NS std
#endif

void
test_insert(void)
{
	TESTED_NS::map<int, int> mp;
	
	mp.insert(TESTED_NS::make_pair(4, 42));
	mp.insert(TESTED_NS::make_pair(1, 42));
	mp.insert(TESTED_NS::make_pair(1, 21));
	TESTED_NS::map<int, int>::iterator mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << "---------------------------------------" << std::endl;

	for (mit = --mp.end(); mit != mp.begin(); mit--)
		std::cout << mit->first << ", " << mit->second << std::endl;
	
	std::cout << "----------tests direct insertion-------------" << std::endl;

	mit = mp.begin();
	mit++;
	mit = mp.insert(mit, TESTED_NS::make_pair(5, 100));
	std::cout << "insert return value : ";
	std::cout << mit->first << ", " << mit->second << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	mit = mp.begin();
	mit = mp.insert(mit, TESTED_NS::make_pair(3, 82));
	std::cout << "insert return value : ";
	std::cout << mit->first << ", " << mit->second << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
}

int main()
{
	test_insert();
	return 0;
}
