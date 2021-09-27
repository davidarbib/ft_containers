#include <iostream>
#include <map>
#include "map.hpp"
#include "rbnode.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

int main()
{
	/*-----------Test tree visualizer-------------*/

	ft::rbnode<int>* nil = new ft::rbnode<int>();
	ft::rbnode<int>* node0 = new ft::rbnode<int>();
	ft::rbnode<int>* node1 = new ft::rbnode<int>();
	ft::rbnode<int>* node2 = new ft::rbnode<int>();
	ft::rbnode<int>* node3 = new ft::rbnode<int>();
	
	nil->value = 0;
	nil->left_child = nil;
	nil->right_child = node0;
	nil->parent = nil;

	node0->value = 10;
	node0->left_child = node1;
	node0->right_child = node2;
	node0->parent = nil;
	node0->red = false;

	node1->value = 5;
	node1->left_child = node3;
	node1->right_child = NULL;
	node1->parent = node0;
	node1->red = true;

	node3->value = 3;
	node3->left_child = NULL;
	node3->right_child = NULL;
	node3->parent = node1;
	node3->red = true;

	node2->value = 15;
	node2->left_child = NULL;
	node2->right_child = NULL;
	node2->parent = node0;
	node2->red = true;

//	std::cout << "root is : " << 
	print_tree(nil);
	/*
	rbnode<int>* node0 = malloc(sizeof(rbnode<int>);
	node0->value = 10;

	rbnode<int>* node0 = malloc(sizeof(rbnode<int>);
	node0->value = 10;

	rbnode<int>* node0 = malloc(sizeof(rbnode<int>);
	node0->value = 10;
	*/
	
	return 0;
}
