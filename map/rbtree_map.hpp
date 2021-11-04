#ifndef RBTREE_MAP_HPP
# define RBTREE_MAP_HPP

#include <iostream>
#include <iomanip>
#include "rbnode.hpp"
#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"
#include <stdint.h>
#include <string.h>
#include "print_pair.hpp"

#define LEFTMOST	2
#define LEFTCHILD	1

#define LL			3
#define LR			2
#define RL			1
#define RR			0

namespace ft
{
	template <typename Key, typename T, class Compare = std::less<T>,
			 	class KeyCompare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class rbTreeMap
	{
		public :
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef ft::rbnode<value_type>					node_type;
			typedef node_type*								node_pointer;
			typedef Alloc									allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef ft::rbtree_iterator<value_type, false>	iterator;
			typedef ft::rbtree_iterator<value_type, true>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::size_t								size_type;

		private :
			typedef typename Alloc::template rebind<node_type>::other
															node_allocator_type;
		public : 
			rbTreeMap(const Compare& cmp = Compare(), 
						const KeyCompare& key_cmp = KeyCompare(),
						const Alloc& alloc = Alloc())
			: _alloc(alloc), _cmp(cmp), _key_cmp(key_cmp),
				_nil(make_null_node()), _begin_node(_nil), _end_node(_nil),
				_size(0)
			{ _max_size = _node_alloc.max_size(); }

			rbTreeMap(const rbTreeMap<Key, T, Compare, KeyCompare, Alloc>& src)
			: _alloc(src._alloc), _cmp(src._cmp), _key_cmp(src._key_cmp),
				_nil(make_null_node()), _size(src._size), _max_size(src._max_size)
			{
				duplicateTree(src.getRoot(), _nil);
				_begin_node = leftmost(getRoot());
				_end_node = _nil;
			}

			virtual ~rbTreeMap()
			{
				//std::cout << "rbtree destructor" << std::endl;
				_clear_();
				_node_alloc.deallocate(_nil, 1);
			}
			
			rbTreeMap&
			operator=(const rbTreeMap<Key, T, Compare, KeyCompare, Alloc>& src)
			{
				_clear_();
				duplicateTree(src.getRoot(), _nil);
				_begin_node = leftmost(getRoot());
				_size = src._size;
				_max_size = src._max_size;
				return *this;
			}
			
			node_pointer
			beginNode(void) const
			{ return _begin_node; }

			node_pointer
			endNode(void) const
			{ return _end_node; }

			bool
			empty() const
			{ return _size == 0; }
			
			size_type
			size() const
			{ return _size; }

			size_type
			max_size() const
			{ return _max_size; }

			node_pointer
			getRoot(void) const
			{ return _nil->right_child; }

			node_pointer
			getNodeWhoseValue(node_pointer root, const_reference value) const
			{
				if (root == NULL)
					return NULL;
				if (root->value == value)
					return root;
				if (value < root->value)
					return getNodeWhoseValue(root->left_child, value);
				return getNodeWhoseValue(root->right_child, value);
			}

			node_pointer
			_insert_(const_reference value, bool *success)
			{	
				node_pointer node = NULL;
				try
				{
					node = insert(value, success);
				}
				catch (std::bad_alloc &e)
				{
					e.what();
				}
				return node;
			}

			node_pointer
			_insert_(iterator hint, const_reference value, bool *success)
			{	
				node_pointer node = NULL;
				try
				{
					if (hint.getCurrentPtr() == _end_node)
						return insert(value, success);
					iterator after_hint = hint;
					after_hint++;
					if (after_hint.getCurrentPtr() != _end_node
							&& _cmp(*hint, value) && _cmp(value, *after_hint))
					{
						node_pointer new_node = createNode(value);
						node = directInsert(hint.getCurrentPtr(),
											new_node, success);
					}
					else if (after_hint.getCurrentPtr() == _end_node
							&& _cmp(*hint, value))
					{
						node_pointer new_node = createNode(value);
						node = directInsert(hint.getCurrentPtr(),
											new_node, success);
					}
					else
						node = insert(value, success);
				}
				catch (std::bad_alloc &e)
				{
					e.what();
				}
				return node;
			}
			
			void
			_erase_(node_pointer node_to_del)
			{ erase(node_to_del); }

			void
			_erase_(iterator first, iterator last)
			{
				iterator it = first;
				node_pointer tmp = NULL;
				int i = 0;
				for (; it != last; it++)
				{
					if (i > 0)
					{
			 			_erase_(tmp);
						i--;
						tmp = NULL;
					}
					tmp = it.getCurrentPtr();
					i++;
				}
				if (tmp)
			 		_erase_(tmp);
			}

			void
			_clear_(void)
			{
				node_pointer tree_root = getRoot();
				if (tree_root)
					clear(tree_root);
				_begin_node = _end_node;
				_size = 0;
				_nil->right_child = NULL;
			}

			void
			clear(node_pointer root)
			{	
				if (root == NULL)
					return ;
				if (root->left_child)
					clear(root->left_child);
				if (root->right_child)
					clear(root->right_child);
				//std::cout << "-----------------------" << std::endl;
				//std::cout << "node to delete is :  ";
				//std::cout << root << std::endl;
				//std::cout << root->value.first << ", ";
				//std::cout << root->value.second << std::endl;
				_alloc.destroy(&root->value);
				//std::cout << "before deallocation" << std::endl;
				_node_alloc.deallocate(root, 1);
				//std::cout << "after deallocation" << std::endl;
			}

			size_type
			count(const key_type& x) const
			{
				if (getNodeWithKey(getRoot(), x) != NULL) 
					return 1;
				return 0;
			}

			iterator
			find(const Key& key)
			{
				node_pointer node;

				node = getNodeWithKey(getRoot(), key);
				if (!node)
					node = _end_node;
				return iterator(node);
			}

			const_iterator
			find(const Key& key) const
			{
				node_pointer node;

				node = getNodeWithKey(getRoot(), key);
				if (!node)
					node = _end_node;
				return const_iterator(node);
			}

			iterator
			findNotLess(const Key& key)
			{ return iterator(getNodeWithKeyNotLess(getRoot(), key)); }

			const_iterator
			findNotLess(const Key& key) const
			{ return const_iterator(getNodeWithKeyNotLess(getRoot(), key)); }

			iterator
			findUpper(const Key& key)
			{ return iterator(getNodeWithKeyGreater(getRoot(), key)); }

			const_iterator
			findUpper(const Key& key) const
			{ return const_iterator(getNodeWithKeyGreater(getRoot(), key)); }

			node_pointer
			getNodeWithKey(node_pointer root, const Key& key) const
			{
				if (root == NULL)
					return NULL;
				if (root->value.first == key)
					return root;
				if (_key_cmp(key, root->value.first))
					return getNodeWithKey(root->left_child, key);
				return getNodeWithKey(root->right_child, key);
			}

			node_pointer
			getNodeWithKeyGreater(node_pointer root, const Key& key) const
			{
				node_pointer greatest = _end_node;
				node_pointer head = root;

				while (head)
				{
					if (_key_cmp(key, head->value.first))
					{
						greatest = head;
						head = head->left_child;
					}
					else
						head = head->right_child;
				}
				return greatest;
			}

			node_pointer
			getNodeWithKeyNotLess(node_pointer root, const Key& key) const
			{
				node_pointer notless = _end_node;
				node_pointer head = root;

				while (head)
				{
					if (keyEqualTo(key, head->value.first))
					{
						notless = head;
						break;
					}
					if (_key_cmp(key, head->value.first))
					{
						notless = head;
						head = head->left_child;
					}
					else
						head = head->right_child;
				}
				return notless;
			}

			#define RED "\e[0;31m"
			#define RESET "\e[0;0m"

			void
			print_tree(void) const
			{
				std::cout << std::endl;
				std::cout << "--------------------" << std::endl;
				std::cout << std::endl;
				int height = 0;

				node_pointer head = _nil->right_child;
				if (head == NULL)
				{
					std::cout << "tree is empty" << std::endl;
					return ;
				}
				while (head->right_child)
				{
					head = head->right_child;
					height++;
				}
				while (head != _nil)
				{
					for (int i = 0; i < height; i++)
						std::cout << "      ";
					if (head->red)
					{
						std::cout << RED;
						std::cout  << "|";
						std::cout << std::setw(3) << head->value;
						std::cout << "|";
						std::cout <<  RESET << std::endl;
					}
					else
					{
						std::cout << "|";
						std::cout << std::setw(3) << head->value;
						std::cout << "|" << std::endl;
					}
					head = previous_node(head, &height);
				}
			}

			void
			printInOrderValues(void) const
			{
				std::cout << std::endl;
				std::cout << "-- in order values --" << std::endl;
				std::cout << std::endl;

				node_pointer head = beginNode();
				while (head != endNode())
				{
					std::cout << head->value << std::endl;
					head = next_node(head);
				}
				std::cout << "---------------------" << std::endl;
				std::cout << std::endl;
			}

		private :
			node_allocator_type	_node_alloc;
			allocator_type		_alloc;
			Compare				_cmp;
			KeyCompare			_key_cmp;
			node_pointer		_nil;
			node_pointer		_begin_node;
			node_pointer		_end_node;
			size_type			_size;
			size_type			_max_size;
			
			bool
			equalTo(const_reference x, const_reference y)
			{ return !_cmp(x, y) && !_cmp(y, x); }

			bool
			keyEqualTo(const Key &x, const Key &y) const
			{ return !_key_cmp(x, y) && !_key_cmp(y, x); }

			void
			duplicateTree(node_pointer src_root, node_pointer parent_dest_tree, bool left = false)
			{
				if (src_root)
				{
					node_pointer new_node = createNode(src_root->value);
					new_node->parent = parent_dest_tree;
					if (left)
						parent_dest_tree->left_child = new_node;
					else
						parent_dest_tree->right_child = new_node;
					new_node->red = src_root->red;
					duplicateTree(src_root->left_child, new_node, true);
					duplicateTree(src_root->right_child, new_node, false);
				}
			}
			
			node_pointer
			createNode(const_reference value)
			{
				node_pointer node = NULL;
				try
				{
					node_pointer node = _node_alloc.allocate(1);
					node->left_child = NULL;
					node->right_child = NULL;
					node->parent = NULL;
					node->red = true;
					_alloc.construct(&node->value, value);
					//std::cout << "node : " << node << std::endl;
					//std::cout << "with value : " << node->value << "created";
					//std::cout << std::endl;
					return node;
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				return node;
			}

			node_pointer
			insert(const_reference value, bool *success)
			{
				uint8_t		cfg = 0;

				if (_nil->right_child == NULL)
				{
					*success = 1;
					node_pointer new_node = createNode(value);
					_nil->right_child = new_node;
					new_node->red = false;
					new_node->parent = _nil;
					_begin_node = new_node;
					_size++;
					return new_node;
				}
				node_pointer root = _nil->right_child;
				node_pointer stop_node = push_back(root, value, &cfg, success);
				if (*success)
				{
					check_recolor_rotate(root, stop_node, cfg);
					_begin_node = leftmost(getRoot());
					if (_begin_node == NULL)
						_begin_node = _nil;
					_size++;
				}
				return stop_node;
			}

			node_pointer
			directInsert(node_pointer hint, node_pointer new_node, bool *success)
			{
				uint8_t		cfg = 0;

				_size++;
				if (hint->right_child)
				{
					node_pointer parent = leftmost(hint->right_child);
					parent->left_child = new_node;		
					new_node->parent = parent;
					if (isLeftChild(parent->parent, parent))
						cfg = LL;
					else
						cfg = RL;
				}
				else
				{
					node_pointer parent = hint;	
					parent->right_child = new_node;
					new_node->parent = parent;
					if (isLeftChild(parent->parent, parent))
						cfg = LR;
					else
						cfg = RR;
				}
				new_node->red = true;
				*success = 1;
				check_recolor_rotate(getRoot(), new_node, cfg);
				_begin_node = leftmost(getRoot());
				return new_node;
			}

			/*
			 * in this implementation of red black delete
			 * there isnt copy of predecessor/successor
			 * just pointers update, to avoid large data copy for complex_type
			 */
			void
			erase(node_pointer del_node)
			{ 
				_size--;
				if (!del_node->left_child && !del_node->right_child)
				{
					if (!del_node->red)
						resolve_double_blackness(del_node);
					destroy_node(del_node);
					_begin_node = leftmost(getRoot());
					if (_begin_node == NULL)
						_begin_node = _nil;
					return ;
				}
				if (del_node->left_child)
				{
					handle_left_case(del_node);
					del_node->parent = NULL;
					destroy_node(del_node);
					_begin_node = leftmost(getRoot());
					if (_begin_node == NULL)
						_begin_node = _nil;
					return ;
				}
				if (isLeftChild(del_node->parent, del_node))
					del_node->parent->left_child = del_node->right_child;
				else
					del_node->parent->right_child = del_node->right_child;
				del_node->right_child->parent = del_node->parent;	
				node_pointer moved_node = del_node->right_child;
				balance(del_node->red, moved_node);
				del_node->parent = NULL;
				destroy_node(del_node);
				_begin_node = leftmost(getRoot());
				if (_begin_node == NULL)
					_begin_node = _nil;
			}


			//(a)if sibling (s) black and at least one sibling child is red (r) : rotations of parent (eventually sibling pre rotation)
			//	LL (s is a left child of his parent and r left child or both children are red
			//	LR (s is left, r right)
			//	RL (s is right, r left)
			//	RR (s is right, r right or both)
			//(b)if s is black and both children are black
			//	recoloring and recur on parent if parent is black
			//(c)if s is red : rotation and recolor old sibling and parent
			//	L (s is left) : right rotate
			//	R (s is right): left rotate
			void
			resolve_double_blackness(node_pointer node)
			{
				uint8_t cfg = 99;

				if (node == getRoot())
				{
					node->red = false;
					return ;
				}
				if (isSiblingBlackNephewRed(node))
				{
					if (isLeftChild(node->parent, sibling(node))
						&& isRedNode(sibling(node)->left_child))
						cfg = LL;
					if (isLeftChild(node->parent, sibling(node))
						&& isRedNode(sibling(node)->right_child)
						&& isBlackNode(sibling(node)->left_child))
						cfg = LR;
					if (!isLeftChild(node->parent, sibling(node))
						&& isRedNode(sibling(node)->left_child)
						&& isBlackNode(sibling(node)->right_child))
						cfg = RL;
					if (!isLeftChild(node->parent, sibling(node))
						&& isRedNode(sibling(node)->right_child))
						cfg = RR;
					//std::cout << "cfg is : " << (int)cfg << std::endl;
					rotate_recolor_erase(sibling(node), cfg);
					return ;
				}
				if (isSiblingBlackNephewsBlack(node))
				{
					sibling(node)->red = true;
					if (!node->parent->red)
						resolve_double_blackness(node->parent);
					else
						node->parent->red = false;
					return ;
				}
				if (isRedNode(sibling(node)))
				{
					node_pointer old_sibling = sibling(node);
					if (isLeftChild(node->parent, node))
						rotLeft(node->parent);
					else
						rotRight(node->parent);
					node->parent->red = !node->parent->red;
					old_sibling->red = !old_sibling->red;
					resolve_double_blackness(node);
				}
			}

			bool
			isLeftChild(node_pointer parent, node_pointer child) const
			{
				if (parent->left_child == child)
					return true;
				return false;
			}

			node_pointer
			grandParent(node_pointer node) const
			{
				if (node->parent == NULL)
					return NULL;
				return node->parent->parent;
			}

			node_pointer
			uncle(node_pointer node) const
			{
				if (node->parent == NULL)
					return NULL;
				if (grandParent(node) == NULL)
					return NULL;
				if (isLeftChild(grandParent(node), node->parent))
					return grandParent(node)->right_child;
				return grandParent(node)->left_child;
			}

			node_pointer
			sibling(node_pointer node) const
			{
				if (node->parent == NULL)
					return NULL;
				if (isLeftChild(node->parent, node))
					return node->parent->right_child;
				return node->parent->left_child;
			}

			bool
			isSiblingBlackNephewsBlack(node_pointer node) const
			{
				if (isBlackNode(sibling(node))
					&& isBlackNode(nephewL(node))
					&& isBlackNode(nephewR(node)))
					return true;
				return false;
			}

			bool
			isSiblingBlackNephewRed(node_pointer node) const
			{
				if (isBlackNode(sibling(node))
					&& (isRedNode(nephewL(node))
						|| isRedNode(nephewR(node))))
					return true;
				return false;
			}
			
			bool
			isBlackNode(node_pointer node) const
			{
				if (!node || !node->red)
					return true;
				return false;
			}

			bool
			isRedNode(node_pointer node) const
			{ return !isBlackNode(node); }

			node_pointer
			nephewL(node_pointer node) const
			{ return sibling(node)->left_child; }

			node_pointer
			nephewR(node_pointer node) const
			{ return sibling(node)->right_child; }

			void
			handle_left_case(node_pointer del_node)
			{
				node_pointer moved_node = rightmost(del_node->left_child); 
				node_pointer rmost_leftchild = moved_node->left_child;
				if (rmost_leftchild)
				{
					moved_node->parent->right_child = rmost_leftchild;
					rmost_leftchild->parent = moved_node->parent;

					if (moved_node != del_node->left_child)
					{
						moved_node->left_child = del_node->left_child;
						del_node->left_child->parent = moved_node;
					}
					if (isLeftChild(del_node->parent, del_node))
						del_node->parent->left_child = moved_node;
					else
						del_node->parent->right_child = moved_node;
					moved_node->parent = del_node->parent;

					moved_node->right_child = del_node->right_child;
					if (del_node->right_child)
					del_node->right_child->parent = moved_node;

					rmost_leftchild->red = false;
					return ;
				}

				node_type v_node;
				v_node.red = false;
				v_node.parent = moved_node->parent;
				v_node.left_child = NULL;
				v_node.right_child = NULL;
				//std::cout << "v_node address : " << &v_node << std::endl;

				if (moved_node != del_node->left_child)
				{
					moved_node->left_child = del_node->left_child;
					del_node->left_child->parent = moved_node;
					moved_node->parent->right_child = NULL;
				}
				else
					moved_node->parent->left_child = &v_node;

				if (isLeftChild(del_node->parent, del_node))
					del_node->parent->left_child = moved_node;
				else
					del_node->parent->right_child = moved_node;
				moved_node->parent = del_node->parent;

				moved_node->right_child = del_node->right_child;
				if (del_node->right_child)
					del_node->right_child->parent = moved_node;

				if (moved_node->red)
					moved_node->red = false;
				else
					resolve_double_blackness(&v_node);
			}
			
			void
			balance(bool del_node_red, node_pointer moved_node)
			{
				if (del_node_red ^ moved_node->red)
				{
					moved_node->red = false;
					return ;
				}
				if (del_node_red == false && moved_node->red == false)
					resolve_double_blackness(moved_node);
			}

			node_pointer
			next_node(node_pointer start_node) const
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
			rotRight(node_pointer node)
			{
				node_pointer tmp = node->left_child->right_child;
				if (isLeftChild(node->parent, node))
					node->parent->left_child = node->left_child;
				else
					node->parent->right_child = node->left_child;
				node->left_child->parent = node->parent;
				node->parent = node->left_child;
				node->parent->right_child = node;
				if (tmp)
					tmp->parent = node;
				node->left_child = tmp;
				return node;
			}

			node_pointer
			rotLeft(node_pointer node)
			{
				node_pointer tmp = node->right_child->left_child;

				if (isLeftChild(node->parent, node))
					node->parent->left_child = node->right_child;
				else
					node->parent->right_child = node->right_child;
				node->right_child->parent = node->parent;
				node->parent = node->right_child;
				node->parent->left_child = node;
				node->right_child = tmp;
				if (tmp)
					tmp->parent = node;
				return node;
			}

			node_pointer
			push_back(node_pointer root, const_reference value,
						uint8_t *cfg, bool *success)
			{
				if (equalTo(value, root->value))
				{
					*success = false;
					return root;
				}
				if (_cmp(value, root->value))
				{
					if (root->left_child == NULL)
					{	
						*cfg |= LEFTCHILD;
						node_pointer new_node = createNode(value);
						root->left_child = new_node;
						new_node->parent = root;
						*success = true;
						return new_node;
					}
					*cfg |= LEFTMOST;
					return push_back(root->left_child, value, cfg, success);
				}
				else
				{
					if (root->right_child == NULL)
					{	
						node_pointer new_node = createNode(value);
						root->right_child = new_node;
						new_node->parent = root;
						*success = true;
						return new_node;
					}
					*cfg = 0;
					return push_back(root->right_child, value, cfg, success);
				}
			}

			node_pointer
			get_nil(node_pointer start_node) const
			{
				node_pointer head = start_node;

				while (head != head->parent)
					head = head->parent;
				return head;
			}

			/*
			void
			rotate_recolor_erase(node_pointer sibling, uint8_t cfg)
			{
				node_pointer parent = sibling->parent;

				switch (cfg)
				{
					case LL:
						sibling->left_child->red = false;
						rotRight(parent);
						break;
					case LR:
						sibling->right_child->red = false;
						rotLeft(sibling);
						rotRight(parent);
						break;
					case RR:
						sibling->right_child->red = false;
						rotLeft(parent);
						break;
					case RL:
						sibling->left_child->red = false;
						rotRight(sibling);
						rotLeft(parent);
						break;
				}
			}
			*/

			void
			rotate_recolor_erase(node_pointer sibling, uint8_t cfg)
			{
				node_pointer parent = sibling->parent;

				switch (cfg)
				{
					case LL:
						rotRight(parent);
						sibling->left_child->red = false;
						break;
					case LR:
						rotLeft(sibling);
						//if (isRedNode(parent))
						swapColor(sibling->parent, sibling);
						rotRight(parent);
						sibling->red = false;
						break;
					case RR:
						rotLeft(parent);
						sibling->right_child->red = false;
						break;
					case RL:
						rotRight(sibling);
						//if (isRedNode(parent))
						swapColor(sibling->parent, sibling);
						rotLeft(parent);
						sibling->red = false;
						break;
				}
				if (isRedNode(parent)
					&& (cfg == RR || cfg == LL))
				{
					parent->red = false;
					sibling->red = true;
					//std::cout << "sibling->parent value ";
					//std::cout << sibling->parent->value.first;
					//std::cout << ", " << sibling->parent->value.second;
					//std::cout << std::endl;
				}
				if (isRedNode(parent)
					&& (cfg == RL || cfg == LR))
				{
					parent->red = false;
					sibling->parent->red = true;
					//std::cout << "sibling->parent value ";
					//std::cout << sibling->parent->value.first;
					//std::cout << ", " << sibling->parent->value.second;
					//std::cout << std::endl;
				}
			}
			
			void
			swapColor(node_pointer node1, node_pointer node2)
			{
				bool tmp_red = node1->red;
				node1->red = node2->red;
				node2->red = tmp_red;
			}
			
			void
			rotate_recolor_insert(node_pointer new_node, uint8_t cfg)
			{
				node_pointer grand_parent = grandParent(new_node);
				node_pointer parent = new_node->parent;

				switch (cfg)
				{
					case LL:
						rotRight(grand_parent);
						grand_parent->red = !grand_parent->red;
						parent->red = !parent->red;
						break;
					case LR:
						rotLeft(parent);
						rotRight(grand_parent);
						new_node->red = !new_node->red;
						new_node->right_child->red = !new_node->right_child->red;
						break;
					case RR:
						rotLeft(grand_parent);
						grand_parent->red = !grand_parent->red;
						parent->red = !parent->red;
						break;
					case RL:
						rotRight(parent);
						rotLeft(grand_parent);
						new_node->red = !new_node->red;
						new_node->left_child->red = !new_node->left_child->red;
						break;
				}
			}

			void
			check_recolor_rotate(node_pointer root, node_pointer new_node,
									uint8_t cfg)
			{
				if (new_node == root)
					new_node->red = false;
				if (!new_node->parent->red)
					return ;
				if (!uncle(new_node))
				{
					rotate_recolor_insert(new_node, cfg);
					return ;
				}
				if (uncle(new_node)->red)
				{
					new_node->parent->red = false;
					uncle(new_node)->red = false;
					grandParent(new_node)->red = true;
					check_recolor_rotate(root, grandParent(new_node), cfg);
				}
				else
					rotate_recolor_insert(new_node, cfg);
			}

			void
			destroy_node(node_pointer node)
			{
				if (node->parent)
				{
					if (isLeftChild(node->parent, node))
						node->parent->left_child = NULL;
					else
						node->parent->right_child = NULL;
				}
				_alloc.destroy(&node->value);
				_node_alloc.deallocate(node, 1);
			}

			node_pointer
			leftmost(node_pointer start_node) const
			{
				node_pointer head = start_node;
				if (!head)
					return NULL;
				while (head->left_child)
					head = head->left_child;
				return head;
			}

			node_pointer
			rightmost(node_pointer start_node) const
			{
				node_pointer head = start_node;
				if (!head)
					return NULL;
				while (head->right_child)
					head = head->right_child;
				return head;
			}

			//-------------for tree printing-------------------
			node_pointer
			previous_node(node_pointer start_node, int *height) const
			{
				if (start_node->left_child)
				{
					node_pointer head = start_node->left_child;
					(*height)++;
					while (head->right_child)
					{
						(*height)++;
						head = head->right_child;
					}
					return head;
				}
				node_pointer previous = start_node;
				node_pointer head = start_node->parent;
				(*height)--;
				while (previous == head->left_child)
				{
					if (previous == head)
						return head;
					previous = head;
					(*height)--;
					head = head->parent;
				}
				return head;
			}

			node_pointer
			make_null_node(void)
			{
				node_pointer null_node = _node_alloc.allocate(1);
				null_node->red = false;
				null_node->parent = null_node;
				null_node->left_child = null_node;
				null_node->right_child = NULL;
				//std::cout << "nil address : " << null_node << std::endl;
				return null_node;
			}
	};
}
#endif
