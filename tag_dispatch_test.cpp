#include <iostream>
#include <list>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	//std::list<int> l;
	//
	//l.push_back(1);
	//l.push_back(2);
	//l.push_back(3);
	//l.push_back(4);

	//std::cout << ft::distance(l.begin(), l.end()) << std::endl;

	ft::vector<int> v;
	
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	std::cout << ft::distance(v.begin(), v.end()) << std::endl;

	return 0;
}
