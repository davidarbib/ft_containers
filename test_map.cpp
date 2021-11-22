#include "map.hpp"
#include <map>
#include <iostream>
#include "print_pair.hpp" //TODO delete before evaluation

//#define TESTED_NS ft

#ifndef TESTED_NS
# define TESTED_NS std
#endif

template <class Key, class T>
void	print(TESTED_NS::map<Key, T>& lst)
{
	for (typename TESTED_NS::map<Key, T>::iterator it = lst.begin();
			it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

template <class Key, class T>
void	printPair(TESTED_NS::pair<Key, T>& pair)
{
	std::cout << pair.first << ", " << pair.second << std::endl;
}

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
	std::cout << mp.empty() << std::endl;
	std::cout << mp.size() << std::endl;
	mp.insert(TESTED_NS::make_pair(1, 1));
	std::cout << mp.empty() << std::endl;
	std::cout << mp.size() << std::endl;
	mp.erase(1);
	std::cout << mp.empty() << std::endl;
	std::cout << mp.size() << std::endl;
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

	/*
	itlow = mymap.lower_bound('k');
	itup = mymap.upper_bound('k');

	std::cout << "results for inexistant elem :" << std::endl;
	std::cout << itlow->first << ", " << itlow->second << std::endl;
	std::cout << itup->first << ", " << itup->second << std::endl;
	std::cout << "*****************************" << std::endl;
	*/

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

void
test_ctors_assign(void)
{
	TESTED_NS::map<char,int> mp_src;
	
	mp_src['a'] = 4;
	mp_src['b'] = 5;
	mp_src['c'] = 6;
	mp_src['d'] = 7;

	for (TESTED_NS::map<char,int>::iterator it=mp_src.begin();
			it!=mp_src.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "copy of map : " << std::endl;

	TESTED_NS::map<char,int> mp_dest(mp_src);
	for (TESTED_NS::map<char,int>::iterator it=mp_src.begin();
			it!=mp_src.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "------------------range ctor----------------------" << std::endl;

	TESTED_NS::map<char,int> mp_range(mp_src.begin(), mp_src.end());
	for (TESTED_NS::map<char,int>::iterator it=mp_range.begin();
			it!=mp_range.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	std::cout << "--------------------assign----------------------" << std::endl;
	
	TESTED_NS::map<char,int> mp_src2;
	
	mp_src2['a'] = 41;
	mp_src2['b'] = 51;
	mp_src2['c'] = 61;
	mp_src2['d'] = 71;
	mp_src2['e'] = 81;
	mp_src2['f'] = 91;

	mp_dest = mp_src2;	

	for (TESTED_NS::map<char,int>::iterator it=mp_src2.begin();
			it!=mp_src2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void
test_swap(void)
{
	TESTED_NS::map<char,int> mp1;
	mp1['a'] = 41;
	mp1['b'] = 51;
	mp1['c'] = 61;
	mp1['d'] = 71;
	mp1['e'] = 81;
	mp1['f'] = 91;

	TESTED_NS::map<char,int> mp2;
	mp2['a'] = 42;
	mp2['b'] = 52;
	mp2['c'] = 62;
	mp2['d'] = 72;
	mp2['e'] = 82;
	mp2['f'] = 92;
	
	std::cout << "------------before swap-------------" << std::endl;
	std::cout << std::endl;
	for (TESTED_NS::map<char,int>::iterator it=mp1.begin();
			it!=mp1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << std::endl;

	for (TESTED_NS::map<char,int>::iterator it=mp2.begin();
			it!=mp2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mp1.swap(mp2);

	std::cout << "------------after swap-------------" << std::endl;
	std::cout << std::endl;
	for (TESTED_NS::map<char,int>::iterator it=mp1.begin();
			it!=mp1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << std::endl;

	for (TESTED_NS::map<char,int>::iterator it=mp2.begin();
			it!=mp2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

int test_erase_hbaudet()
{
	TESTED_NS::map<char,int> mymap;
	TESTED_NS::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

//	mymap.tree().print_tree();
	it=mymap.find('b');
	std::cout << "found b\n";
	mymap.erase (it);                   // erasing by iterator
	std::cout << "erase iterator to b\n";
	mymap.erase ('c');                  // erasing by key
	std::cout << "erase by key 'c'\n";
	it=mymap.find ('e');
	std::cout << "erase by range 'e' to end\n";
	mymap.erase ( it, mymap.end() );    // erasing by range

	std::cout << " display :\n";
	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}

void
test_at_find(void)
{
	TESTED_NS::map<int, int> mp;
	mp[1] = 23;
	mp[2] = 24;
	mp[3] = 25;
	mp[4] = 26;
	mp[5] = 27;
	mp[6] = 28;
	mp[7] = 29;
	mp[8] = 210;
	int idx = 4;
	std::cout << "at " << idx << " there is " << mp.at(idx) << std::endl;
	int noidx = 100;
	try
	{
		std::cout << "at " << noidx << " there is " << mp.at(noidx);
		std::cout << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	printPair(*(mp.find(6)));
	std::cout << (mp.end() == mp.find(0)) << std::endl;
	std::cout << (mp.end() == mp.find(10)) << std::endl;
}

void
test_reverseit(void)
{
	TESTED_NS::map<char,int> mp;

	mp['a'] = 100;
	mp['b'] = 200;
	mp['c'] = 300;

	TESTED_NS::map<char,int>::reverse_iterator rit;
	for (rit=mp.rbegin(); rit!=mp.rend(); ++rit)
		printPair(*rit);
}

void
test_count(void)
{
	int count = 10;
	TESTED_NS::map<char,int> mp;
	char c = 'a';

	for (int i = 0; i < count; i++)
		mp[c + i]= i;

	for (c='a'; c<'z'; c++)
	{
		std::cout << c;
		if (mp.count(c)>0)
			std::cout << " is an element of mp.\n";
		else 
			std::cout << " is not an element of mp.\n";
	}
}

void
test_empty(void)
{
	TESTED_NS::map<int,int> mp;
	int count = 10;

	std::cout << "mp is empty : " << mp.empty() << std::endl;

	for (int i = 0; i < count; i++)
		mp[i]= 100 + i;
	
	std::cout << "mp is empty : " << mp.empty() << std::endl;

	mp.clear();

	std::cout << "mp is empty : " << mp.empty() << std::endl;
}

void
test_getallocator(void)
{
	TESTED_NS::map<char,int> mp;
	TESTED_NS::pair<const char,int>* p;

	p=mp.get_allocator().allocate(5);
	mp.get_allocator().deallocate(p,5);
}

void
test_keycomp(void)
{
	int count = 10;
	TESTED_NS::map<int,int> mp;
	for (int i = 0; i < count; i++)
		mp[i] = 100 + i;
	for (TESTED_NS::map<int,int>::iterator it = mp.begin();
			mp.key_comp()(it->first, count / 2);
			it++)
		printPair(*it);
}

void
test_valuecomp(void)
{
	TESTED_NS::map<char,int> mp;

	mp['a']=1;
	mp['b']=2;
	mp['c']=3;

	std::cout << mp.value_comp()(*mp.begin(), *(++mp.begin())) << std::endl;
}

void
test_relational(void)
{
	int count = 10;
	TESTED_NS::map<char, int> mp;
	TESTED_NS::map<char, int> mp2;

	for (int i = 0; i < count; i++)
	{
		mp['a' + i] = i;
		mp2['a' + (i * 2)] = i;
	}
	std::cout << (mp < mp2) << std::endl;
	std::cout << (mp <= mp2) << std::endl;
	std::cout << (mp > mp2) << std::endl;
	std::cout << (mp >= mp2) << std::endl;
	std::cout << (mp == mp2) << std::endl;
	std::cout << (mp != mp2) << std::endl;
}

void
test_nonmemberswap()
{
	TESTED_NS::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	swap(foo,bar);

	std::cout << "foo contains:\n";
	for (TESTED_NS::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (TESTED_NS::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

int main()
{
#ifdef FT 
	std::cout << "Namespace tested : ft" << std::endl;
#else
	std::cout << "Namespace tested : std" << std::endl;
#endif
	std::cout << "---------------- insert ------------------" << std::endl;
	test_insert();
	std::cout << "---------------- erase ------------------" << std::endl;
	test_erase();
	std::cout << "---------------- clear ------------------" << std::endl;
	test_clear();
	std::cout << "---------------- operator[] ------------------" << std::endl;
	test_brackets_op();
	std::cout << "---------------- lower/upper/equal range ------------------" << std::endl;
	test_bounds_range();
	std::cout << "---------------- ctors/assign ------------------" << std::endl;
	test_ctors_assign();
	std::cout << "---------------- swap ------------------" << std::endl;
	test_swap();
	std::cout << "---------------- at/find ------------------" << std::endl;
	test_at_find();
	std::cout << "---------------- reverse it ------------------" << std::endl;
	test_reverseit();
	std::cout << "---------------- count ------------------" << std::endl;
	test_count();
	std::cout << "---------------- empty ------------------" << std::endl;
	test_empty();
	std::cout << "---------------- keycomp ------------------" << std::endl;
	test_keycomp();
	std::cout << "---------------- valuecomp ------------------" << std::endl;
	test_valuecomp();
	std::cout << "---------------- relational ------------------" << std::endl;
	test_relational();
	std::cout << "---------------- non member swap ------------------" << std::endl;
	test_nonmemberswap();
	//while (1) {};
	return 0;
}
