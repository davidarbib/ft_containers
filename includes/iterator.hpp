#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "iterator_traits.hpp"

/*
** iterator tag dispatching used to compute distance with 
** iterator specific complexity
*/

namespace ft
{
	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type
	do_distance(InputIt first, InputIt last, ft::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIt>::difference_type distance = 0;
		for (InputIt it = first; it != last; it++) 
			distance++;
		return distance;
	}

	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type
	do_distance(InputIt first, InputIt last, ft::random_access_iterator_tag)
	{
		return last - first;
	}

	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type
	distance(InputIt first, InputIt last)
	{
		return ft::do_distance(first, last,
				typename ft::iterator_traits<InputIt>::iterator_category());	
	}
}

#endif 
