#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"
#include <iostream>

#define LEFTMOST	2
#define LEFTCHILD	1

#define LL			3
#define LR			2
#define RL			1
#define RR			0

namespace ft
{
	template <class T>
	struct rbnode
	{
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
		T						value;
		bool					red;
		int						nb;
	};

	template <class T>
	bool
	isLeftChild(rbnode<T> *parent, rbnode<T> *child)
	{
		if (parent->left_child == child)
			return true;
		return false;
	}

	template <class T>
	rbnode<T>*
	grandParent(rbnode<T> *node)
	{
		if (node->parent == NULL)
			return NULL;
		return node->parent->parent;
	}

	template <class T>
	rbnode<T>*
	uncle(rbnode<T> *node)
	{
		if (node->parent == NULL)
			return NULL;
		if (grandParent(node) == NULL)
			return NULL;
		if (isLeftChild(grandParent(node)))
			return grandParent(node)->right_child;
		return grandParent(node)->left_child;
	}

	template <class T>
	rbnode<T>*
	rotRight(rbnode<T> *node)
	{
		std::cout << "######## internal of rotRight #######" << std::endl;
		rbnode<T> *tmp;

		std::cout << "node " << node->right_child << " go to tmp" << std::endl;
		tmp = node->right_child;
		
		if (isLeftChild(grandParent(node), node->parent))
			grandParent(node)->left_child = node;
		else
			grandParent(node)->right_child = node;

		std::cout << "node " << node->parent;
		std::cout << " go to node right child" << std::endl;
		node->right_child = node->parent;

		std::cout << "node " << node->right_child->parent;
		std::cout << " go to node->parent" << std::endl;
		node->parent = node->right_child->parent;

		std::cout << "node " << node << " go to right_child->parent" << std::endl;
		node->right_child->parent = node;

		std::cout << "node " << node->right_child << " go to tmp->parent" << std::endl;
		tmp->parent = node->right_child;

		std::cout << "node " << tmp << " go to right_child->left_child" << std::endl;
		node->right_child->left_child = tmp;

		std::cout << "######## internal of rotRight #######" << std::endl;
		return node;
	}

	template <class T>
	rbnode<T>*
	rotLeft(rbnode<T> *node)
	{
		std::cout << "######## internal of rotLeft #######" << std::endl;

		rbnode<T>* tmp;
		
		std::cout << "node " << node->parent;
		std::cout << " go to node->right_child->parent" << std::endl;
		node->right_child->parent = node->parent;

		if (isLeftChild(node->parent, node))
			node->parent->left_child = node->right_child;
		else
			node->parent->right_child = node->right_child;

		std::cout << "node " << node->parent;
		std::cout << " go to node->right_child->parent" << std::endl;
		node->right_child->parent = node->parent;

		std::cout << "node " << node->right_child;
		std::cout << " go to node->parent" << std::endl;
		node->parent = node->right_child;

		std::cout << "node " << node->right_child->left_child;
		std::cout << " go to tmp" << std::endl;
		tmp = node->right_child->left_child;

		std::cout << "node " << node << "go to ";
		std::cout << "node->right_child->left_child" << std::endl;
		node->right_child->left_child = node;
		
		std::cout << "node " << tmp << "go to ";
		std::cout << "node->right_child" << std::endl;
		node->right_child = tmp;

		std::cout << "######## internal of rotLeft #######" << std::endl;

		return node;
	}

	template <class T>
	rbnode<T>*
	push_back(rbnode<T> *root, rbnode<T> *new_node, uint8_t *cfg)
	{
		if (new_node->value < root->value)
		{
			new_node_parent = leftmost(root);
			*cfg |= LEFTMOST;
		}
		else
			new_node_parent = rightmost(root);
		if (new_node->value < new_node_parent->value)
		{
			new_node_parent->left_child = new_node;
			*cfg |= LEFT;
		}
		else
			new_node_parent->right_child = new_node;
		new_node->parent = new_node_parent;
	}

	template <class T>
	void
	rotate_recolor(rbnode<T> *new_node, uint8_t cfg)
	{
		switch (cfg)
		{
			case LL:
				rotRight(grandParent(new_node));
				grandParent(new_node)->red = !grandParent(new_node)->red;
				new_node->parent->red = !new_node->parent->red;
				break;
			case LR:
				rotLeft(new_node->parent);
				rotate_recolor(new_node, LL);
				break;
			case RR:
				rotLeft(grandParent(new_node));
				grandParent(new_node)->red = !grandParent(new_node)->red;
				new_node->parent->red = !new_node->parent->red;
				break;
			case RL:
				rotRight(new_node->parent);
				rotate_recolor(new_node, RR);
				break;
		}
	}

	template <class T>
	void
	check_recolor_rotate(rbnode<T> *root, rbnode<T> *new_node, uint8_t cfg)
	{
		if (new_node == root)
			new_node->red = false;
		if (!new_node->parent->red)
			return ;
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

	template <class T>
	rbnode<T>*
	insert(rbnode<T> *nil, rbnode<T> *new_node)
	{
		rbnode<T> 	*new_node_parent = NULL;
		uint8_t		cfg = 0;
		
		if (nil->right_child == NULL)
		{
			nil->right_child = new_node;
			new_node->red = false;
			return new_node;
		}
		rbnode<T> *root = nil->right_child;
		new_node->red = true;
		push_back(root, new_node, &cfg);
		check_recolor_rotate(root, new_node);
		return new_node;
	}

	template <class T>
	rbnode<T>*
	leftmost(rbnode<T>* start_node)
	{
		rbnode<T>* head = start_node;
		while (head->left_child)
			head = head->left_child;
		return head;
	}

	template <class T>
	rbnode<T>*
	rightmost(rbnode<T>* start_node)
	{
		rbnode<T>* head = start_node;
		while (head->right_child)
			head = head->right_child;
		return head;
	}

	"-------------for tree printing-------------------
	template <class T>
	rbnode<T>*
	previous_node(rbnode<T>* start_node, int *height)
	{
		if (start_node->left_child)
		{
			rbnode<T>* head = start_node;
			while (head->right_child)
			{
				(*height)++;
				head = head->right_child;
			}
		}
		node_pointer previous = start_node;
		node_pointer head = start_node->parent;
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

	#define RED "\u001b[31m"
	#define RESET "\u001b[0m"
	template <class T>
	void
	print_tree(rbnode<T> *nil_node)
	{
		int height = 0;

		rbnode<T>* head = nil_node;
		while (head->right_child)
		{
			head = head->right_child;
			height++;
		}
		while (head != nil_node)
		{
			for (int i = 0; i < height; i++)
				std::cout << "  ";
			if (head->red)
				std::cout << RED << "| " << head->value << " |" <<  RESET << std::endl;
			else
				std::cout << "| " << head->value << " |" << std::endl;
			head = previous_node(head, &height);
		}
	}
}

#endif
