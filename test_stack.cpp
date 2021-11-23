#include "stack.hpp"
#include <stack>
#include <iostream>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

int count = 5;

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

int main()
{
#ifdef FT 
	std::cout << "Namespace tested : ft" << std::endl;
#else
	std::cout << "Namespace tested : std" << std::endl;
#endif
	std::cout << "---------------- ctors ------------------" << std::endl;
	test_ctors();
	std::cout << "---------------- empty ------------------" << std::endl;
	test_empty();
	std::cout << "---------------- push/pop ------------------" << std::endl;
	test_pushpop();
	std::cout << "---------------- relational ------------------" << std::endl;
	test_relational();
	return 0;
}
