/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:24:16 by darbib            #+#    #+#             */
/*   Updated: 2021/08/17 18:04:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <iterator_traits.hpp>

namespace ft
{
	template <class T>
	class vect_iterator
	: public ft::iterator_traits<T*>
	{
		public :
			typedef T								value_type;
			typedef T&								reference;
			typedef const T&						const_reference;
			typedef T*								pointer;
			typedef const T*						const_pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::random_access_iterator_tag	iterator_category;

#if __IT_LIFE_DEBUG__ == 1
			vect_iterator()
			: _current_ptr(NULL)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			vect_iterator(vect_iterator const &src)
			: _current_ptr(src._current_ptr)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			vect_iterator(pointer ptr)
			: _current_ptr(ptr)
			//{ }
			{ std::cout << "an iterator is created" << std::endl;}

			virtual ~vect_iterator()
			//{ }
			{ std::cout << "an iterator is destroyed" << std::endl;}

#else
			vect_iterator()
			: _current_ptr(NULL)
			{ }

			vect_iterator(vect_iterator const &src)
			: _current_ptr(src._current_ptr)
			{ }

			vect_iterator(pointer ptr)
			: _current_ptr(ptr)
			{ }

			virtual ~vect_iterator()
			{ }
#endif

			vect_iterator &
			operator=(vect_iterator const &src)
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

			reference
			operator[](unsigned int offset)
			{
				return *(_current_ptr + offset);
			}

			difference_type	
			operator-(vect_iterator &other) const
			{
				
				return static_cast<difference_type>(this->_current_ptr - other._current_ptr);
			}

			bool
			operator<(const vect_iterator &other) const
			{ return this->_current_ptr < other._current_ptr; }

			bool
			operator>(const vect_iterator &other) const
			{ return this->_current_ptr > other._current_ptr; }

			bool
			operator>=(const vect_iterator &other) const
			{ return this->_current_ptr >= other._current_ptr; }

			bool
			operator<=(const vect_iterator &other) const
			{ return this->_current_ptr <= other._current_ptr; }

			bool
			operator==(const vect_iterator &other) const
			{ return this->_current_ptr == other._current_ptr; }

			bool
			operator!=(const vect_iterator &other) const
			{ return !(*this == other); }

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

			vect_iterator
			operator+(int n) const
			{
				vect_iterator vi;
				vi._current_ptr = this->_current_ptr + n;
				return vi;
			}

			vect_iterator
			operator-(int n) const
			{ 
				vect_iterator vi;
				vi._current_ptr = this->_current_ptr - n;
				return vi;
			}

			vect_iterator &
			operator+=(int n)
			{
				this->_current_ptr += n;
				return *this;
			}

			vect_iterator &
			operator-=(int n)
			{
				this->_current_ptr -= n;
				return *this;
			}

			vect_iterator &
			operator--(void)
			{
			{ std::cout << "prefix dec" << std::endl;}
				this->_current_ptr -= 1;
				return *this;
			}

			vect_iterator
			operator--(int)
			{
			{ std::cout << "postfix dec" << std::endl;}
				vect_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr -= 1;
				return tmp;
			}

			vect_iterator &
			operator++(void)
			{
			{ std::cout << "prefix inc" << std::endl;}
				this->_current_ptr += 1;
				return *this;
			}

			vect_iterator
			operator++(int)
			{
			{ std::cout << "postfix inc" << std::endl;}
				vect_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr += 1;
				return tmp;
			}

		protected :
			pointer		_current_ptr;
	};

	template <class T>
	vect_iterator<T>
	operator+(int n, vect_iterator<T> &other)
	{	
		vect_iterator<T> vi;
		vi.setCurrentPtr(other.getCurrentPtr() + n);
		return vi;
	}
}
