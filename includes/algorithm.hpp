#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

#include "iterator.hpp"

namespace ft
{
	template <class InputIt1, class InputIt2>
	bool
	lexicographical_compare(InputIt1 first1, InputIt1 last1,
							InputIt2 first2, InputIt2 last2)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size1;
		typename ft::iterator_traits<InputIt2>::difference_type size2;
		
		size1 = ft::distance(first1, last1);
		size2 = ft::distance(first2, last2);

		if (size1 == 0 && size2 != 0)
			return true;
		if (size2 == 0)
			return false;
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	
	template <class InputIt1, class InputIt2, class Compare>
	bool
	lexicographical_compare(InputIt1 first1, InputIt1 last1,
							InputIt2 first2, InputIt2 last2, Compare comp)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size1;
		typename ft::iterator_traits<InputIt2>::difference_type size2;
		
		size1 = ft::distance(first1, last1);
		size2 = ft::distance(first2, last2);

		if (size1 == 0 && size2 != 0)
			return true;
		if (size2 == 0)
			return false;
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIt1, class InputIt2>
	bool
	equal(InputIt1 first1, InputIt1 last1,
           InputIt2 first2)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size;
		
		size = ft::distance(first1, last1);
		InputIt2 last2 = first2 + size;

		if (size == 0)
			return true;
		for (; (first1 != last1); ++first1, ++first2)
		{
			if (*first1 < *first2) return false;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 == last2);
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool
	equal(InputIt1 first1, InputIt1 last1,
            InputIt2 first2, BinaryPredicate p)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size;
		
		size = ft::distance(first1, last1);
		InputIt2 last2 = first2 + size;

		if (size == 0)
			return true;
		for (; (first1 != last1); ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return (first1 == last1) && (first2 == last2);
	}

	template <class InputIt1, class InputIt2>
	bool
	equal(InputIt1 first1, InputIt1 last1,
           InputIt2 first2, InputIt2 last2)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size1;
		typename ft::iterator_traits<InputIt2>::difference_type size2;
		
		size1 = ft::distance(first1, last1);
		size2 = ft::distance(first2, last2);

		if (size1 == 0 && size2 == 0)
			return true;
		if (size1 == 0)
			return false;
		if (size2 == 0)
			return false;
		for (; (first1 != last1 && first2 != last2); ++first1, ++first2)
			if (*first1 != *first2) return false;
		return (first1 == last1) && (first2 == last2);
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool
	equal(InputIt1 first1, InputIt1 last1,
            InputIt2 first2, InputIt2 last2, BinaryPredicate p)
	{
		typename ft::iterator_traits<InputIt1>::difference_type size1;
		typename ft::iterator_traits<InputIt1>::difference_type size2;
		
		size1 = ft::distance(first1, last1);
		size2 = ft::distance(first2, last2);

		if (size1 == 0 && size2 == 0)
			return true;
		if (size1 == 0)
			return false;
		if (size2 == 0)
			return false;

		for (; (first1 != last1 && first2 != last2); ++first1, ++first2)
			if (!p(*first1, *first2)) return false;
		return true;
	}

	/*
	template <typename T>
	void
	swap(T& a, T& b)
	{
		T tmp = T(a);
		a = b;
		b = tmp;
	}
	*/
}

#endif
