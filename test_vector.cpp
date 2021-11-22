#include "vector.hpp"
#include <vector>
#include <iostream>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

int count = 20;

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
	TESTED_NS::vector<int> vec;
	for (int i = 0; i < count; i++)
		vec[i] = i * 10;

	printVec(vec);

	std::cout << vec.back() << std::endl;
}

void
test_beginend(void);
void
test_rbeginend(void);
void
test_clear(void);
void
test_empty(void);
void
test_erase(void);
void
test_front(void);
void
test_getallocator(void);
void
test_insert(void);
void
test_opeequal(void);
void
test_opebracket(void);
void
test_popback(void);
void
test_pushback(void);
void
test_reserve(void);
void
test_resize(void);
void
test_swap(void);
void
test_relational(void);
void
test_nonmemberswap(void);
int main()
{
	test_ctors();
	test_assign();
	test_at();
	//test_back();
	//test_beginend();
	//test_rbeginend();
	//test_clear();
	//test_empty();
	//test_erase();
	//test_front();
	//test_getallocator();
	//test_insert();
	//test_opeequal();
	//test_opebracket();
	//test_popback();
	//test_pushback();
	//test_reserve();
	//test_resize();
	//test_swap();
	//test_relational();
	//test_nonmemberswap();
	return 0;
}
