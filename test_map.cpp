#include <iostream>
#include <map>
#include "map.hpp"
#include "rbtree.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

int main()
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

	return 0;
}

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
{
	ft::rbTree<int> tree;
	std::cout << tree.isRedNode(NULL) << std::endl;
	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/

/*
int main()
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

	return 0;
}
*/
