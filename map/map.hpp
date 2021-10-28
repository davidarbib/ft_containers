#ifndef MAP_HPP
# define MAP_HPP

#ifndef TEST_TREE
# define TEST_TREE 0
#endif

#define CHAR_TYPEID "c"

#include <typeinfo>
#include <functional>
#include <string.h>
#include "rbtree_map.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
    		typedef std::size_t								size_type;
    		typedef std::ptrdiff_t							difference_type;
			typedef ft::rbtree_iterator<value_type, false>	iterator;
			typedef ft::rbtree_iterator<value_type, true>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			class value_compare
			: public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:
					bool
					operator()(const value_type& x, const value_type& y) const
					{ return comp(x.first, y.first); }
			};

			typedef ft::rbTreeMap<key_type, mapped_type, 
					value_compare, key_compare,
					allocator_type>							tree_type; 

			map(const Compare& comp = Compare(),
					const Allocator& = Allocator())
			: _tree(tree_type(value_compare(comp))),
				_comp(comp)
			{ }

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& = Allocator())
			: _tree(tree_type(value_compare(comp))),
				_comp(comp)
			{ insert(first, last); }
			
			map(const map<Key,T,Compare,Allocator>& x)
			: _tree(tree_type(x._tree)), _comp(x._comp)
			{ }

			virtual ~map()
			{ }

			map<Key,T,Compare,Allocator>&
			operator=(const map<Key,T,Compare,Allocator>& x)
			{
				_tree = x._tree;
				return *this;
			}

			iterator
			begin()
			{ return iterator(_tree.beginNode()); }

			const_iterator
			begin() const
			{ return const_iterator(_tree.beginNode()); }

			iterator
			end()
			{ return iterator(_tree.endNode()); }

			const_iterator
			end() const
			{ return const_iterator(_tree.endNode()); }

			reverse_iterator
			rbegin()
			{ return reverse_iterator(_tree.beginNode()); }

			const_reverse_iterator
			rbegin() const
			{ return const_reverse_iterator(_tree.beginNode()); }

			reverse_iterator
			rend()
			{ return reverse_iterator(_tree.endNode()); }

			const_reverse_iterator
			rend() const
			{ return const_reverse_iterator(_tree.endNode()); }

			bool
			empty() const
			{ return _tree.empty(); }

			size_type
			size() const
			{ return _tree.size(); }

			size_type
			max_size() const
			{ return _tree.max_size(); }

			mapped_type&
			operator[](const key_type& x)
			{
				ft::pair<iterator, bool> pair
					= insert(ft::make_pair(x, mapped_type()));
				return pair.first->second;
			}

			pair<iterator, bool>
			insert(const value_type& x)
			{
				bool success;

				iterator it(_tree._insert_(x, &success));
				return ft::make_pair(it, success);
			}

			iterator
			insert(iterator position, const value_type& x)
			{
				bool success = 0;

				iterator after_position = position;
				after_position++;
				iterator it = iterator(_tree._insert_(after_position.getCurrentPtr(), x,
							&success));
				return it;
			}

			template <class InputIterator>
			void
			insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>
					::type* = 0)
			{
				bool success = 0;

				InputIterator it = first;
				for (; it != last; it++)
					_tree._insert_(*it, &success);
			}

			void
			erase(iterator position)
			{ _tree._erase_(position.getCurrentPtr()); }

			size_type
			erase(const key_type& x)
			{
				size_type key_nbr = 1;

				iterator elem_to_del = _tree.find(x);
				if (elem_to_del == end())
					key_nbr = 0;
				else
					_tree._erase_(_tree.find(x).getCurrentPtr());
				return key_nbr;
			}

			void
			erase(iterator first, iterator last)
			{ _tree._erase_(first, last); }

			void
			swap(map<Key,T,Compare,Allocator>&);

			void
			clear()
			{ _tree._clear_(_tree.getRoot()); }

			key_compare
			key_comp() const
			{ return _comp; }

			value_compare
			value_comp() const
			{ return value_compare(_comp); }

			iterator
			find(const key_type& x)
			{ return _tree.find(x); }

			const_iterator
			find(const key_type& x) const
			{ return _tree.find(x); }

			size_type
			count(const key_type& x) const
			{ return _tree.count(x); }

			iterator
			lower_bound(const key_type& x)
			{ return _tree.find(x); }

			const_iterator
			lower_bound(const key_type& x) const
			{ return _tree.find(x); }

			iterator
			upper_bound(const key_type& x)
			{
				iterator it = _tree.find(x);
				it++;
				return it;
			}

			const_iterator
			upper_bound(const key_type& x) const
			{
				const_iterator it = _tree.find(x);
				it++;
				return it;
			}

			pair<iterator, iterator>
			equal_range(const key_type& x)
			{
				iterator low_it = lower_bound(x);
				iterator up_it = upper_bound(x);
				return make_pair(low_it, up_it);
			}

			pair<const_iterator, const_iterator>
			equal_range(const key_type& x) const
			{ 
				const_iterator low_it = lower_bound(x);
				const_iterator up_it = upper_bound(x);
				return make_pair(low_it, up_it);
			}

			tree_type& //TODO delete this method before evaluation
			tree(void)
			{ return _tree; }

		private :
			tree_type			_tree;
			key_compare			_comp;
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
				map<Key,T,Compare,Allocator>& y);
}
#endif
