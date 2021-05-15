#include <vector>
#include <iostream>
#include "vect_iterator.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	int tb[] = { 4, 7, -2, 13 };

	ft::Vect_Iterator<int> it(tb);
	std::cout << *it << std::endl;
	std::cout << *(it + 2) << std::endl;
	std::cout << *(2 + it) << std::endl;
	ft::Vect_Iterator<int> it2 = it + 1 + 1;
	std::cout << *it2 << std::endl;
	std::cout << it2 - it << std::endl;
	//ft::Random_Access_Iterator<int> itnull;
	//std::cout << it << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << tb[2] << std::endl;
	*it2 = -42;
	std::cout << tb[2] << std::endl;
	it2 += 1; //it2 = tb + 3
	std::cout << tb[3] << std::endl;
	*it2 = 56; 
	std::cout << tb[3] << std::endl;

	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << *it2-- << std::endl; //it2 = tb + 2
	std::cout << *it2 << std::endl;
	std::cout << *--it2 << std::endl; //it2 = tb + 1

	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;

	ft::Vect_Iterator<int>it3;
	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;
	it3 = it2--; //it2 = tb
	std::cout << *it3 << std::endl;
	return 0;

}
