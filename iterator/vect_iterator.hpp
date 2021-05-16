/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:24:16 by darbib            #+#    #+#             */
/*   Updated: 2021/05/16 15:35:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include "iterator.hpp"

namespace ft
{
	template <class T>
	class Vect_Iterator
	: public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			Vect_Iterator()
			: _current_ptr(NULL)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			Vect_Iterator(Vect_Iterator const &src)
			: _current_ptr(src._current_ptr)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			Vect_Iterator(pointer ptr)
			: _current_ptr(ptr)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			virtual ~Vect_Iterator()
			//{ }
			{ std::cout << "an iterator is destroyed" << std::endl;}

			Vect_Iterator &
			operator=(Vect_Iterator const &src)
			{
			{ std::cout << "iterator assignment" << std::endl;}
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
			operator-(Vect_Iterator &other) const
			{ return static_cast<difference_type>(this->_current_ptr - other._current_ptr); }

			bool
			operator<(Vect_Iterator &other) const
			{ return this->_current_ptr < other._current_ptr; }

			bool
			operator>(Vect_Iterator &other) const
			{ return this->_current_ptr > other._current_ptr; }

			bool
			operator>=(Vect_Iterator &other) const
			{ return this->_current_ptr >= other._current_ptr; }

			bool
			operator<=(Vect_Iterator &other) const
			{ return this->_current_ptr <= other._current_ptr; }

			bool
			operator==(Vect_Iterator &other) const
			{ return this->_current_ptr == other._current_ptr; }

			bool
			operator!=(Vect_Iterator &other) const
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

			value_type
			operator[](int n)
			{
				return *(this + n);
			}

			Vect_Iterator
			operator+(int n) const
			{
				Vect_Iterator vi;
				vi._current_ptr = this->_current_ptr + n;
				return vi;
			}

			Vect_Iterator
			operator-(int n) const
			{ 
				Vect_Iterator vi;
				vi._current_ptr = this->_current_ptr - n;
				return vi;
			}

			Vect_Iterator &
			operator+=(int n)
			{
				this->_current_ptr += n;
				return *this;
			}

			Vect_Iterator &
			operator-=(int n)
			{
				this->_current_ptr -= n;
				return *this;
			}

			Vect_Iterator &
			operator--(void)
			{
			{ std::cout << "prefix dec" << std::endl;}
				this->_current_ptr -= 1;
				return *this;
			}

			Vect_Iterator
			operator--(int)
			{
			{ std::cout << "postfix dec" << std::endl;}
				Vect_Iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr -= 1;
				return tmp;
			}

			Vect_Iterator &
			operator++(void)
			{
			{ std::cout << "prefix inc" << std::endl;}
				this->_current_ptr += 1;
				return *this;
			}

			Vect_Iterator
			operator++(int)
			{
			{ std::cout << "postfix inc" << std::endl;}
				Vect_Iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr += 1;
				return tmp;
			}

		protected :
			pointer		_current_ptr;
	};

	template <class T>
	Vect_Iterator<T>
	operator+(int n, Vect_Iterator<T> &other)
	{	
		Vect_Iterator<T> vi;
		vi.setCurrentPtr(other.getCurrentPtr() + n);
		return vi;
	}
}
