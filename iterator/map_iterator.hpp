#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <cstddef>
#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <class T, bool isconst = false>
	class map_iterator
	{
		public :
			typedef T												value_type;
			typedef typename
				ft::conditional<isconst, const T&, T&>::type	reference;
			typedef typename
				ft::conditional<isconst, const T*, T*>::type	pointer;
			typedef std::ptrdiff_t									difference_type;
			typedef ft::bidirectionnal_iterator_tag					iterator_category;

			map_iterator()
			: _current_ptr(NULL)
			{ }

			map_iterator(map_iterator const &src)
			: _current_ptr(src._current_ptr)
			{ }

			template <bool B>
			map_iterator(const map_iterator<T, B> &src,
					typename ft::enable_if<!B>::type* = 0)
			: _current_ptr(src.getCurrentPtr())
			{ }

			map_iterator(pointer ptr)
			: _current_ptr(ptr)
			{ }

			virtual ~map_iterator()
			{ }

			map_iterator &
			operator=(map_iterator const &src)
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

			map_iterator &
			operator--(void)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix dec" << std::endl;}
#endif
				this->_current_ptr -= 1;
				return *this;
			}

			map_iterator
			operator--(int)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "postfix dec" << std::endl;}
#endif
				map_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr -= 1;
				return tmp;
			}

			map_iterator &
			operator++(void)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix inc" << std::endl;}
#endif
				this->_current_ptr += 1;
				return *this;
			}

			map_iterator
			operator++(int)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "postfix inc" << std::endl;}
#endif
				map_iterator tmp;
				tmp._current_ptr = this->_current_ptr;
				this->_current_ptr += 1;
				return tmp;
			}

		private :
			pointer		_current_ptr;
			
			pointer
			next_node(pointer start_node)
			{
				if (start_node->right_child)
					return leftmost(start_node->right_child);	
				pointer previous = start_node;
				pointer head = start_node->parent;
				while (previous == head->right_child)
				{
					if (previous == head)
						return head;
					previous = head;
					head = head->parent;
				}
				return leftmost(head->right_child);
			}

			pointer
			previous_node(pointer start_node)
			{
				if (start_node->right_child)
					return leftmost(start_node->right_child);	
				pointer previous = start_node;
				pointer head = start_node->parent;
				while (previous == head->right_child)
					head = head->parent;
			}

			pointer
			leftmost(pointer start_node)
			{
				pointer head = start_node;
				while (head->left_child)
					head = head->left_child;
				return head;
			}

			pointer
			rightmost(pointer start_node)
			{
				pointer head = start_node;
				while (head->right_child)
					head = head->right_child;
				return head;
			}
	};

	template<typename T, bool B, bool C>
	bool
	operator==(const map_iterator<T, B> &lhs,
			const map_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() == rhs.getCurrentPtr(); }

	template<typename T, bool B, bool C>
	bool
	operator!=(const map_iterator<T, B> &lhs,
			const map_iterator<T, C> &rhs)
	{ return lhs.getCurrentPtr() != rhs.getCurrentPtr(); }
}

#endif
