#include <vector>
#include <iostream>
#include "iterator.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	int tb[] = { 4, 7, -2, 13 };

	ft::Random_Access_Iterator<int> it(tb);
	std::cout << *it << std::endl;
	std::cout << *(it + 2) << std::endl;
	ft::Random_Access_Iterator<int> it2 = it + 1 + 1;
	std::cout << *it2 << std::endl;
	std::cout << it2 - it << std::endl;
	//ft::Random_Access_Iterator<int> itnull;
	//std::cout << it << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << tb[2] << std::endl;
	*it2 = -42;
	std::cout << tb[2] << std::endl;
	std::vector<int> vec;
	std::vector<int>::iterator itstd;
	std::cout << *itstd << std::endl;
	return 0;

}
