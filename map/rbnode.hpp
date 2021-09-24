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
			return new_node;
		}
		rbnode<T> *root = nil->right_child;
		push_back(root, new_node, &cfg);
			
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
}

#endif
