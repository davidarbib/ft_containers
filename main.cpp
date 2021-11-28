#include "map.hpp"
#include <map>
#include "vector.hpp"
#include <vector>
#include "stack.hpp"
#include <stack>
#include "set.hpp"
#include <set>
#include <iostream>
#include <sys/time.h>

#ifdef FT
# define TESTED_NS ft
#else
# define TESTED_NS std
#endif

#define TIME_FACTOR 1000

int count = 20;

long	get_usec_from_epoch()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * TIME_FACTOR * TIME_FACTOR);
}

long	get_relative_us(struct timeval begin_tv)
{
	struct timeval	current_tv;
	long			sec_interval;
	long			usec_interval;

	gettimeofday(&current_tv, NULL);
	sec_interval = current_tv.tv_sec - begin_tv.tv_sec;
	usec_interval = current_tv.tv_usec - begin_tv.tv_usec;
	return (usec_interval + sec_interval * TIME_FACTOR * TIME_FACTOR);
}

long	get_relative_ms(struct timeval begin_tv)
{
	struct timeval	current_tv;
	long			sec_interval;
	long			usec_interval;

	gettimeofday(&current_tv, NULL);
	sec_interval = current_tv.tv_sec - begin_tv.tv_sec;
	usec_interval = current_tv.tv_usec - begin_tv.tv_usec;
	return (usec_interval / TIME_FACTOR + sec_interval * TIME_FACTOR);
}

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

template <class T>
void
printVec(TESTED_NS::vector<T>& vec)
{
	std::cout << "------------------------------" << std::endl;
	std::cout << "size : " << vec.size() << std::endl;
	std::cout << "elems : " << std::endl;
	for (typename TESTED_NS::vector<T>::iterator it = vec.begin();
			it != vec.end(); it++)
		std::cout << *it << std::endl;
}

namespace map_test
{
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

void
test_performance(void)
{
	count = 1000;
	struct timeval before;

	TESTED_NS::map<int, int> mp;

	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		mp.insert(TESTED_NS::make_pair(i, i * 5));
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		mp.erase(i);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::map<int, int> mp2;
	gettimeofday(&before, NULL);
	count *= 10;
	for (int i = 0; i < count; i++)
		mp2.insert(TESTED_NS::make_pair(i, i * 10));
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		mp2.erase(i);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::map<int, int> mp3;
	gettimeofday(&before, NULL);
	count *= 10;
	for (int i = 0; i < count; i++)
		mp3.insert(TESTED_NS::make_pair(i, i * 10));
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		mp3.erase(i);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;
}
}

namespace set_test
{
void
test_insert(void)
{
	TESTED_NS::set<int> st;
	
	st.insert(4);
	st.insert(1);
	st.insert(1);
	TESTED_NS::set<int>::iterator sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	std::cout << "---------------------------------------" << std::endl;

	for (sit = --st.end(); sit != st.begin(); sit--)
		std::cout << *sit << std::endl;
	
	std::cout << "----------tests direct insertion-------------" << std::endl;

	sit = st.begin();
	sit++;
	sit = st.insert(sit, 5);
	std::cout << "insert return value : ";
	std::cout << *sit << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	sit = st.begin();
	sit = st.insert(sit, 82);
	std::cout << "insert return value : ";
	std::cout << *sit << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	std::cout << "----------range insert-------------" << std::endl;
	
	TESTED_NS::set<int> st_dest;
	
	std::cout << "st_dest before " << std::endl;
	std::cout << std::endl;
	st_dest.insert(7);
	st_dest.insert(0);
	sit = st_dest.begin();
	for (; sit != st_dest.end(); sit++)
		std::cout << *sit << std::endl;

	std::cout << "st_dest after " << std::endl;
	std::cout << std::endl;

	st_dest.insert(st.begin(), st.end());
	sit = st_dest.begin();
	for (; sit != st_dest.end(); sit++)
		std::cout << *sit << std::endl;
}

void
test_erase()
{
	TESTED_NS::set<int> st;
	
	st.insert(4);
	st.insert(1);
	st.insert(1);
	TESTED_NS::set<int>::iterator sit;

	std::cout << "before erase" << std::endl;
	std::cout << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;
	
	st.erase(st.begin());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	std::cout << std::endl;
	std::cout << "----------range erase-----------" << std::endl;
	std::cout << std::endl;
	
	st.insert(sit, 5);
	st.insert(sit, 7);
	st.insert(sit, 65);

	std::cout << "before erase" << std::endl;
	std::cout << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	st.erase(st.find(5), st.find(7));

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;

	std::cout << std::endl;
	std::cout << "----------clear erase-----------" << std::endl;
	std::cout << std::endl;

	st.erase(st.find(4), st.end());

	std::cout << "after erase" << std::endl;
	std::cout << std::endl;
	sit = st.begin();
	for (; sit != st.end(); sit++)
		std::cout << *sit << std::endl;
}

void
test_clear()
{
	TESTED_NS::set<int> st;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	st.insert(1);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	st.erase(1);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
}

void
test_bounds_range(void)
{
	std::cout << "----------------bounds--------------------" << std::endl;

	TESTED_NS::set<char> myset;
	TESTED_NS::set<char>::iterator itlow,itup;

	myset.insert('a');
	myset.insert('b');
	myset.insert('c');
	myset.insert('d');
	myset.insert('e');

	itlow=myset.lower_bound('b');  // itlow points to b
	itup=myset.upper_bound('d');   // itup points to e (not d!)

	myset.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (TESTED_NS::set<char>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "----------------equal_range--------------" << std::endl;

	TESTED_NS::set<char> st2;

	st2.insert('a');
	st2.insert('b');
	st2.insert('c');

	TESTED_NS::pair<TESTED_NS::set<char>::iterator,TESTED_NS::set<char>::iterator> ret;
	ret = st2.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << *ret.first << std::endl;

	std::cout << "upper bound points to: ";
	std::cout << *ret.second << std::endl;
}

void
test_ctors_assign(void)
{
	TESTED_NS::set<char> st_src;
	
	st_src.insert('a');
	st_src.insert('b');
	st_src.insert('c');
	st_src.insert('d');

	for (TESTED_NS::set<char>::iterator it=st_src.begin();
			it!=st_src.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "copy of set : " << std::endl;

	TESTED_NS::set<char> st_dest(st_src);
	for (TESTED_NS::set<char>::iterator it=st_src.begin();
			it!=st_src.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "------------------range ctor----------------------" << std::endl;

	TESTED_NS::set<char> st_range(st_src.begin(), st_src.end());
	for (TESTED_NS::set<char>::iterator it=st_range.begin();
			it!=st_range.end(); ++it)
		std::cout << *it << std::endl;
	
	std::cout << "--------------------assign----------------------" << std::endl;
	
	TESTED_NS::set<char> st_src2;
	
	st_src2.insert('a');
	st_src2.insert('b');
	st_src2.insert('c');
	st_src2.insert('d');
	st_src2.insert('e');
	st_src2.insert('f');

	st_dest = st_src2;	

	for (TESTED_NS::set<char>::iterator it=st_src2.begin();
			it!=st_src2.end(); ++it)
		std::cout << *it << std::endl;
}

void
test_swap(void)
{
	TESTED_NS::set<char> st1;
	st1.insert('a');
	st1.insert('b');
	st1.insert('c');
	st1.insert('d');
	st1.insert('e');
	st1.insert('f');

	TESTED_NS::set<char> st2;
	st2.insert('a');
	st2.insert('b');
	st2.insert('c');
	st2.insert('d');
	st2.insert('e');
	st2.insert('f');
	
	std::cout << "------------before swap-------------" << std::endl;
	std::cout << std::endl;
	for (TESTED_NS::set<char>::iterator it=st1.begin();
			it!=st1.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << std::endl;

	for (TESTED_NS::set<char>::iterator it=st2.begin();
			it!=st2.end(); ++it)
		std::cout << *it << std::endl;

	st1.swap(st2);

	std::cout << "------------after swap-------------" << std::endl;
	std::cout << std::endl;
	for (TESTED_NS::set<char>::iterator it=st1.begin();
			it!=st1.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << std::endl;

	for (TESTED_NS::set<char>::iterator it=st2.begin();
			it!=st2.end(); ++it)
		std::cout << *it << std::endl;
}

void
test_find(void)
{
	TESTED_NS::set<int> st;

	st.insert(1);
	st.insert(2);
	st.insert(3);
	st.insert(4);
	st.insert(5);
	st.insert(6);
	st.insert(7);
	st.insert(8);
	
	std::cout << *(st.find(6)) << std::endl;
	std::cout << (st.end() == st.find(0)) << std::endl;
	std::cout << (st.end() == st.find(10)) << std::endl;
}

void
test_reverseit(void)
{
	TESTED_NS::set<char> st;

	st.insert('a');
	st.insert('b');
	st.insert('c');

	TESTED_NS::set<char>::reverse_iterator rit;
	for (rit=st.rbegin(); rit!=st.rend(); ++rit)
		std::cout << *rit << std::endl;
}

void
test_count(void)
{
	int count = 10;
	TESTED_NS::set<char> st;
	char c = 'a';

	for (int i = 0; i < count; i++)
		st.insert(c + i);

	for (c='a'; c<'z'; c++)
	{
		std::cout << c;
		if (st.count(c) > 0)
			std::cout << " is an element of st.\n";
		else 
			std::cout << " is not an element of st.\n";
	}
}

void
test_empty(void)
{
	TESTED_NS::set<int> st;
	int count = 10;

	std::cout << "st is empty : " << st.empty() << std::endl;

	for (int i = 0; i < count; i++)
		st.insert(100 + i);
	
	std::cout << "st is empty : " << st.empty() << std::endl;

	st.clear();

	std::cout << "st is empty : " << st.empty() << std::endl;
}

void
test_getallocator(void)
{
	TESTED_NS::set<char> st;
	char* p;

	p=st.get_allocator().allocate(5);
	st.get_allocator().deallocate(p,5);
}

void
test_keycost(void)
{
	int count = 10;
	TESTED_NS::set<int> st;
	for (int i = 0; i < count; i++)
		st.insert(i);
	for (TESTED_NS::set<int>::iterator it = st.begin();
			st.key_comp()(*it, count / 2);
			it++)
		std::cout << *it << std::endl;
}

void
test_valuecost(void)
{
	TESTED_NS::set<char> st;

	st.insert('a');
	st.insert('b');
	st.insert('c');

	std::cout << st.value_comp()(*st.begin(), *(++st.begin())) << std::endl;
}

void
test_relational(void)
{
	int count = 10;
	TESTED_NS::set<char> st;
	TESTED_NS::set<char> st2;

	for (int i = 0; i < count; i++)
	{
		st.insert('a' + i);
		st2.insert('a' + i * 2);
	}
	std::cout << (st < st2) << std::endl;
	std::cout << (st <= st2) << std::endl;
	std::cout << (st > st2) << std::endl;
	std::cout << (st >= st2) << std::endl;
	std::cout << (st == st2) << std::endl;
	std::cout << (st != st2) << std::endl;
}

void
test_nonmemberswap()
{
	TESTED_NS::set<char> foo,bar;

	foo.insert('x');
	foo.insert('y');

	bar.insert('a');
	bar.insert('b');
	bar.insert('c');

	swap(foo,bar);

	std::cout << "foo contains:\n";
	for (TESTED_NS::set<char>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "bar contains:\n";
	for (TESTED_NS::set<char>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << *it << std::endl;
}

void
test_performance(void)
{
	count = 1000;
	struct timeval before;

	TESTED_NS::set<int> st;

	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		st.insert(i * 5);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		st.erase(i * 5);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::set<int> st2;
	gettimeofday(&before, NULL);
	count *= 10;
	for (int i = 0; i < count; i++)
		st2.insert(i * 10);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		st2.erase(i * 10);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::set<int> st3;
	gettimeofday(&before, NULL);
	count *= 10;
	for (int i = 0; i < count; i++)
		st3.insert(i * 3);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		st3.erase(i * 3);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;
}
}

namespace stack_test
{
void
test_ctors(void)
{
	TESTED_NS::stack<int> st;
}

void
test_empty(void)
{
	TESTED_NS::stack<int> st;
	std::cout << st.empty() << std::endl;
	
	st.push(4);
	std::cout << st.empty() << std::endl;
	
	st.pop();
	std::cout << st.empty() << std::endl;
}

void
test_pushpop(void)
{
	TESTED_NS::stack<int> st;
	
	for (int i = 0; i < count; i++)
		st.push(i * 5);
	for (int i = 0; i < count; i++)
	{
		std::cout << st.top() << std::endl;
		st.pop();
	}
}

void
test_relational(void)
{
	TESTED_NS::stack<int> st;
	TESTED_NS::stack<int> st2;

	for (int i = 0; i < count; i++)
	{
		st.push(i * 5);
		st2.push(i * 3);
	}

	std::cout << (st < st2) << std::endl;
	std::cout << (st <= st2) << std::endl;
	std::cout << (st > st2) << std::endl;
	std::cout << (st >= st2) << std::endl;
	std::cout << (st == st2) << std::endl;
	std::cout << (st != st2) << std::endl;
}
}

namespace vector_test
{

void
test_performance(void)
{
	std::cout << "--------------------multiple insertion/deletion--------------------" << std::endl;
	count = 10;
	struct timeval before;

	TESTED_NS::vector<int> vec;
	std::cout << "capacity : " << vec.capacity() << std::endl;

	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		vec.insert(vec.begin(), i);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	std::cout << "capacity : " << vec.capacity() << std::endl;
	for (int i = 0; i < count; i++)
		vec.erase(vec.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::vector<int> vec2;

	count *= 10;
	std::cout << "capacity : " << vec2.capacity() << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		vec2.insert(vec2.begin(), i);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	std::cout << "capacity : " << vec2.capacity() << std::endl;
	for (int i = 0; i < count; i++)
		vec2.erase(vec2.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::vector<int> vec3;

	std::cout << "capacity : " << vec3.capacity() << std::endl;
	count *= 10;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		vec3.insert(vec3.begin(), i);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	std::cout << "capacity : " << vec3.capacity() << std::endl;
	for (int i = 0; i < count; i++)
		vec3.erase(vec3.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	TESTED_NS::vector<int> vec4;

	std::cout << "capacity : " << vec4.capacity() << std::endl;
	gettimeofday(&before, NULL);
	for (int i = 0; i < count; i++)
		vec4.insert(vec4.begin(), i);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;
	gettimeofday(&before, NULL);
	std::cout << "capacity : " << vec4.capacity() << std::endl;
	for (int i = 0; i < count; i++)
		vec4.erase(vec4.end() - 1);
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;
}

void
test_performance2(void)
{
	std::cout << "--------------------single insertion/deletion--------------------" << std::endl;
	/*
	**here are benchmarks of inserting / deleting one element
	**on different vector size
	*/
	count = 10;
	struct timeval before;

	TESTED_NS::vector<int> vec;
	std::cout << "capacity : " << vec.capacity() << std::endl;

	for (int i = 0; i < count; i++)
		vec.insert(vec.begin(), i);

	gettimeofday(&before, NULL);
	vec.insert(vec.begin(), 777);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;

	gettimeofday(&before, NULL);
	vec.erase(vec.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	std::cout << "capacity : " << vec.capacity() << std::endl;

	TESTED_NS::vector<int> vec2;

	count *= 10;
	std::cout << "capacity : " << vec2.capacity() << std::endl;
	for (int i = 0; i < count; i++)
		vec2.insert(vec2.begin(), i);

	gettimeofday(&before, NULL);
	vec2.insert(vec2.begin(), 777);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;

	gettimeofday(&before, NULL);
	vec2.erase(vec2.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	std::cout << "capacity : " << vec2.capacity() << std::endl;

	TESTED_NS::vector<int> vec3;

	std::cout << "capacity : " << vec3.capacity() << std::endl;
	count *= 10;
	for (int i = 0; i < count; i++)
		vec3.insert(vec3.begin(), i);

	gettimeofday(&before, NULL);
	vec3.insert(vec3.begin(), 777);
	std::cout << "insert time : " << get_relative_us(before) << " us" << std::endl;

	gettimeofday(&before, NULL);
	vec3.erase(vec3.begin());
	std::cout << "erase time : " << get_relative_us(before) << " us" << std::endl;

	std::cout << "capacity : " << vec2.capacity() << std::endl;
}


void
test_ctors(void)
{
	std::cout << "---------------- ctors ------------------" << std::endl;
	TESTED_NS::vector<int> v_empty;
	printVec(v_empty);

	TESTED_NS::vector<int> v_fill(10, 10);
	printVec(v_fill);

	TESTED_NS::vector<int> v_range(v_fill.begin(), v_fill.end());
	printVec(v_range);

	TESTED_NS::vector<int> v_copy(v_fill);
	printVec(v_copy);
}

void
test_assign(void)
{
	std::cout << "---------------- assign ------------------" << std::endl;
	TESTED_NS::vector<int> v_fill(10, 10);
	printVec(v_fill);
	
	TESTED_NS::vector<int> v(20, 5);
	printVec(v);
	
	v.assign(v_fill.begin(), v_fill.end());
	printVec(v);
}

void
test_at(void)
{
	std::cout << "---------------- at ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
	{
		try
		{
			vec[i] = i * 10;
		}
		catch (std::out_of_range &e)
		{
			std::cout << e.what() << std::endl;	
		}
	}
	printVec(vec);
	
	std::cout << vec.at(3) << std::endl;
}

void
test_back(void)
{
	std::cout << "---------------- back ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;

	printVec(vec);

	std::cout << vec.back() << std::endl;
}

void
test_beginend(void)
{
	std::cout << "---------------- begin/end ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;

	printVec(vec);

	std::cout << *vec.begin() << std::endl;
	std::cout << (vec.begin() != vec.end()) << std::endl;
}

void
test_rbeginend(void)
{
	std::cout << "---------------- rbegin/rend ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;

	printVec(vec);
	for (TESTED_NS::vector<int>::reverse_iterator rit = vec.rbegin();
			rit != vec.rend(); rit++)
		std::cout << *rit << std::endl;
}

void
test_clear(void)
{
	std::cout << "---------------- clear ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;

	printVec(vec);
	vec.clear();
	printVec(vec);
}

void
test_empty(void)
{
	std::cout << "---------------- empty ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	
	std::cout << "empty : " << vec.empty() << std::endl;
	
	vec.assign(4, 3);
	printVec(vec);

	std::cout << "empty : " << vec.empty() << std::endl;

	vec.clear();
	printVec(vec);

	std::cout << "empty : " << vec.empty() << std::endl;
}

void
test_erase(void)
{
	std::cout << "---------------- erase ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;
	
	printVec(vec);

	vec.erase(vec.begin());
	printVec(vec);

	vec.erase(vec.begin() + 2, vec.end() - 1);
	printVec(vec);
}

void
test_front(void)
{
	std::cout << "---------------- front ------------------" << std::endl;
	TESTED_NS::vector<int> vec(20, 5);
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;
	
	printVec(vec);
	std::cout << vec.front() << std::endl;

	TESTED_NS::vector<int> empty;
	printVec(vec);
	std::cout << vec.front() << std::endl;
}

void
test_getallocator(void)
{
	std::cout << "---------------- get_allocator ------------------" << std::endl;
	int size = 5;
	int *ptr = NULL;
	TESTED_NS::vector<int> vec;
	ptr = vec.get_allocator().allocate(size);
	for (int i = 0; i < size; i++)
		vec.get_allocator().construct(&ptr[i], i * 100);

	for (int i = 0; i < size; i++)
		std::cout << ptr[i] << std::endl;

	for (int i = 0; i < size; i++)
		vec.get_allocator().destroy(&ptr[i]);

	vec.get_allocator().deallocate(ptr, size);
}

void
test_insert(void)
{
	std::cout << "---------------- insert ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	for (int i = 0; i < count; i++)
		vec.insert(vec.begin(), i * 100);
	printVec(vec);

	TESTED_NS::vector<int> vfill;
	vfill.insert(vfill.begin(), count, 100);
	printVec(vfill);

	TESTED_NS::vector<int> vrange;
	vrange.insert(vrange.begin(), vfill.begin(), vfill.end());
	printVec(vrange);
}

void
test_opeequal(void)
{
	std::cout << "---------------- operator= ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	for (int i = 0; i < count; i++)
		vec.insert(vec.begin(), i * 100);
	printVec(vec);

	TESTED_NS::vector<int> vec2;
	for (int i = 0; i < count; i++)
		vec2.insert(vec2.begin(), i * 200);
	printVec(vec2);

	vec2 = vec;
	printVec(vec);
	printVec(vec2);
}

void
test_popback(void)
{
	std::cout << "---------------- pop_back ------------------" << std::endl;
	TESTED_NS::vector<int> vec(15, 3);
	printVec(vec);
	vec.pop_back();
	printVec(vec);
}

void
test_pushback(void)
{
	std::cout << "---------------- push_back ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	vec.push_back(3);
	printVec(vec);
	vec.push_back(6);
	printVec(vec);
	vec.push_back(9);
	printVec(vec);
	vec.push_back(12);
	printVec(vec);
	vec.push_back(15);
	printVec(vec);
}

void
test_reserve(void)
{
	std::cout << "---------------- reserve ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	std::cout << "properties before reserve" << std::endl;
	std::cout << "size :" << vec.size() << std::endl;
	std::cout << "capacity :" << vec.capacity() << std::endl;
	vec.reserve(20);
	std::cout << "properties after first reserve" << std::endl;
	std::cout << "size :" << vec.size() << std::endl;
	std::cout << "capacity :" << vec.capacity() << std::endl;
	vec.push_back(4);
	vec.push_back(8);
	vec.push_back(12);
	vec.reserve(50);
	std::cout << "properties after second reserve and few pushbacks" << std::endl;
	std::cout << "size :" << vec.size() << std::endl;
	std::cout << "capacity :" << vec.capacity() << std::endl;
}

void
test_resize(void)
{
	std::cout << "---------------- resize ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	vec.resize(4, 30);
	printVec(vec);
	std::cout << "capacity :" << vec.capacity() << std::endl;
	vec.resize(10, 25);
	printVec(vec);
	std::cout << "capacity :" << vec.capacity() << std::endl;
	vec.resize(1, 9);
	printVec(vec);
	std::cout << "capacity :" << vec.capacity() << std::endl;
}

void
test_swap(void)
{
	std::cout << "---------------- swap ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	vec.resize(4, 30);
	printVec(vec);

	TESTED_NS::vector<int> vec2;
	vec.resize(20, 56);
	printVec(vec2);

	vec.swap(vec2);

	printVec(vec);
	printVec(vec2);
}

void
test_relational(void)
{
	std::cout << "---------------- relational ope ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	vec.resize(4, 30);
	printVec(vec);

	TESTED_NS::vector<int> vec2;
	vec.resize(20, 56);
	printVec(vec2);

	std::cout << (vec < vec2) << std::endl;
	std::cout << (vec <= vec2) << std::endl;
	std::cout << (vec > vec2) << std::endl;
	std::cout << (vec >= vec2) << std::endl;
	std::cout << (vec == vec2) << std::endl;
	std::cout << (vec != vec2) << std::endl;
}

void
test_nonmemberswap(void)
{
	std::cout << "---------------- non member swap ------------------" << std::endl;
	TESTED_NS::vector<int> vec;
	vec.resize(4, 30);
	printVec(vec);

	TESTED_NS::vector<int> vec2;
	vec.resize(20, 56);
	printVec(vec2);

	swap(vec, vec2);

	printVec(vec);
	printVec(vec2);
}
}

int main()
{
#ifdef FT 
	std::cout << "Namespace tested : ft" << std::endl;
#else
	std::cout << "Namespace tested : std" << std::endl;
#endif
	std::cout << "###################################" << std::endl;
	std::cout << "##             vector            ##" << std::endl;
	std::cout << "###################################" << std::endl;
	
	{
	using namespace vector_test;
	/*
	test_ctors();
	test_assign();
	test_at();
	test_back();
	test_beginend();
	test_rbeginend();
	test_clear();
	test_empty();
	test_erase();
	test_front();
	test_getallocator();
	test_insert();
	test_opeequal();
	test_popback();
	test_pushback();
	test_reserve();
	test_resize();
	test_swap();
	test_relational();
	test_nonmemberswap();
	test_performance();
	*/
	test_performance2();
	}
	return 0;

	std::cout << "###################################" << std::endl;
	std::cout << "##             stack             ##" << std::endl;
	std::cout << "###################################" << std::endl;
	
	{
	using namespace stack_test;
	std::cout << "---------------- ctors ------------------" << std::endl;
	test_ctors();
	std::cout << "---------------- empty ------------------" << std::endl;
	test_empty();
	std::cout << "---------------- push/pop ------------------" << std::endl;
	test_pushpop();
	std::cout << "---------------- relational ------------------" << std::endl;
	test_relational();
	}

	std::cout << "###################################" << std::endl;
	std::cout << "##              map              ##" << std::endl;
	std::cout << "###################################" << std::endl;
	
	{
	using namespace map_test;
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
	//test_performance();
	//
	//
	}

	std::cout << "###################################" << std::endl;
	std::cout << "##              set              ##" << std::endl;
	std::cout << "###################################" << std::endl;
	
	{
	using namespace set_test;
	std::cout << "---------------- insert ------------------" << std::endl;
	test_insert();
	std::cout << "---------------- erase ------------------" << std::endl;
	test_erase();
	std::cout << "---------------- clear ------------------" << std::endl;
	test_clear();
	std::cout << "---------------- lower/upper/equal range ------------------" << std::endl;
	test_bounds_range();
	std::cout << "---------------- ctors/assign ------------------" << std::endl;
	test_ctors_assign();
	std::cout << "---------------- swap ------------------" << std::endl;
	test_swap();
	std::cout << "---------------- find ------------------" << std::endl;
	test_find();
	std::cout << "---------------- reverse it ------------------" << std::endl;
	test_reverseit();
	std::cout << "---------------- count ------------------" << std::endl;
	test_count();
	std::cout << "---------------- empty ------------------" << std::endl;
	test_empty();
	std::cout << "---------------- keycost ------------------" << std::endl;
	test_keycost();
	std::cout << "---------------- valuecost ------------------" << std::endl;
	test_valuecost();
	std::cout << "---------------- relational ------------------" << std::endl;
	test_relational();
	std::cout << "---------------- non member swap ------------------" << std::endl;
	test_nonmemberswap();
	//test_performance();
	}

	return 0;
}
