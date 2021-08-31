#include <memory>
#include <iostream>
#include "vect_iterator.hpp"
#include "type_traits.hpp"
#include <iterator_traits.hpp>

#define CHAR_TYPEID "c"
#define MAX_SIZE 9223372036854775807

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
			: _size(0), _capacity(0), _elems(NULL), _alloc(Alloc())
			{
				if (strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = MAX_SIZE / sizeof(T) * 2;
				_max_size = MAX_SIZE / sizeof(T);
			}

			vector(const Alloc& alloc)
			: _size(0), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = MAX_SIZE / sizeof(T) * 2;
				_max_size = MAX_SIZE / sizeof(T);
			}

			vector(size_type count, const T& value = T(), const Alloc& alloc = Alloc())
			: _size(count), _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = MAX_SIZE / sizeof(T) * 2;
				_max_size = MAX_SIZE / sizeof(T);

				if (_size == 0)
					return ;
				_capacity = computeCapacity(_size);
				try
				{
					_elems = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_elems[i] = T(value);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}
				_capacity = _size;
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const Alloc& alloc = Alloc())
			: _capacity(0), _elems(NULL), _alloc(alloc)
			{
				if (strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = MAX_SIZE / sizeof(T) * 2;
				_max_size = MAX_SIZE / sizeof(T);

				this->_size = computeSize(first, last);
				if (this->_size == 0)
					return ;
				try
				{
					this->_elems = this->_alloc.allocate(_size);
					InputIterator it = first;
					size_type i = 0;
					for (; it < last; it++)
					{
						_elems[i] = value_type(*it);
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
			: _size(other.size()), _capacity(other.capacity()), _elems(NULL),
				_alloc(other._alloc)
			{
				if (strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = MAX_SIZE / sizeof(T) * 2;
				_max_size = MAX_SIZE / sizeof(T);

				if (!this->_size)
					return ;
				try
				{
					this->_elems = static_cast<T*>(this->_alloc.allocate(_size));
					for (size_type i = 0; i < this->_size; i++)
						this->_elems[i] = value_type(other._elems[i]);
				}
				catch (std::exception e)
				{
					std::cout << e.what() << std::endl;	
					return ;
				}	
			}

			vector &
			operator= (const vector& x)
			{
				if (this->_capacity != 0)
					this->destroy_elems();
				this->_size = x._size;
				this->_capacity = x._capacity;
				if (this->_capacity != 0)
				{
					try
					{
						this->_elems = this->_alloc.allocate(this->_capacity);
						for (size_type i = 0; i < this->_size; i++)
							this->_elems[i] = value_type(x._elems[i]);
					}
					catch (std::bad_alloc &e)
					{
						std::cout << e.what() << std::endl;
					}
				}
				return *this;
			}

			virtual ~vector()
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_elems[i].~T();
				if (_capacity != 0)
					this->_alloc.deallocate(this->_elems, this->_capacity);
			}

			size_type size() const 
				{return _size;}

			size_type max_size() const
				{
					return _max_size;
				}

			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
				{
					this->realloc_elems();
					for (size_type i = _size; i < n; i++)
						_elems[i] = value_type(val);
				}
				_size = n;
			}

			size_type capacity() const
				{return this->_capacity;}

			bool empty() const
				{return (this->_size > 0);}

			void reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				this->realloc_elems();
				_capacity = n;
			}

			template <class InputIterator>
			void
			assign (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type tmp_size = computeSize(first, last);
				if (_capacity != 0)
					_alloc.deallocate(_elems, _capacity);
				if (tmp_size > _capacity)
				try
				{
					_elems = _alloc.allocate(tmp_size);
					int i = 0;
					for (InputIterator it = first; it != last; it++)
						_elems[i++] = value_type(*it);
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				_size = tmp_size;
				_capacity = tmp_size;
			}

			void
			assign (size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				this->destroy_elems(_capacity);
				try
				{
					if (n > _capacity)
						_elems = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						_elems[i] = value_type(val);
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				_size = n;
				_capacity = n;
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
				_elems[_size] = value_type(val);
				_size++;
			}

			void
			pop_back()
			{
				_size--;
			}

			/*
			* if current capacity is not sufficient
			* realloc reimplementation to avoid unnecessary memory moves
			*
			*/
			iterator
			insert (iterator position, const value_type& val)
			{
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
							new_elems[i] = _elems[i];	
							i++;
							it++;
						}
						new_elems[i++] = val;
						while (i < _size + 1)
						{
							new_elems[i] = _elems[i - 1];
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
						_elems[i] = _elems[i - 1];
						i--;
						it--;
					}
					_elems[i] = val;
				}
				_size++;
				return position;
			}

			void
			insert (iterator position, size_type n, const value_type& val)
			{
				size_type new_size = _size + n;
				if (new_size > _capacity)
					try
					{
						size_type new_capacity = computeCapacity(new_size);
						pointer new_elems = _alloc.allocate(new_capacity);
						iterator it = this->begin();
						size_type i = 0;
						while (it != position)
						{
							new_elems[i] = _elems[i];
							i++;
							it++;
						}
						size_type j;
						for (j = 0; j < n; j++)
							new_elems[i + j] = val;
						while (i + j < new_size)
						{
							new_elems[i + j] = _elems[i];
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
				else
				{
					iterator it = this->begin() + new_size - 1;
					size_type i = new_size;
					while (it != position)
					{
						_elems[i] = _elems[i - n];
						i--;
						it--;
					}
					std::cout << "i :" << i << std::endl;
					std::cout << "elems[i] : " << _elems[i] << std::endl;
					for (size_type j = 0; j < n; j++)
						_elems[i - j] = val;
				}
				_size = new_size;
			}

			template <class InputIterator>
			void
			insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type n = computeSize(first, last);
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
							new_elems[i] = value_type(_elems[i]);
							i++;
							it++;
						}
						size_type j = 0;
						InputIterator in_it = first;
						while (in_it != last)
						{
							new_elems[i + j] = value_type(*in_it);
							in_it++;
							j++;
						}
						while (i + j < new_size)
						{
							new_elems[i + j] = value_type(_elems[i]);
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
					size_type insert_idx = 0;
					while (it != position)
					{
						insert_idx++;
						it++;
					}
					size_type j = new_size;
					while (j >= insert_idx)
					{
						_elems[j] = _elems[j - n];
						j--;
					}
					InputIterator in_it = first;
					j = 0;
					while (in_it != last)
					{
						_elems[insert_idx + j] = *in_it;
						in_it++;
						j++;
					}
				}
				_size = new_size;
			}

			iterator erase (iterator position)
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
				_elems[i].~value_type();
				while (it != this->end() - 1)
				{
					_elems[i] = _elems[i + 1];
					i++;
					it++;
				}
				_size--;
				return position;
			}

			iterator erase (iterator first, iterator last)
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
					_elems[i + j].~value_type();
					j++;
					it++;
				}
				while (it != this->end())
				{
					_elems[i] = _elems[i + j];
					i++;
					it++;
				}
				_size -= j;
				return first;
			}
			
			void
			swap (vector<value_type>& x)
			{
				vector<value_type> tmp = x;
				x = *this;
				*this = tmp;
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
				size_type capacity;

				if (size > 8)
					return size;
				capacity = 1;
				while (capacity < size)
					capacity *= 2;
				return capacity;
			}

			void
			realloc_elems(void)
			{
				size_type new_capacity = _capacity * 2;
				try
				{
					pointer new_elems = _alloc.allocate(new_capacity);	
					for (size_type i = 0; i < _size; i++)
						new_elems[i] = value_type(_elems[i]);
					if (_capacity != 0)
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
				for (size_type i = 0; i < _capacity; i++)
					_elems[i].~T();
				_alloc.deallocate(_elems, _capacity);
			}

			reference
			front()
			{
				return _elems[0];
			}

			reference
			back()
			{
				return _elems[_size - 1];
			}
	};
}
