#include "vector.hpp"
#include <vector>
#include <iostream>
#include <sys/time.h>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

int count = 20;
#define TIME_FACTOR 1000

long	get_usec_from_epoch()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / TIME_FACTOR + tv.tv_sec * TIME_FACTOR);
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

int main()
{
#ifdef FT 
	std::cout << "Namespace tested : ft" << std::endl;
#else
	std::cout << "Namespace tested : std" << std::endl;
#endif
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
	return 0;
}
