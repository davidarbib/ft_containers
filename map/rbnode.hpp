/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:22:14 by darbib            #+#    #+#             */
/*   Updated: 2021/09/28 13:53:17 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"
#include <iostream>
#include <iomanip>

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
		if (isLeftChild(grandParent(node), node->parent))
			return grandParent(node)->right_child;
		return grandParent(node)->left_child;
	}

	template <class T>
	rbnode<T>*
	rotRight(rbnode<T> *node)
	{
		std::cout << "######## internal of rotRight #######" << std::endl;
		rbnode<T> *tmp;

		std::cout << "node " << node->left_child->right_child << " go to tmp" << std::endl;
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

		std::cout << "node " << tmp << " go to node->left_child" << std::endl;
		node->left_child = tmp;

		std::cout << "######## internal of rotRight #######" << std::endl;
		return node;
	}

	template <class T>
	rbnode<T>*
	rotLeft(rbnode<T> *node)
	{
		std::cout << "######## internal of rotLeft #######" << std::endl;

		rbnode<T>* tmp = node->right_child->left_child;
		
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

	/*
	template <class T>
	void
	push_back(rbnode<T> *root, rbnode<T> *new_node, uint8_t *cfg)
	{
		rbnode<T>* new_node_parent;
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
			*cfg |= LEFTCHILD;
		}
		else
			new_node_parent->right_child = new_node;
		new_node->parent = new_node_parent;
	}
	*/

	template <class T>
	void
	push_back(rbnode<T> *root, rbnode<T> *new_node, uint8_t *cfg)
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
	rbnode<T>*
	get_nil(rbnode<T> *start_node)
	{
		rbnode<T>* head = start_node;
		
		while (head != head->parent)
			head = head->parent;
		return head;
	}

	template <class T>
	void
	rotate_recolor(rbnode<T> *new_node, uint8_t cfg)
	{
		rbnode<T> *grand_parent = grandParent(new_node);
		rbnode<T> *parent = new_node->parent;

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
	check_recolor_rotate(rbnode<T> *root, rbnode<T> *new_node, uint8_t cfg)
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

	template <class T>
	rbnode<T>*
	insert(rbnode<T> *nil, rbnode<T> *new_node)
	{
		uint8_t		cfg = 0;
		
		if (nil->right_child == NULL)
		{
			nil->right_child = new_node;
			new_node->red = false;
			new_node->parent = nil;
			return new_node;
		}
		rbnode<T> *root = nil->right_child;
		new_node->red = true;
		push_back(root, new_node, &cfg);
		check_recolor_rotate(root, new_node, cfg);
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

	//-------------for tree printing-------------------
	template <class T>
	rbnode<T>*
	previous_node(rbnode<T>* start_node, int *height)
	{
		if (start_node->left_child)
		{
			rbnode<T>* head = start_node->left_child;
			(*height)++;
			while (head->right_child)
			{
				(*height)++;
				head = head->right_child;
			}
			return head;
		}
		rbnode<T>* previous = start_node;
		rbnode<T>* head = start_node->parent;
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
	print_tree(rbnode<T> *nil_node)
	{
		std::cout << std::endl;
		std::cout << "--------------------" << std::endl;
		std::cout << std::endl;
		int height = 0;

		rbnode<T>* head = nil_node->right_child;
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
}

#endif
