#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{

	template <typename Iter>
	class reverse_iterator
	{
		public :
			typedef Iter													iterator_type;
			typedef typename iterator_traits<Iter>::value_type				value_type;
			typedef typename iterator_traits<Iter>::difference_type			difference_type;
			typedef typename iterator_traits<Iter>::pointer					pointer;
			typedef typename iterator_traits<Iter>::reference				reference;
			typedef typename iterator_traits<Iter>::iterator_category		iterator_category;

			reverse_iterator()
			: _base_it(iterator_type())
			{ }

			reverse_iterator(iterator_type x)
			: _base_it(x)
			{ }

			template <class U>
			reverse_iterator(const reverse_iterator<U>& u)
			: _base_it(u.base())
			{ }

			iterator_type
			base(void) const
			{ return _base_it; }

			reference
			operator*(void)
			{
				iterator_type tmp = _base_it;
				return *--tmp;
			}

			pointer
			operator->(void)
			{
				iterator_type tmp = _base_it;
				--tmp;
				return tmp.getCurrentPtr();
			}
			
			reverse_iterator&
			operator++(void)
			{
				_base_it--;
				return *this;
			}

			reverse_iterator
			operator++(int)
			{
				reverse_iterator tmp = *this;
				_base_it--;
				return tmp;
			}

			reverse_iterator&
			operator--()
			{
				_base_it++;
				return *this;
			}

			reverse_iterator
			operator--(int)
			{
				reverse_iterator tmp = *this;
				_base_it++;
				return tmp;
			}

			reverse_iterator
			operator+(difference_type n) const
			{ return reverse_iterator(_base_it - n); }

			reverse_iterator&
			operator+=(difference_type n)
			{
				_base_it -= n;
				return *this;
			}

			reverse_iterator
			operator-(difference_type n) const
			{ return reverse_iterator(_base_it + n); }

			reverse_iterator&
			operator-=(difference_type n)
			{
				_base_it += n;
				return *this;
			}

			reference
			operator[](difference_type n) const
			{ return _base_it[-n - 1]; }

		protected :
			iterator_type	_base_it;
	};

	template <typename Iter, typename Iter2>
	bool
	operator==( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
	{ return x.base() == y.base(); }

	template <class Iter, typename Iter2>
	bool
	operator<( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
		{ return x.base() > y.base(); }

	template <typename Iter, typename Iter2>
	bool
	operator!=( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
	{ return x.base() != y.base(); }

	template <typename Iter, typename Iter2>
	bool
	operator>( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
	{ return x.base() < y.base(); }

	template <typename Iter, typename Iter2>
	bool operator>=( const reverse_iterator<Iter>& x,
					const reverse_iterator<Iter2>& y)
	{ return x.base() <= y.base(); }

	template <typename Iter, typename Iter2>
	bool operator<=( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
	{ return x.base() >= y.base(); }

	template <typename Iter, typename Iter2>
	typename reverse_iterator<Iter>::difference_type
	operator-( const reverse_iterator<Iter>& x,
				const reverse_iterator<Iter2>& y)
	{ return y.base() - x.base(); }

	template <typename Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
				const reverse_iterator<Iter>& x)
	{ return reverse_iterator<Iter>(x.base() - n); }
}

#endif
