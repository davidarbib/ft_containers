/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:40:13 by darbib            #+#    #+#             */
/*   Updated: 2021/08/14 23:19:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>

namespace ft
{
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
	class Random_Access_Iterator
	: public ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			Random_Access_Iterator()
			: _current_ptr(NULL)
			{ }

			Random_Access_Iterator(Random_Access_Iterator const &src)
			: _current_ptr(src._current_ptr)
			{ }

			Random_Access_Iterator(pointer ptr)
			: _current_ptr(ptr)
			{ }

			virtual ~Random_Access_Iterator()
			{ }
	
			Random_Access_Iterator
			&operator=(Random_Access_Iterator const &src)
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

			difference_type	
			operator-(Random_Access_Iterator &other) const
			{ return static_cast<difference_type>(this->_current_ptr - other._current_ptr); }

			bool
			operator<(Random_Access_Iterator &other) const
			{ return this->_current_ptr < other._current_ptr; }

			bool
			operator>(Random_Access_Iterator &other) const
			{ return this->_current_ptr > other._current_ptr; }

			bool
			operator>=(Random_Access_Iterator &other) const
			{ return this->_current_ptr >= other._current_ptr; }

			bool
			operator<=(Random_Access_Iterator &other) const
			{ return this->_current_ptr <= other._current_ptr; }

			bool
			operator==(Random_Access_Iterator &other) const
			{ return this->_current_ptr == other._current_ptr; }

			bool
			operator!=(Random_Access_Iterator &other) const
			{ return this->_current_ptr != other._current_ptr; }

			pointer
			getCurrentPtr(void)
			{
				return this->_current_ptr;
			}

			void
			setCurrentPtr(pointer ptr)
			{
				this->_current_ptr = ptr;
			}

		protected :
			pointer		_current_ptr;
	};
}
