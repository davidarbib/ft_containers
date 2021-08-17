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

			vector(size_type count, const T& value = T(), const Alloc& alloc = Alloc())
			: _size(count), _max_size(MAX_SIZE), _capacity(0), _elems(NULL),
			_alloc(alloc)
			{
				if (this->_size == 0)
					return ;
				try
				{
					this->_elems = this->_alloc.allocate(_size);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}
				for (size_type i = 0; i < this->_size; i++)
					this->_elems[i] = value;
				_capacity = _size;
			}

			template<class InputIt>
			vector(InputIt first, InputIt last, const Alloc& alloc = Alloc())
			: _max_size(MAX_SIZE), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				this->_size = computeSize(first, last);
				if (this->_size == 0)
					return ;
				try
				{
					this->_elems = this->_alloc.allocate(_size);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
			//		need iterator implementation
				_capacity = _size;
			}

			vector(const vector& other)
			: _size(other.size()), _capacity(other.capacity()), _elems(NULL),
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
				for (size_type i = 0; i < this->_size; i++)
					this->_elems[i] = other._elems[i];
			}

			virtual ~vector()
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_elems[i].~T();
				this->_alloc.deallocate(this->_elems, this->_capacity);
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
				this->alloc.deallocate(_elems, _capacity);
				this->elems = tmp;
				this->_capacity = n;
			}

			template <class InputIterator>
			void
			assign (InputIterator first, InputIterator last)
			{
				size_type tmp_size = computeSize(first, last);
				if (_capacity != 0)
					_alloc.deallocate(_elems, _capacity);
				if (tmp_size > _capacity)
				try
				{
					_elems = _alloc.allocate(tmp_size);
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				_size = tmp_size;
				_capacity = tmp_size;
				int i = 0;
				for (InputIterator it = first; it != last; it++)
					_elems[i++] = *it;
			}

			void
			assign (size_type n, const value_type& val) //TODO enable if to avoid caller casting
			{
				if (n == 0)
					return ;
				_alloc.deallocate(_elems, _capacity);
				if (n > _capacity)
					_elems = _alloc.allocate(n);
				_size = n;
				_capacity = n;
				for (size_type i = 0; i < n; i++)
					_elems[i] = val;
			}

			void
			push_back (const value_type& val)
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
					this->realloc_elems();
				_elems[_size] = val;
				_size++;
			}

			void
			pop_back()
			{
				_size--;
			}

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);

			void
			swap (vector& x)
			{
				(void)x;
			}

			void
			clear()
			{
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

			iterator
			end(void)
			{
				iterator it(_elems + _size);
				return it;
			}

			allocator_type get_allocator() const;

		private:
			size_type 					_size;
			size_type 					_max_size;
			size_type 					_capacity;
			pointer						_elems;
			allocator_type				_alloc;

			template <class InputIterator>
			size_t
			computeSize(InputIterator first, InputIterator last)
			{
				size_type size = 1;
				for (InputIterator it = first; it != last; it++) 
					size++;
				return size;
			}

			void
			realloc_elems(void)
			{
				size_type new_capacity = _capacity * 2;
				try
				{
					pointer new_elems = _alloc.allocate(new_capacity);	
					for (size_type i = 0; i < _size; i++)
						new_elems[i] = _elems[i];
					_alloc.deallocate(_elems, _capacity);
					_elems = new_elems;
					_capacity = new_capacity;
				}
				catch(std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
	};
}
