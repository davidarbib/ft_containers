#include "set.hpp"
#include <set>
#include <iostream>
#include <sys/time.h>

//#define TESTED_NS ft

#ifndef TESTED_NS
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
	std::cout << "---------------- estty ------------------" << std::endl;
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
	//while (1) {};
	return 0;
}
