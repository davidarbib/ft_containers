#ifndef VECT_ITERATOR_HPP
# define VECT_ITERATOR_HPP

#include <cstddef>
#include <iterator_traits.hpp>
#include <type_traits.hpp>

namespace ft
{
	template <class T, bool isconst = false>
	class vect_iterator
	{
		public :
			typedef T														value_type;
			typedef typename ft::conditionnal<isconst, const T&, T&>::type	reference;
			typedef typename ft::conditionnal<isconst, const T*, T*>::type	pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::random_access_iterator_tag	iterator_category;

			vect_iterator()
			: _current_ptr(NULL)
			{ }

			vect_iterator(vect_iterator const &src)
			: _current_ptr(src._current_ptr)
			{ }

			template <bool B>
			vect_iterator(const vect_iterator<T, B> &src,
					typename ft::enable_if<!B>::type* = 0)
			: _current_ptr(src.getCurrentPtr())
			{ }

			vect_iterator(pointer ptr)
			: _current_ptr(ptr)
			{ }

			virtual ~vect_iterator()
			{ }

			vect_iterator &
			operator=(vect_iterator const &src)
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

			reference
			operator[](int offset)
			{
				return *(_current_ptr + offset);
			}

			const reference
			operator[](int offset) const
			{
				return *(_current_ptr + offset);
			}



			pointer
			getCurrentPtr(void) const
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
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix dec" << std::endl;}
#endif
				this->_current_ptr -= 1;
				return *this;
			}

			vect_iterator
			operator--(int)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "postfix dec" << std::endl;}
#endif
				vect_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr -= 1;
				return tmp;
			}

			vect_iterator &
			operator++(void)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix inc" << std::endl;}
#endif
				this->_current_ptr += 1;
				return *this;
			}

			vect_iterator
			operator++(int)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "postfix inc" << std::endl;}
#endif
				vect_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr += 1;
				return tmp;
			}

		private :
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

	template <typename T, bool B, bool C>
	typename vect_iterator<T, B>::difference_type
	operator-(const vect_iterator<T, B> &lhs, const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() - rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator<(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() < rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator>(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() > rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator<=(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() <= rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator>=(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() >= rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator==(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() == rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator!=(const vect_iterator<T, B> &lhs,
			const vect_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() != rhs.getCurrentPtr(); }
}

#endif
