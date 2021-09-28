#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>
#include <iomanip>
#include "rbnode.hpp"

#define LEFTMOST	2
#define LEFTCHILD	1

#define LL			3
#define LR			2
#define RL			1
#define RR			0

namespace ft
{
	template <typename T, class Alloc, class Compare = std::less<T> >
	class rbTree
	{
		public :
			typedef T										value_type;
			typedef ft::rbnode<value_type>					node_type;
			typedef node_type*								node_pointer;
			typedef Alloc									allocator_type;

		private :
			typedef typename Alloc::template rebind<node_type>::other
															node_allocator_type;
		public : 
			rbTree()
			: _nil(make_null_node)
			{ return make_test_tree(); };

			~rbTree();
			
			node_pointer
			beginNode(void) const
			{ return _begin_node; }

			node_pointer
			endNode(void) const
			{ return _end_node; }

			node_pointer
			root(void) const
			{ return _nil->right_child; }


			template <class T>
			node_pointer
			insert(node_pointer nil, node_pointer new_node)
			{
				uint8_t		cfg = 0;

				if (nil->right_child == NULL)
				{
					nil->right_child = new_node;
					new_node->red = false;
					new_node->parent = nil;
					return new_node;
				}
				node_pointer root = nil->right_child;
				new_node->red = true;
				push_back(root, new_node, &cfg);
				check_recolor_rotate(root, new_node, cfg);
				return new_node;
			}

			template <class T>
			node_pointer
			erase(node_pointer *nil, node_pointer *new_node)
			{
			}

		private :
			typedef typename Alloc::template rebind<node_type>::other
															node_allocator_type;
			node_allocator_type	_node_alloc;
			allocator_type		_alloc;
			node_pointer		_nil;
			node_pointer		_begin_node;
			node_pointer		_end_node;

			bool
			isLeftChild(node_pointer *parent, node_pointer *child)
			{
				if (parent->left_child == child)
					return true;
				return false;
			}

			template <class T>
			node_pointer
			grandParent(node_pointer *node)
			{
				if (node->parent == NULL)
					return NULL;
				return node->parent->parent;
			}

			template <class T>
			node_pointer
			uncle(node_pointer *node)
			{
				if (node->parent == NULL)
					return NULL;
				if (grandParent(node) == NULL)
					return NULL;
				if (isLeftChild(grandParent(node), node->parent))
					return grandParent(node)->right_child;
				return grandParent(node)->left_child;
			}

			late <class T>
			node_pointer
			rotRight(node_pointer *node)
			{
				std::cout << "######## internal of rotRight #######" << std::endl;
				node_pointer *tmp;

				std::cout << "node " << node->left_child->right_child;
				std::cout << " go to tmp" << std::endl;
				tmp = node->left_child->right_child;

				if (isLeftChild(node->parent, node))
					node->parent->left_child = node->left_child;
				else
					node->parent->right_child = node->left_child;

				std::cout << "node " << node->parent;
				std::cout << " go to node->left_child->parent" << std::endl;
				node->left_child->parent = node->parent;

				std::cout << "node " << node->left_child;
				std::cout << " go to node->parent" << std::endl;
				node->parent = node->left_child;

				std::cout << "node " << node << " go to node->parent->right_child";
				std::cout << std::endl;
				node->parent->right_child = node;

				if (tmp)
				{
					std::cout << "node " << node;
					std::cout << " go to tmp->parent" << std::endl;
					tmp->parent = node;
				}

				std::cout << "node " << tmp ;
				std::cout << " go to node->left_child" << std::endl;
				node->left_child = tmp;

				std::cout << "######## internal of rotRight #######" << std::endl;
				return node;
			}

			template <class T>
			node_pointer
			rotLeft(node_pointer *node)
			{
				std::cout << "######## internal of rotLeft #######" << std::endl;

				node_pointer tmp = node->right_child->left_child;

				if (isLeftChild(node->parent, node))
					node->parent->left_child = node->right_child;
				else
					node->parent->right_child = node->right_child;

				std::cout << "node " << node->parent;
				std::cout << " go to node->right_child->parent" << std::endl;
				node->right_child->parent = node->parent;


				std::cout << "node " << node->parent;
				std::cout << " go to node->right_child->parent" << std::endl;
				node->right_child->parent = node->parent;

				std::cout << "node " << node->right_child;
				std::cout << " go to node->parent" << std::endl;
				node->parent = node->right_child;

				std::cout << "node " << node << "go to ";
				std::cout << "node->parent->left_child" << std::endl;
				node->parent->left_child = node;

				std::cout << "node " << tmp << "go to ";
				std::cout << "node->right_child" << std::endl;
				node->right_child = tmp;

				std::cout << "node->value : " << node->value << std::endl;
				std::cout << "######## internal of rotLeft #######" << std::endl;

				return node;
			}

			template <class T>
			void
			push_back(node_pointer *root, node_pointer *new_node, uint8_t *cfg)
			{
				if (new_node->value < root->value)
				{
					if (root->left_child == NULL)
					{	
						*cfg |= LEFTCHILD;
						root->left_child = new_node;
						new_node->parent = root;
						return ;
					}
					*cfg |= LEFTMOST;
					push_back(root->left_child, new_node, cfg);
				}
				else
				{
					if (root->right_child == NULL)
					{	
						root->right_child = new_node;
						new_node->parent = root;
						return ;
					}
					*cfg = 0;
					push_back(root->right_child, new_node, cfg);
				}
			}

			template <class T>
			node_pointer
			get_nil(node_pointer *start_node)
			{
				node_pointer head = start_node;

				while (head != head->parent)
					head = head->parent;
				return head;
			}

			template <class T>
			void
			rotate_recolor(node_pointer *new_node, uint8_t cfg)
			{
				node_pointer *grand_parent = grandParent(new_node);
				node_pointer *parent = new_node->parent;

				switch (cfg)
				{
					case LL:
						std::cout << "LL" << std::endl;
						rotRight(grand_parent);
						grand_parent->red = !grand_parent->red;
						parent->red = !parent->red;
						break;
					case LR:
						std::cout << "LR" << std::endl;
						rotLeft(parent);
						rotRight(grand_parent);
						new_node->red = !new_node->red;
						new_node->right_child->red = !new_node->right_child->red;
						break;
					case RR:
						std::cout << "RR" << std::endl;
						rotLeft(grand_parent);
						grand_parent->red = !grand_parent->red;
						parent->red = !parent->red;
						break;
					case RL:
						std::cout << "RL" << std::endl;
						rotRight(parent);
						std::cout << "intermediary print" << std::endl;
						print_tree(get_nil(new_node));
						rotLeft(grand_parent);
						new_node->red = !new_node->red;
						new_node->left_child->red = !new_node->left_child->red;
						std::cout << "grand_parent value : " << grand_parent->value;
						std::cout << std::endl;
						std::cout << "parent value : " << parent->value << std::endl;
						break;
				}
			}

			template <class T>
			void
			check_recolor_rotate(node_pointer *root, node_pointer *new_node, uint8_t cfg)
			{
				if (new_node == root)
					new_node->red = false;
				if (!new_node->parent->red)
					return ;
				if (!uncle(new_node))
				{
					rotate_recolor(new_node, cfg);
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
					rotate_recolor(new_node, cfg);
			}

			/*
			 * in this implementation of red black delete
			 * there isnt copy of predecessor/successor
			 * just pointers update (and eventually more rotations)
			 * to avoid large data copy for complex_type
			 */
			template <class T>
			node_pointer
			bst_delete(node_pointer del_node)
			{
				if (!del_node->left_child && !del_node->right_child)
				{
				}
			}

			template <class T>
			node_pointer
			leftmost(node_pointer start_node)
			{
				node_pointer head = start_node;
				while (head->left_child)
					head = head->left_child;
				return head;
			}

			template <class T>
			node_pointer
			rightmost(node_pointer start_node)
			{
				node_pointer head = start_node;
				while (head->right_child)
					head = head->right_child;
				return head;
			}

			//-------------for tree printing-------------------
			template <class T>
			node_pointer
			previous_node(node_pointer start_node, int *height)
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

			#define RED "\e[0;31m"
			#define RESET "\e[0;0m"

			template <class T>
			void
			print_tree(node_pointer nil_node)
			{
				std::cout << std::endl;
				std::cout << "--------------------" << std::endl;
				std::cout << std::endl;
				int height = 0;

				node_pointer head = nil_node->right_child;
				while (head->right_child)
				{
					head = head->right_child;
					height++;
				}
				while (head != nil_node)
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
			clear_tree(node_pointer root)
			{	
				if (root->left_child)
					clear_tree(root->left_child);
				if (root->right_child)
					clear_tree(root->right_child);
				_alloc.destroy(&root->pair);
				_node_alloc.deallocate(root, 1);
			}

			node_pointer
			make_null_node(void)
			{
				node_pointer null_node = _node_alloc.allocate(1);
				null_node->red = false;
				null_node->parent = null_node;
				null_node->left_child = null_node;
				null_node->right_child = null_node;
				return null_node;
			}

			node_pointer
			make_test_tree(node_pointer null_node)
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

				std::cout << "root addr : " <<  root << std::endl;
				root->left_child = one;
				root->right_child = two;
				root->parent = null_node;
				_alloc.construct(&root->value, make_pair<int, int>(0, 0));
				root->nb = 5;

				one->left_child = three;
				one->right_child = four;
				one->parent = root;
				_alloc.construct(&root->value, make_pair<int, int>(1, 0));
				one->nb = 10;

				two->left_child = five;
				two->right_child = six;
				two->parent = root;
				_alloc.construct(&root->value, make_pair<int, int>(2, 0));
				two->nb = 15;

				three->left_child = seven;
				three->right_child = NULL;
				three->parent = one;
				_alloc.construct(&root->value, make_pair<int, int>(3, 0));
				three->nb = 20;

				four->left_child = NULL;
				four->right_child = eight;
				four->parent = one;
				_alloc.construct(&root->value, make_pair<int, int>(4, 0));
				four->nb = 25;

				five->left_child = NULL;
				five->right_child = NULL;
				five->parent = two;
				_alloc.construct(&root->value, make_pair<int, int>(5, 0));
				five->nb = 30;

				six->left_child = NULL;
				six->right_child = nine;
				six->parent = two;
				_alloc.construct(&root->value, make_pair<int, int>(6, 0));
				six->nb = 35;

				seven->left_child = NULL;
				seven->right_child = NULL;
				seven->parent = three;
				_alloc.construct(&root->value, make_pair<int, int>(7, 0));
				seven->nb = 40;

				eight->left_child = NULL;
				eight->right_child = NULL;
				eight->parent = four;
				_alloc.construct(&root->value, make_pair<int, int>(8, 0));
				eight->nb = 45;

				nine->left_child = ten;
				nine->right_child = NULL;
				nine->parent = six;
				_alloc.construct(&root->value, make_pair<int, int>(9, 0));
				nine->nb = 50;

				ten->left_child = eleven;
				ten->right_child = twelve;
				ten->parent = nine;
				_alloc.construct(&root->value, make_pair<int, int>(10, 0));
				ten->nb = 55;

				eleven->left_child = NULL;
				eleven->right_child = NULL;
				eleven->parent = ten;
				_alloc.construct(&root->value, make_pair<int, int>(11, 0));
				eleven->nb = 60;

				twelve->left_child = NULL;
				twelve->right_child = NULL;
				twelve->parent = ten;
				_alloc.construct(&root->value, make_pair<int, int>(12, 0));
				twelve->nb = 65;
				
				_begin_node = seven;
				_end_node = null_node;

				return root;
			}
	};
}
#endif

