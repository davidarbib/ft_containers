#ifndef PRINT_PAIR_HPP
# define PRINT_PAIR_HPP

#include "pair.hpp"
#include <iostream>

namespace ft
{
	template <typename T, typename U>
	std::ostream& operator<<(std::ostream& os, const ft::pair<T, U>& pair)
	{
		os << pair.first << ", " << pair.second;
		return os;
	}
}

#endif
