#include <iostream>
#include <map>
#include "map.hpp"
#include "rbnode.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

/*
int main()
{
	//-----------Test tree visualizer-------------

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

	print_tree(nil);
	return 0;
}
*/

int main()
{
	ft::rbnode<int>* nil = new ft::rbnode<int>();
	ft::rbnode<int>* node0 = new ft::rbnode<int>();
	ft::rbnode<int>* node1 = new ft::rbnode<int>();
	ft::rbnode<int>* node2 = new ft::rbnode<int>();
	ft::rbnode<int>* node3 = new ft::rbnode<int>();
	ft::rbnode<int>* node4 = new ft::rbnode<int>();
	ft::rbnode<int>* node5 = new ft::rbnode<int>();
	ft::rbnode<int>* node6 = new ft::rbnode<int>();
	ft::rbnode<int>* node7 = new ft::rbnode<int>();
	ft::rbnode<int>* node8 = new ft::rbnode<int>();
	ft::rbnode<int>* node9 = new ft::rbnode<int>();
	ft::rbnode<int>* node10 = new ft::rbnode<int>();

	nil->value = 0;
	nil->left_child = nil;
	nil->right_child = NULL;
	nil->parent = nil;

	node0->value = 10;
	node1->value = 5;
	node2->value = 15;
	node3->value = 3;
	node4->value = 7;
	node5->value = 2;
	node6->value = 1;
	node7->value = 20;
	node8->value = 12;
	node9->value = 23;
	node10->value = 21;

	ft::insert(nil, node0);
	print_tree(nil);
	std::cout << std::endl;
	ft::insert(nil, node1);
	print_tree(nil);
	ft::insert(nil, node2);
	print_tree(nil);
	ft::insert(nil, node3);
	print_tree(nil);
	ft::insert(nil, node4);
	print_tree(nil);
	ft::insert(nil, node5);
	print_tree(nil);
	ft::insert(nil, node6);
	print_tree(nil);
	ft::insert(nil, node7);
	print_tree(nil);
	ft::insert(nil, node8);
	print_tree(nil);
	ft::insert(nil, node9);
	print_tree(nil);
	ft::insert(nil, node10);
	print_tree(nil);
	return 0;
}
