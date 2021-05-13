/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:40:13 by darbib            #+#    #+#             */
/*   Updated: 2021/05/13 18:19:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};	
	struct output_iterator_tag {};	
	struct forward_iterator_tag : input_iterator_tag, output_iterator_tag {};
	struct bidirectionnal_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectionnal_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, 
			 class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	class AARandom_Access_Iterator
	: public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			ARandom_Access_Iterator()
			: _current_ptr(NULL)
			{ }

			ARandom_Access_Iterator(ARandom_Access_Iterator const &src)
			: _current_ptr(src._current_ptr)
			{ }

			ARandom_Access_Iterator(pointer ptr)
			: _current_ptr(ptr)
			{ }

			virtual ~ARandom_Access_Iterator()
			{ }
	
			ARandom_Access_Iterator
			&operator=(ARandom_Access_Iterator const &src)
			{
				this->_current_ptr = src._current_ptr;
				return *this;
			}

			reference
			operator*(void)
			{ return static_cast<reference>(*this->_current_ptr); }

			pointer
			operator->(void) const
			{ return this->_current_ptr; }

			ARandom_Access_Iterator
			operator+(int n) const 
			{
				ARandom_Access_Iterator	rai;
				rai._current_ptr = this->_current_ptr + n;  
				return rai;
			}

			friend ARandom_Access_Iterator
			operator+(int n, ARandom_Access_Iterator &other);

			ARandom_Access_Iterator
			operator+(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr + other._current_ptr; }

			difference_type	
			operator-(ARandom_Access_Iterator &other) const
			{ return static_cast<difference_type>(this->_current_ptr - other._current_ptr); }

			ARandom_Access_Iterator
			virtual operator-(int n) const = 0;

			ARandom_Access_Iterator
			virtual operator+=(int n) = 0;

			ARandom_Access_Iterator
			virtual operator-=(int n) const = 0;

			bool
			operator<(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr < other._current_ptr; }

			bool
			operator>(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr > other._current_ptr; }

			bool
			operator>=(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr >= other._current_ptr; }

			bool
			operator<=(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr <= other._current_ptr; }

			bool
			operator==(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr == other._current_ptr; }

			bool
			operator!=(ARandom_Access_Iterator &other) const
			{ return this->_current_ptr != other._current_ptr; }

		protected :
			pointer		_current_ptr;
	};

	template <class T>
	ARandom_Access_Iterator<T>
	operator+(int n, ARandom_Access_Iterator<T> &other)
	{
		ARandom_Access_Iterator<T>	rai;
		rai._current_ptr = n + other._current_ptr;  
		return rai;
	}
}
