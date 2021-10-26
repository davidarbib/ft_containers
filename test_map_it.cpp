#include "map.hpp"
#include <map>
#include <iostream>
#include "print_pair.hpp" //TODO delete before evaluation

//#define TESTED_NS ft

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
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	mit = mp.begin();
	mit = mp.insert(mit, TESTED_NS::make_pair(3, 82));
	std::cout << "insert return value : ";
	std::cout << mit->first << ", " << mit->second << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << "----------range insert-------------" << std::endl;
	
	TESTED_NS::map<int, int> mp_dest;
	
	std::cout << "mp_dest before " << std::endl;
	std::cout << std::endl;
	mp_dest.insert(TESTED_NS::make_pair(7, 777));
	mp_dest.insert(TESTED_NS::make_pair(0, 777));
	mit = mp_dest.begin();
	for (; mit != mp_dest.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << "mp_dest after " << std::endl;
	std::cout << std::endl;

	mp_dest.insert(mp.begin(), mp.end());
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
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	mp.erase(mp.find(5), mp.find(7));

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;

	std::cout << std::endl;
	std::cout << "----------clear erase-----------" << std::endl;
	std::cout << std::endl;

	mp.erase(mp.find(4), mp.end());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	mit = mp.begin();
	for (; mit != mp.end(); mit++)
		std::cout << mit->first << ", " << mit->second << std::endl;
}

void
test_clear()
{
	TESTED_NS::map<int, int> mp;
	mp.insert(TESTED_NS::make_pair(1, 1));
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

void
test_bounds_range(void)
{
	std::cout << "----------------bounds--------------------" << std::endl;

	TESTED_NS::map<char,int> mymap;
	TESTED_NS::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound('b');  // itlow points to b
	itup=mymap.upper_bound('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (TESTED_NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "----------------equal_range--------------" << std::endl;

	TESTED_NS::map<char,int> mp2;

	mp2['a']=10;
	mp2['b']=20;
	mp2['c']=30;

	TESTED_NS::pair<TESTED_NS::map<char,int>::iterator,TESTED_NS::map<char,int>::iterator> ret;
	ret = mp2.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

int main()
{
#ifdef FT 
	std::cout << "Namespace tested : ft" << std::endl;
#else
	std::cout << "Namespace tested : std" << std::endl;
#endif
	//test_insert();
	//test_erase();
	//test_clear();
	//test_erase_isolated();
	//test_brackets_op();
	test_bounds_range();
	//while (1) {};
	return 0;
}
