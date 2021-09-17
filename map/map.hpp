#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include "rbnode.hpp"
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
			typedef ft::rbnode<value_type>					node_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
    		typedef std::size_t								size_type;
    		typedef std::ptrdiff_t							difference_type;
			typedef ft::map_iterator<value_type, false>		iterator;
			typedef ft::map_iterator<value_type, true>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			typedef node_type*								node_pointer;
			typedef typename Allocator::template rebind<node_type>::other
															node_allocator_type;

		public:

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
			: _alloc(Allocator()), _tree(make_nil_node()), _size(0),
				_comp(comp)
			{ _tree->right_child = make_test_tree(_tree); }

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& = Allocator());
			//{ }
			
			map(const map<Key,T,Compare,Allocator>& x);

			virtual ~map()
			{ }

			map<Key,T,Compare,Allocator>&
			operator=(const map<Key,T,Compare,Allocator>& x);

			iterator
			begin()
			{ return iterator(_begin_node); }

			const_iterator
			begin() const
			{ return const_iterator(_begin_node); }

			iterator
			end()
			{ return iterator(_end_node); }

			const_iterator
			end() const
			{ return const_iterator(_end_node); }

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			bool
			empty() const
			{ return _size == 0; }

			size_type
			size() const
			{ return _size; }

			size_type
			max_size() const;

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
			clear();

			key_compare
			key_comp() const;

			value_compare
			value_comp() const;

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

		private :
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			node_pointer		_tree;
			size_type			_size;
			node_pointer		_begin_node;
			node_pointer		_end_node;
			key_compare			_comp;
			
			node_pointer
			make_nil_node(void)
			{
				node_pointer nil_node = _node_alloc.allocate(1);
				nil_node->red = false;
				nil_node->parent = nil_node;
				nil_node->left_child = nil_node;
				nil_node->right_child = nil_node;
				return nil_node;
			}
			
			node_pointer
			make_test_tree(node_pointer nil_node)
			{
				_size = 12;
				node_pointer root = _node_alloc.allocate(1);
				node_pointer one = _node_alloc.allocate(1);
				node_pointer two = _node_alloc.allocate(1);
				node_pointer three = _node_alloc.allocate(1);
				node_pointer four = _node_alloc.allocate(1);
				node_pointer five = _node_alloc.allocate(1);
				node_pointer six = _node_alloc.allocate(1);
				node_pointer seven = _node_alloc.allocate(1);
				node_pointer eight = _node_alloc.allocate(1);
				node_pointer nine = _node_alloc.allocate(1);
				node_pointer ten = _node_alloc.allocate(1);
				node_pointer eleven = _node_alloc.allocate(1);
				node_pointer twelve = _node_alloc.allocate(1);

				
				root->left_child = one;
				root->right_child = two;
				root->parent = nil_node;
				_alloc.construct(&root->pair, make_pair<int, int>(0, 0));
				root->nb = 5;

				one->left_child = three;
				one->right_child = four;
				one->parent = root;
				_alloc.construct(&root->pair, make_pair<int, int>(1, 0));
				one->nb = 10;

				two->left_child = five;
				two->right_child = six;
				two->parent = root;
				_alloc.construct(&root->pair, make_pair<int, int>(2, 0));
				two->nb = 15;

				three->left_child = seven;
				three->right_child = NULL;
				three->parent = one;
				_alloc.construct(&root->pair, make_pair<int, int>(3, 0));
				three->nb = 20;

				four->left_child = NULL;
				four->right_child = eight;
				four->parent = one;
				_alloc.construct(&root->pair, make_pair<int, int>(4, 0));
				four->nb = 25;

				five->left_child = NULL;
				five->right_child = NULL;
				five->parent = two;
				_alloc.construct(&root->pair, make_pair<int, int>(5, 0));
				five->nb = 30;

				six->left_child = NULL;
				six->right_child = nine;
				six->parent = two;
				_alloc.construct(&root->pair, make_pair<int, int>(6, 0));
				six->nb = 35;

				seven->left_child = NULL;
				seven->right_child = NULL;
				seven->parent = three;
				_alloc.construct(&root->pair, make_pair<int, int>(7, 0));
				seven->nb = 40;

				eight->left_child = NULL;
				eight->right_child = NULL;
				eight->parent = four;
				_alloc.construct(&root->pair, make_pair<int, int>(8, 0));
				eight->nb = 45;

				nine->left_child = ten;
				nine->right_child = NULL;
				nine->parent = six;
				_alloc.construct(&root->pair, make_pair<int, int>(9, 0));
				nine->nb = 50;

				ten->left_child = eleven;
				ten->right_child = twelve;
				ten->parent = nine;
				_alloc.construct(&root->pair, make_pair<int, int>(10, 0));
				ten->nb = 55;

				eleven->left_child = NULL;
				eleven->right_child = NULL;
				eleven->parent = ten;
				_alloc.construct(&root->pair, make_pair<int, int>(11, 0));
				eleven->nb = 60;

				twelve->left_child = NULL;
				twelve->right_child = NULL;
				twelve->parent = ten;
				_alloc.construct(&root->pair, make_pair<int, int>(12, 0));
				twelve->nb = 65;
				
				_begin_node = seven;
				_end_node = twelve;

				return root;
			}
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
