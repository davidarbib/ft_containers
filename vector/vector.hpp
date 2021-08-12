/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:48:08 by darbib            #+#    #+#             */
/*   Updated: 2021/08/12 19:50:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include "vect_iterator.hpp"

#define MAX_SIZE	2305843009213693951

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector 
	{
		public:
			typedef	T										value_type;
    		typedef Alloc                               	allocator_type;
    		typedef typename Alloc::reference               reference;
    		typedef const typename Alloc::const_reference   const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
    		typedef std::size_t								size_type;
    		typedef std::ptrdiff_t							difference_type;
    		typedef typename ft::vect_iterator<T>			iterator;
    		typedef typename ft::vect_iterator<T const>		const_iterator;
    		//typedef std::reverse_iterator<iterator>       reverse_iterator;
    		//typedef std::reverse_iterator<const_itar      const_reverse_iterator;

			vector()
			: _size(0), _max_size(MAX_SIZE), _capacity(0), _elems(NULL), 
			_alloc(Alloc())
			{}

			vector(const Alloc& alloc)
			: _size(0), _max_size(MAX_SIZE), _capacity(0), _elems(NULL), 
			_alloc(alloc)
			{}

			vector(std::size_t count, const T& value = T(),
                 	const Alloc& alloc = Alloc())
			: _size(count), _max_size(MAX_SIZE), _capacity(0), _elems(NULL),
			_alloc(alloc)
			{
				if (this->_size == 0)
					return ;
				try
				{
					this->_elems = static_cast<T*>(this->_alloc.allocate(_size));
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
				for (int i = 0; i < this->_size; i++)
					this->_elems[i] = value;
			}

			vector(std::size_t count)
			: _size(count), _max_size(MAX_SIZE), _capacity(0), _elems(NULL),
				_alloc(Alloc())
			{
				try
				{
					this->_elems = static_cast<T*>(this->_alloc.allocate(_size));
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
				}	
			}

			template<class InputIt>
			vector(InputIt first, InputIt last,
						const Alloc& alloc = Alloc())
			: _max_size(MAX_SIZE), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				this->_size = computeSize(first, last);
				if (this->_size == 0)
					return ;
				try
				{
					this->_elems = static_cast<T*>(this->_alloc.allocate(_size));
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
			//		need iterator implementation
			}

			vector(const vector& other)
			: _size(other.size), _capacity(other.capacity), _elems(NULL),
				_max_size(MAX_SIZE), _alloc(other.alloc)
			{
				if (!this->_size)
					return ;
				try
				{
					this->_elems = static_cast<T*>(this->_alloc.allocate(_size));
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
				for (int i = 0; i < this->_size; i++)
					this->_elems[i] = other._elems[i];
			}

			virtual ~vector()
			{
				for (int i = 0; i < this->_size; i++)
					this->elems[i].~T();
				this->alloc.deallocate(this->_elems, this->_capacity);
			}

			size_type size() const 
				{return this->_size;}

			size_type max_size() const
				{return this->_size;}

			/* needs push_back etc....
			void resize (size_type n, value_type val = value_type())
			{
				T *tmp = static_cast<T*>(this->alloc.allocate
			}
			*/

			size_type capacity() const
				{return this->_capacity;}

			bool empty() const
				{return (this->_size > 0);}

			void reserve(size_type n)
			{
				if (n <= this->_capacity)
					return ;
				T *tmp = NULL;
				try
				{
					tmp = static_cast<T*>(this->_alloc.allocate(n));
				}
				catch(std::exception e)
				{
					std::cout << e.what() << std::endl;
					return ;
				}
				for (int i = 0; i < this->_size; i++)
					this->elems[i].~T();
				this->alloc.deallocate(this->_elems, this->_capacity);
				this->elems = tmp;
				this->_capacity = n;
			}

			template <class InputIterator>
			void
			assign (InputIterator first, InputIterator last)
			{
				size_t tmp_size = computeSize(first, last);
				if (tmp_size == 0)
					return ;
				this->_alloc.deallocate(this->_size);
				this->_alloc.allocate(tmp_size);
				this->_size = tmp_size;
				this->_capacity = tmp_size;
				int i = 0;
				for (InputIterator it = first; it != last; it++)
					this[i++] = *it;
			}

			void
			assign (size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				this->_alloc.deallocate(this->_size);
				this->_alloc.allocate(n);
				this->_size = n;
				this->_capacity = n;
				for (size_type i = 0; i < n; i++)
					this[i] = val;
			}

			void push_back (const value_type& val);
			void pop_back();
			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear();

			allocator_type get_allocator() const;

			template <class InputIterator>
			size_t
			computeSize(InputIterator first, InputIterator last)
			{
				if (first == NULL || last == NULL)
					return 0;
				size_t	size = 1;
				for (InputIterator it = first; it != last; it++) 
					size++;
				return size;
			}

		private:
			size_type 		_size;
			size_type 		_max_size;
			size_type 		_capacity;
			T				*_elems;
			const Alloc		&_alloc;
	};
}
