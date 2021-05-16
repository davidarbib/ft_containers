#include <vector>
#include <iostream>
#include "vect_iterator.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	int tb[] = { 4, 7, -2, 13 };

	ft::vect_iterator<int> it(tb);
	std::cout << *it << std::endl;
	std::cout << *(it + 2) << std::endl;
	std::cout << *(2 + it) << std::endl;
	ft::vect_iterator<int> it2 = it + 1 + 1;
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

	ft::vect_iterator<int>it3;
	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;
	it3 = it2--; //it2 = tb
	std::cout << *it3 << std::endl;

	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;

	ft::vect_iterator<int> itchain1(tb);
	ft::vect_iterator<int> itchain2;
	ft::vect_iterator<int> itchain3;
	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;
	itchain3 = ++itchain2 = ++itchain1;
	//itchain3 = itchain2++ = itchain1++;
	//itchain2 = ++itchain1;
	//itchain2 = itchain1++;
	std::cout << "*itchain1 : " << *itchain1 << std::endl;
	std::cout << "*itchain2 : " << *itchain2 << std::endl;
	std::cout << "*itchain3 : " << *itchain3 << std::endl;

	std::cout << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << std::endl;

	std::vector<int> vec;
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(-2);
	vec.push_back(13);
	std::vector<int>::iterator itvec1 = vec.begin();
	std::vector<int>::iterator itvec2;
	std::vector<int>::iterator itvec3;
	itvec3 = ++itvec2 = ++itvec1;
	//itvec3 = itvec2++ = itvec1++;
	std::cout << "*itvec1 : " << *itvec1 << std::endl;
	std::cout << "*itvec2 : " << *itvec2 << std::endl;
	std::cout << "*itvec3 : " << *itvec3 << std::endl;
	return 0;
}
