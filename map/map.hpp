#ifndef MAP_HPP
# define MAP_HPP

#ifndef TEST_TREE
# define TEST_TREE 0
#endif

#include <functional>
#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"

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
			typedef ft::rbTree<value_type, allocator_type>	tree_type;
    		typedef std::size_t								size_type;
    		typedef std::ptrdiff_t							difference_type;
			typedef ft::map_iterator<value_type, false>		iterator;
			typedef ft::map_iterator<value_type, true>		const_iterator;
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

			map(const Compare& comp = Compare(),
					const Allocator& = Allocator())
			: _alloc(Allocator()), _tree(tree_type()), _size(0),
				_comp(comp)
		#if TEST_TREE == 1
			{ _tree->right_child = make_test_tree(_tree); }
		#else
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();
			}
		#endif  

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& = Allocator());
			/*
			{
				if (!strncmp(typeid(value_type).name(), CHAR_TYPEID, 1))
					_max_size = _alloc.max_size() / 2;
				else
					_max_size = _alloc.max_size();
			}
			*/
			
			map(const map<Key,T,Compare,Allocator>& x);

			virtual ~map()
			{ }

			map<Key,T,Compare,Allocator>&
			operator=(const map<Key,T,Compare,Allocator>& x);

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
			{ return _size == 0; }

			size_type
			size() const
			{ return _size; }

			size_type
			max_size() const
			{ return _max_size; }

			T&
			operator[](const key_type& x);

			pair<iterator, bool>
			insert(const value_type& x);

			iterator
			insert(iterator position, const value_type& x);

			template <class InputIterator>
			void
			insert(InputIterator first, InputIterator last);

			void
			erase(iterator position);

			size_type
			erase(const key_type& x);

			void
			erase(iterator first, iterator last);

			void
			swap(map<Key,T,Compare,Allocator>&);

			void
			clear()
			{
				clear_tree(_tree);
				_size = 0;
			}

			key_compare
			key_comp() const
			{ return _comp; }

			value_compare
			value_comp() const
			{ return value_compare(); }

			iterator
			find(const key_type& x);

			const_iterator
			find(const key_type& x) const;

			size_type
			count(const key_type& x) const;

			iterator
			lower_bound(const key_type& x);

			const_iterator
			lower_bound(const key_type& x) const;

			iterator
			upper_bound(const key_type& x);

			const_iterator
			upper_bound(const key_type& x) const;

			pair<iterator, iterator>
			equal_range(const key_type& x);

			pair<const_iterator, const_iterator>
			equal_range(const key_type& x) const;

			tree_type //TODO delete this method before evaluation
			tree(void)
			{ return _tree; }

		private :
			allocator_type		_alloc;
			tree_type			_tree;
			size_type			_size;
			size_type			_max_size;
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
