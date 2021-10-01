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
	template <typename T, class Alloc = std::allocator<T>,
			 	class Compare = std::less<T> >
	class rbTree
	{
		public :
			typedef T										value_type;
			typedef ft::rbnode<value_type>					node_type;
			typedef node_type*								node_pointer;
			typedef Alloc									allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;

		private :
			typedef typename Alloc::template rebind<node_type>::other
															node_allocator_type;
		public : 
			rbTree()
			: _nil(make_null_node())
			{ }

			~rbTree()
			{ clear(_nil->right_child); }
			
			node_pointer
			beginNode(void) const
			{ return _begin_node; }

			node_pointer
			endNode(void) const
			{ return _end_node; }

			node_pointer
			root(void) const
			{ return _nil->right_child; }

			node_pointer
			get_node_whose_value(node_pointer root, const_reference value) const
			{
				if (root == NULL)
					return NULL;
				if (root->value == value)
					return root;
				if (value < root->value)
					return get_node_whose_value(root->left_child, value);
				return get_node_whose_value(root->right_child, value);
			}

			node_pointer
			insert(const_reference value)
			{
				uint8_t		cfg = 0;

				node_pointer new_node = createNode(value);
				if (_nil->right_child == NULL)
				{
					_nil->right_child = new_node;
					new_node->red = false;
					new_node->parent = _nil;
					return new_node;
				}
				node_pointer root = _nil->right_child;
				new_node->red = true;
				push_back(root, new_node, &cfg);
				check_recolor_rotate(root, new_node, cfg);
				return new_node;
			}
			
			node_pointer
			_erase_(const_reference value)
			{ erase(get_node_whose_value(tree.root(), value)); }

			node_pointer
			erase(node_pointer *node_to_del)
			{
				

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

		private :
			node_allocator_type	_node_alloc;
			allocator_type		_alloc;
			node_pointer		_nil;
			node_pointer		_begin_node;
			node_pointer		_end_node;
			
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
					_alloc.construct(&node->value, value);
					return node;
				}
				catch (std::bad_alloc &e)
				{
					std::cout << e.what() << std::endl;
				}
				return node;
			}

			bool
			isLeftChild(node_pointer parent, node_pointer child)
			{
				if (parent->left_child == child)
					return true;
				return false;
			}

			node_pointer
			grandParent(node_pointer node)
			{
				if (node->parent == NULL)
					return NULL;
				return node->parent->parent;
			}

			node_pointer
			uncle(node_pointer node)
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
			sibling(node_pointer node)
			{
				if (node->parent == NULL)
					return NULL;
				if (isLeftChild(node->parent, node))
					return node->parent->right_child;
				return node->parent->left_child;
			}

			node_pointer
			rotRight(node_pointer node)
			{
				std::cout << "######## internal of rotRight #######" << std::endl;
				node_pointer tmp;

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

			node_pointer
			rotLeft(node_pointer node)
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

			void
			push_back(node_pointer root, node_pointer new_node, uint8_t *cfg)
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

			node_pointer
			get_nil(node_pointer start_node)
			{
				node_pointer head = start_node;

				while (head != head->parent)
					head = head->parent;
				return head;
			}

			void
			rotate_recolor(node_pointer new_node, uint8_t cfg)
			{
				node_pointer grand_parent = grandParent(new_node);
				node_pointer parent = new_node->parent;

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
						print_tree();
						rotLeft(grand_parent);
						new_node->red = !new_node->red;
						new_node->left_child->red = !new_node->left_child->red;
						std::cout << "grand_parent value : " << grand_parent->value;
						std::cout << std::endl;
						std::cout << "parent value : " << parent->value << std::endl;
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
			void
			bst_delete(node_pointer del_node)
			{
				if (!del_node->left_child && !del_node->right_child)
				{
					destroy_node(del_node);
					return ;
				}
				if (del_node->right_child)
				{
					del_node->parent->right_child;
				}
				/*
				else
				{
					del_node_parent->
					destroy_node(del_node);
					return ;
				}
				*/
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

			void
			clear(node_pointer root)
			{	
				if (root == NULL)
					return ;
				if (root->left_child)
					clear(root->left_child);
				if (root->right_child)
					clear(root->right_child);
				_alloc.destroy(&root->value);
				_node_alloc.deallocate(root, 1);
			}

			node_pointer
			make_null_node(void)
			{
				node_pointer null_node = _node_alloc.allocate(1);
				null_node->red = false;
				null_node->parent = null_node;
				null_node->left_child = null_node;
				null_node->right_child = NULL;
				return null_node;
			}
	};
}
#endif

