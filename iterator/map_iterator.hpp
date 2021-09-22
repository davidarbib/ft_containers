#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rbnode.hpp"

namespace ft
{
	template <class T, bool isconst = false>
	class map_iterator
	{
		private:
			typedef ft::rbnode<T>								node_type;
			typedef node_type*									node_pointer;

		public :
			typedef T											value_type;
			typedef typename
				ft::conditional<isconst, const T&, T&>::type	reference;
			typedef typename
				ft::conditional<isconst, const T*, T*>::type	pointer;
			typedef std::ptrdiff_t								difference_type;
			typedef ft::bidirectionnal_iterator_tag				iterator_category;

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

			map_iterator(node_pointer ptr)
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
			{ return static_cast<reference>(_current_ptr->pair); }

			node_pointer
			operator->(void) const
			{ return _current_ptr; }

			node_pointer
			getCurrentPtr(void) const
			{ return _current_ptr; }

			void
			setCurrentPtr(node_pointer ptr)
			{ _current_ptr = ptr; }

			map_iterator &
			operator--(void)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix dec" << std::endl;}
#endif
				_current_ptr = previous_node(_current_ptr);
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
				_current_ptr = previous_node(_current_ptr);
				return tmp;
			}

			map_iterator &
			operator++(void)
			{
#if __IT_LIFE_DEBUG__ == 1
			{ std::cout << "prefix inc" << std::endl;}
#endif
				_current_ptr = next_node(_current_ptr);
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
				_current_ptr = next_node(_current_ptr);
				return tmp;
			}

		private :
			node_pointer		_current_ptr;
			
			node_pointer
			next_node(node_pointer start_node)
			{
				if (start_node->right_child)
					return leftmost(start_node->right_child);
				node_pointer previous = start_node;
				node_pointer head = start_node->parent;
				while (previous == head->right_child)
				{
					if (previous == head)
						return head;
					previous = head;
					head = head->parent;
				}
				return head;
			}

			node_pointer
			previous_node(node_pointer start_node)
			{
				if (start_node->left_child)
					return rightmost(start_node->left_child);	
				node_pointer previous = start_node;
				node_pointer head = start_node->parent;
				while (previous == head->left_child)
				{
					if (previous == head)
						return head;
					previous = head;
					head = head->parent;
				}
				return head;
			}

			node_pointer
			leftmost(node_pointer start_node)
			{
				node_pointer head = start_node;
				while (head->left_child)
					head = head->left_child;
				return head;
			}

			node_pointer
			rightmost(node_pointer start_node)
			{
				node_pointer head = start_node;
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
