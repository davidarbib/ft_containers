#include <iostream>
#include <map>
#include "map.hpp"
#include "rbtree.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

void
RRcase(void)
{
	//RR case
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(15);
	tree.print_tree();
	tree.insert(12);
	tree.print_tree();
	tree.insert(17);
	tree.print_tree();

	std::cout << "--- erase 5 ---" << std::endl;
	tree._erase_(5);
	tree.print_tree();
	tree.printInOrderValues();
}

void
RLcase(void)
{
	//RL case
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(15);
	tree.print_tree();
	tree.insert(12);
	tree.print_tree();

	std::cout << "--- erase 5 ---" << std::endl;
	tree._erase_(5);
	tree.print_tree();
	tree.printInOrderValues();
}

void
LLcase()
{
	//LL case
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(15);
	tree.print_tree();
	tree.insert(3);
	tree.print_tree();
	tree.insert(6);
	tree.print_tree();

	std::cout << "--- erase 15 ---" << std::endl;
	tree._erase_(15);
	tree.print_tree();
	tree.printInOrderValues();
}

void
LRcase(void)
{
	//LR case
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(15);
	tree.print_tree();
	tree.insert(6);
	tree.print_tree();

	std::cout << "--- erase 15 ---" << std::endl;
	tree._erase_(15);
	tree.print_tree();
	tree.printInOrderValues();
}

void
c_case(void)
{
	//c) case
	ft::rbTree<int> tree;

	tree.insert(20);
	tree.print_tree();
	tree.insert(10);
	tree.print_tree();
	tree.insert(25);
	tree.print_tree();
	tree.insert(21);
	tree.print_tree();
	tree.insert(35);
	tree.print_tree();
	tree.insert(30);
	tree.print_tree();

	std::cout << "--- erase 15 ---" << std::endl;
	tree._erase_(10);
	tree.print_tree();
	tree.printInOrderValues();
}

void
b_case(void)
{
	//b) case
	ft::rbTree<int> tree;

	tree.insert(15);
	tree.print_tree();
	tree.insert(3);
	tree.print_tree();
	tree.insert(20);
	tree.print_tree();
	tree.insert(1);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(0);
	tree.print_tree();
	tree.insert(2);
	tree.print_tree();
	tree._erase_(0);
	tree.print_tree();
	tree._erase_(2);
	tree.print_tree();
	
	std::cout << "--- erase 1 ---" << std::endl;
	tree._erase_(1);
	tree.print_tree();
	tree.printInOrderValues();
}

void
complex1(void)
{
	//intern node, left_child exists, rightmost with left_child case
	ft::rbTree<int> tree;

	tree.insert(15);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(25);
	tree.print_tree();
	tree.insert(3);
	tree.print_tree();
	tree.insert(7);
	tree.print_tree();
	tree.insert(6);
	tree.print_tree();
	
	std::cout << "--- erase 15 ---" << std::endl;
	tree._erase_(15);
	tree.print_tree();
	tree.printInOrderValues();
}

void
complex2(void)
{
	//intern node, left_child exists, rightmost without left_child case
	ft::rbTree<int> tree;

	tree.insert(15);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(25);
	tree.print_tree();
	tree.insert(3);
	tree.print_tree();
	tree.insert(7);
	tree.print_tree();
	tree.insert(6);
	tree.print_tree();
	tree._erase_(6);
	tree.print_tree();
	
	std::cout << "--- erase 15 ---" << std::endl;
	tree._erase_(15);
	tree.print_tree();
	tree.printInOrderValues();
}

void
complex3(void)
{
	//intern node, left_child dont exist case
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(20);
	tree.print_tree();
	tree.insert(25);
	tree.print_tree();
	
	std::cout << "--- erase 20 ---" << std::endl;
	tree._erase_(20);
	tree.print_tree();
	tree.printInOrderValues();
}

/*
int main()
{
	ft::rbTree<int> tree;
	std::cout << tree.isRedNode(NULL) << std::endl;
	return 0;
}
*/

void
smallest_tree_all_black()
{
	//root node, smallest tree, all black
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(20);
	tree.print_tree();
	tree.insert(25);
	tree.print_tree();
	tree._erase_(25);
	tree.print_tree();
	
	std::cout << "--- erase 10 ---" << std::endl;
	tree._erase_(10);
	tree.print_tree();
	tree.printInOrderValues();
}

void
smallest_tree_red_leafs()
{
	//root node, smallest tree, red leafs
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	tree.insert(20);
	tree.print_tree();
	
	std::cout << "--- erase 10 ---" << std::endl;
	tree._erase_(10);
	tree.print_tree();
	tree.printInOrderValues();
}

void
root_node()
{
	//just root node
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	
	std::cout << "--- erase 10 ---" << std::endl;
	tree._erase_(10);
	tree.print_tree();
	tree.printInOrderValues();
}

void
root_node_one_left_erase_root()
{
	//just root node with one left child
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	
	std::cout << "--- erase 10 ---" << std::endl;
	tree._erase_(10);
	tree.print_tree();
	tree.printInOrderValues();
}

void
root_node_one_left_erase_leaf()
{
	//just root node with one left child
	ft::rbTree<int> tree;

	tree.insert(10);
	tree.print_tree();
	tree.insert(5);
	tree.print_tree();
	
	std::cout << "--- erase 5 ---" << std::endl;
	tree._erase_(5);
	tree.print_tree();
	tree.printInOrderValues();
}

int main()
{
	RRcase();
	//RLcase();
	//LLcase();
	//LRcase();
	//c_case();
	//b_case();
	//complex1();
	//complex2();
	//complex3();
	//smallest_tree_all_black();
	//smallest_tree_red_leafs();
	//root_node();
	//root_node_one_left_erase_root();
	//root_node_one_left_erase_leaf();
	return 0;
}
