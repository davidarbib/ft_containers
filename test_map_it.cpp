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

	std::cout << "----------range insert-------------" << std::endl;
	
	TESTED_NS::map<int, int> mp_dest;
	
	std::cout << "mp_dest before " << std::endl;
	std::cout << std::endl;
	mp_dest.insert(TESTED_NS::make_pair(7, 777));
	mp_dest.insert(TESTED_NS::make_pair(0, 777));
	mp_dest.tree().print_tree();
	mit = mp_dest.begin();
	for (; mit != mp_dest.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << "mp_dest after " << std::endl;
	std::cout << std::endl;

	mp_dest.insert(mp.begin(), mp.end());
	mp_dest.tree().print_tree();
	mit = mp_dest.begin();
	for (; mit != mp_dest.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
}

void
test_erase()
{
	TESTED_NS::map<int, int> mp;
	
	mp.insert(TESTED_NS::make_pair(4, 42));
	mp.insert(TESTED_NS::make_pair(1, 42));
	mp.insert(TESTED_NS::make_pair(1, 21));
	TESTED_NS::map<int, int>::iterator mit;

	std::cout << "before erase" << std::endl;
	std::cout << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
	
	mp.erase(mp.begin());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << std::endl;
	std::cout << "----------range erase-----------" << std::endl;
	std::cout << std::endl;
	
	mp.insert(mit, TESTED_NS::make_pair(5, 100));
	mp.insert(mit, TESTED_NS::make_pair(7, 72));
	mp.insert(mit, TESTED_NS::make_pair(65, 02));

	std::cout << "before erase" << std::endl;
	std::cout << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	mp.erase(mp.find(5), mp.find(7));

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << std::endl;
	std::cout << "----------clear erase-----------" << std::endl;
	std::cout << std::endl;

	mp.erase(mp.find(4), mp.end());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
}

void
test_clear()
{
	TESTED_NS::map<int, int> mp;
	mp.insert(ft::make_pair(1, 1));
	mp.erase(1);
}

void
test_erase_isolated()
{
	TESTED_NS::map<int, int> mp;
	
	mp.insert(TESTED_NS::make_pair(4, 42));
	mp.insert(TESTED_NS::make_pair(1, 42));
	mp.insert(TESTED_NS::make_pair(1, 21));
	TESTED_NS::map<int, int>::iterator mit;

	std::cout << "before erase" << std::endl;
	std::cout << std::endl;
	mp.tree().print_tree();
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
	
	mp.erase(mp.begin());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
}

void
test_brackets_op(void)
{
	TESTED_NS::map<char, int> mp;

	mp['a'] = 42;
	mp['b'] = 43;
	mp['c'] = 44;
	mp['d'] = 45;

	TESTED_NS::map<char, int>::iterator mit;

	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
	
	std::cout << mp['b'] << std::endl;
}

int main()
{
	//test_insert();
	//test_erase();
	//test_clear();
	//test_erase_isolated();
	test_brackets_op();
	while (1) {};
	return 0;
}
