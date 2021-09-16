#include "pair.hpp"
#include <string>
#include <iostream>

#ifndef NS
# define NS ft
#endif

int main()
{
	NS::pair<int, std::string> pr1(42, "coucou");
	NS::pair<int, std::string> pr2 = pr1;

	std::cout << "pr1 first : " << pr1.first << std::endl;
	std::cout << "pr1 second : " << pr1.second << std::endl;
	std::cout << "pr2 first : " << pr2.first << std::endl;
	std::cout << "pr2 second : " << pr2.second << std::endl;

	NS::pair<int, int> pr3 = NS::make_pair(7, 14);
	std::cout << "pr3 first : " << pr3.first << std::endl;
	std::cout << "pr3 second : " << pr3.second << std::endl;

	NS::pair<int, int> small_pr = NS::make_pair(3, 4);
	NS::pair<int, int> big_pr = NS::make_pair(12, 3);
	std::cout << (small_pr == big_pr) << std::endl;
	std::cout << (small_pr != big_pr) << std::endl;
	std::cout << (small_pr >= big_pr) << std::endl;
	std::cout << (small_pr <= big_pr) << std::endl;
	std::cout << (small_pr > big_pr) << std::endl;
	std::cout << (small_pr < big_pr) << std::endl;

	small_pr = NS::make_pair(3, 4);
	big_pr = NS::make_pair(12, 3);	
	std::cout << (small_pr == big_pr) << std::endl;
	std::cout << (small_pr != big_pr) << std::endl;
	std::cout << (small_pr >= big_pr) << std::endl;
	std::cout << (small_pr <= big_pr) << std::endl;
	std::cout << (small_pr > big_pr) << std::endl;
	std::cout << (small_pr < big_pr) << std::endl;

	small_pr = NS::make_pair(3, 4);
	big_pr = NS::make_pair(0, 11);	
	std::cout << (small_pr == big_pr) << std::endl;
	std::cout << (small_pr != big_pr) << std::endl;
	std::cout << (small_pr >= big_pr) << std::endl;
	std::cout << (small_pr <= big_pr) << std::endl;
	std::cout << (small_pr > big_pr) << std::endl;
	std::cout << (small_pr < big_pr) << std::endl;

	small_pr = NS::make_pair(0, 11);
	big_pr = NS::make_pair(0, 11);	
	std::cout << (small_pr == big_pr) << std::endl;
	std::cout << (small_pr != big_pr) << std::endl;
	std::cout << (small_pr >= big_pr) << std::endl;
	std::cout << (small_pr <= big_pr) << std::endl;
	std::cout << (small_pr > big_pr) << std::endl;
	std::cout << (small_pr < big_pr) << std::endl;
	
	return 0;
}
