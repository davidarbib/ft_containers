#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <cstring>
#include "vect_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "iterator_traits.hpp"

#define CHAR_TYPEID "c"
#define EMAXSIZE "can't reserve above max_size"
#define E_RANGE "Out of bound exception"

#if __APPLE__ == 1
	#define SIZE_CAP _capacity
#else
	#define SIZE_CAP _size
#endif

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
    		typedef typename ft::vect_iterator<T, false>	iterator;
    		typedef typename ft::vect_iterator<T, true>		const_iterator;
    		typedef ft::reverse_iterator<iterator>       	reverse_iterator;
    		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			vector()
			: _size(0), _capacity(0), _elems(NULL), _alloc(Alloc())
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();
			}

			vector(const Alloc& alloc)
			: _size(0), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();
			}

			vector(size_type count, const T& value = T(), const Alloc& alloc = Alloc())
			: _size(count), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();

				if (_size == 0)
					return ;
				_capacity = _size;
				try
				{
					_elems = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_elems + i, value);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last,
					const Alloc& alloc = Alloc(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			: _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();

				//this->_size = computeSize(first, last);
				this->_size = ft::distance(first, last);
				if (this->_size == 0)
					return ;
				_capacity = _size;
				try
				{
					this->_elems = this->_alloc.allocate(_capacity);
					InputIterator it = first;
					size_type i = 0;
					for (; it != last; it++)
					{
						_alloc.construct(_elems + i, *it);
						i++;
					}
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
				_capacity = _size;
			}

			vector(const vector& other)
			: _size(other._size), _capacity(other.SIZE_CAP), _elems(NULL),
				_alloc(other._alloc)
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();

				if (_size == 0)
					return ;
				//_capacity = _size;
				try
				{
					_elems = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_elems + i, other._elems[i]);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
			}

			vector &
			operator=(const vector& x)
			{ 
				size_type new_capacity;
				try
				{
					if (x._size > this->_capacity)
						new_capacity = x._size;
					else
						new_capacity = this->_capacity;
					pointer new_elems = _alloc.allocate(new_capacity);	
					for (size_type i = 0; i < x._size; i++)
						_alloc.construct(new_elems + i, x._elems[i]);
					for (size_type i = 0; i < this->_size; i++)
						_alloc.destroy(_elems + i);
					_alloc.deallocate(_elems, this->_capacity);
					_elems = new_elems;
					this->_capacity = new_capacity;
					this->_size = x._size;
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				return *this;
			}

			virtual ~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_elems + i);
				if (_capacity != 0)
					_alloc.deallocate(_elems, _capacity);
			}

			size_type
			size() const 
			{ return _size; }

			size_type
			max_size() const
			{ return _max_size; }

			void
			resize(size_type n, value_type val = value_type())
			{
				if (n > _capacity)
				{
					//std::cout << "reallocation" << std::endl;
					this->realloc_elems(computeCapacity(n));
				}
				if (n > _size)
				{
					//std::cout << "construction" << std::endl;
					for (size_type i = _size; i < n; i++)
						_alloc.construct(_elems + i, val);
				}
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_elems + i);
				}
				_size = n;
			}

			size_type
			capacity() const
			{ return this->_capacity; }

			bool
			empty() const
			{ return (this->_size == 0); }

			void
			reserve(size_type n)
			{
				if (n > _max_size)
				{
					try
					{
						throw std::length_error(EMAXSIZE);
					}
					catch(const std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
						return ;
					}
				}
				if (n <= _capacity)
					return ;
				//this->realloc_elems(_capacity * 2);
				this->realloc_elems(n);
				_capacity = n;
			}

			template <class InputIterator>
			void
			assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type tmp_size = computeSize(first, last);
				if (tmp_size > _capacity)
				{
					//size_type new_capacity = computeCapacity(tmp_size);
					size_type new_capacity = tmp_size; 
					this->destroy_elems();
					try
					{
						_elems = _alloc.allocate(new_capacity);
						size_type i = 0;
						for (InputIterator it = first; it != last; it++)
							_alloc.construct(_elems + i++, *it);
					}
					catch (std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
					_capacity = new_capacity;
				}
				else
				{	
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_elems + i);
					size_type i = 0;
					for (InputIterator it = first; it != last; it++)
						_alloc.construct(_elems + i++, *it);
				}
				_size = tmp_size;
			}

			void
			assign(size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n > _capacity)
				{
					//size_type new_capacity = computeCapacity(tmp_size);
					size_type new_capacity = n; 
					this->destroy_elems();
					try
					{
						_elems = _alloc.allocate(n);
						for (size_type i = 0; i < n; i++)
							_alloc.construct(_elems + i, val);
					}
					catch (std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
					_capacity = new_capacity;
				}
				else
				{	
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_elems + i);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_elems + i, val);
				}
				_size = n;
			}

			void
			push_back(const value_type& val)
			{
				try
				{
					if (_capacity == 0)
					{
						_elems = _alloc.allocate(1);	
						_capacity++;
					}
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
					return ;
				}
				if (_size == _capacity)
					this->realloc_elems(_capacity * 2);
				_alloc.construct(_elems + _size, val);
				_size++;
			}

			void
			pop_back()
			{
				_size--;
				_alloc.destroy(_elems + _size);
			}

			/*
			* if current capacity is not sufficient
			* realloc reimplementation to avoid unnecessary memory moves
			*
			*/
			iterator
			insert(iterator position, const value_type& val)
			{
				pointer insert_location = NULL;
				if (_size == _capacity)
				{
					try
					{
						size_type new_capacity = computeCapacity(_size + 1);
						pointer new_elems = _alloc.allocate(new_capacity);
						iterator it = this->begin();
						size_type i = 0;
						while (it != position)
						{
							_alloc.construct(new_elems + i, _elems[i]);
							i++;
							it++;
						}
						insert_location = new_elems + i;
						new_elems[i++] = val;
						while (i < _size + 1)
						{
							_alloc.construct(new_elems + i, _elems[i - 1]);
							i++;
						}
						this->destroy_elems();
						_elems = new_elems;
						_capacity = new_capacity;
					}
					catch(std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
				}
				else
				{
					iterator it = this->end();
					size_type i = _size;
					while (it != position)
					{
						_alloc.construct(_elems + i, _elems[i - 1]);
						_alloc.destroy(_elems + i - 1);
						i--;
						it--;
					}
					_alloc.construct(_elems + i, val);
					insert_location = _elems + i;
				}
				_size++;
				return iterator(insert_location);
			}

			void
			insert(iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				size_type new_size = _size + n;
				if (new_size > _capacity)
				{
					try
					{
						size_type new_capacity = computeCapacity(new_size);
						pointer new_elems = _alloc.allocate(new_capacity);
						iterator it = this->begin();
						size_type i = 0;
						while (it != position)
						{
							_alloc.construct(new_elems + i, _elems[i]);
							i++;
							it++;
						}
						size_type j;
						for (j = 0; j < n; j++)
							_alloc.construct(new_elems + i + j, val);
						while (i + j < new_size)
						{
							_alloc.construct(new_elems + i + j, _elems[i]);
							i++;
						}
						this->destroy_elems();
						_elems = new_elems;
						_capacity = new_capacity;
					}
					catch(std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
				}
				else
				{
					iterator it = this->begin();
					int i = 0;
					while (it != position)
					{
						it++;
						i++;
					}
					int insert_idx = i;
					i = _size - 1;
					while (i >= insert_idx)
					{
						_alloc.construct(_elems + i + n, _elems[i]);
						_alloc.destroy(_elems + i);
						i--;
					}
					for (int j = 0; j < static_cast<int>(n); j++)
						_alloc.construct(_elems + insert_idx + j, val);
				}
				_size = new_size;
			}

			template <class InputIterator>
			void
			insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type n = computeSize(first, last);
				if (n == 0)
					return ;
				size_type new_size = _size + n;
				if (new_size > _capacity)
				{
					try
					{
						size_type new_capacity = computeCapacity(new_size);
						pointer new_elems = _alloc.allocate(new_capacity);
						iterator it = this->begin();
						size_type i = 0;
						while (it != position)
						{
							_alloc.construct(new_elems + i, _elems[i]);
							i++;
							it++;
						}
						size_type j = 0;
						InputIterator in_it = first;
						while (in_it != last)
						{
							_alloc.construct(new_elems + i + j, *in_it);
							in_it++;
							j++;
						}
						while (i + j < new_size)
						{
							_alloc.construct(new_elems + i + j, _elems[i]);
							i++;
						}
						this->destroy_elems();
						_elems = new_elems;
						_capacity = new_capacity;
					}
					catch(std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
				}
				else
				{
					iterator it = this->begin();
					int i = 0;
					while (it != position)
					{
						it++;
						i++;
					}
					int insert_idx = i;
					i = _size - 1;
					while (i >= insert_idx)
					{
						_alloc.construct(_elems + i + n, _elems[i]);
						_alloc.destroy(_elems + i);
						i--;
					}
					InputIterator in_it = first;
					int j = 0;
					while (in_it != last)
					{
						_alloc.construct(_elems + insert_idx + j, *in_it);
						in_it++;
						j++;
					}
				}
				_size = new_size;
			}

			iterator erase(iterator position)
			{
				if (position == this->end())
					return position;
				iterator it = this->begin();
				size_type i = 0;
				while (it != position)
				{	
					i++;
					it++;
				}
				_alloc.destroy(_elems + i);
				while (it != this->end() - 1)
				{
					_alloc.construct(_elems + i, _elems[i + 1]);
					_alloc.destroy(_elems + i + 1);
					i++;
					it++;
				}
				_size--;
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == last)
					return first;
				iterator it = this->begin();
				size_type i = 0;
				while (it != first)
				{	
					i++;
					it++;
				}
				size_type j = 0;
				while (it != last)
				{
					_alloc.destroy(_elems + i + j);
					j++;
					it++;
				}
				while (it != this->end())
				{
					_alloc.construct(_elems + i, _elems[i + j]);
					_alloc.destroy(_elems + i + j);
					i++;
					it++;
				}
				_size -= j;
				return first;
			}
			
			void
			swap(vector<value_type>& x)
			{
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_capacity, x._capacity);
				std::swap(this->_elems, x._elems);
				std::swap(this->_size, x._size);
			}

			void
			clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_elems + i);
				_size = 0;
			}

			reference
			operator[](unsigned int offset)
			{
				return static_cast<reference>(*(_elems + offset));
			}

			iterator
			begin(void)
			{
				iterator it(_elems);
				return it;
			}

			const_iterator
			begin(void) const
			{
				const_iterator it(_elems);
				return it;
			}

			iterator
			end(void)
			{
				iterator it(_elems + _size);
				return it;
			}

			const_iterator
			end(void) const
			{
				const_iterator it(_elems + _size);
				return it;
			}

			reverse_iterator
			rbegin(void)
			{
				reverse_iterator it(_elems + _size);
				return it;
			}

			const_reverse_iterator
			rbegin(void) const
			{
				const_reverse_iterator it(_elems + _size);
				return it;
			}

			reverse_iterator
			rend(void)
			{
				reverse_iterator it(_elems);
				return it;
			}

			const_reverse_iterator
			rend(void) const
			{
				const_reverse_iterator it(_elems);
				return it;
			}

			pointer
			data(void)
			{ return _elems; }

			reference
			at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range(E_RANGE);
				return _elems[pos];
			}

			const_reference
			at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range(E_RANGE);
				return _elems[pos];
			}

			reference
			front()
			{ return _elems[0]; }

			const_reference
			front() const
			{ return _elems[0]; }

			reference
			back()
			{ return _elems[_size - 1]; }

			const_reference
			back() const
			{ return _elems[_size - 1]; }

			allocator_type
			get_allocator(void) const
			{ return _alloc; }

		private:
			size_type 					_size;
			size_type 					_max_size;
			size_type 					_capacity;
			pointer						_elems;
			allocator_type				_alloc;

			template <class InputIterator>
			size_type
			computeSize(InputIterator first, InputIterator last)
			{
				size_type size = 0;
				for (InputIterator it = first; it != last; it++) 
					size++;
				return size;
			}

			size_type
			computeCapacity(size_type size)
			{	
				if (size > SIZE_CAP * 2)
					return size;
				if (SIZE_CAP > 0)
					return SIZE_CAP * 2;
				return 1;
			}

			void
			realloc_elems(size_type new_capacity)
			{
				try
				{
					pointer new_elems = _alloc.allocate(new_capacity);	
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(new_elems + i, _elems[i]);
					this->destroy_elems();
					_elems = new_elems;
					_capacity = new_capacity;
				}
				catch(std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			void
			destroy_elems(void)
			{
				if (_capacity == 0)
					return ;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_elems + i);
				_alloc.deallocate(_elems, _capacity);
			}
	};

	template< class T, class Alloc >
	void
	swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{ lhs.swap(rhs); }

	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ||
				ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) &&
				ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ||
				ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) &&
				!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
}

#endif
