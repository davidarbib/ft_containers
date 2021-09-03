#include <iostream>
#include "vector.hpp"
#include <vector>
#include "algorithm.hpp"
#include <algorithm>

int main()
{
	typedef ft::vector<int>::iterator VectIt;

	ft::vector<int> v1;
	ft::vector<int> v2;
	
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);

	std::cout << "less than : ";
	std::cout << ft::lexicographical_compare<VectIt, VectIt>(v1.begin(), v1.end(),
															v2.begin(), v2.end());
	std::cout << std::endl;

	return 0;
}
