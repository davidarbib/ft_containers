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

	return 0;
}
*/

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

	return 0;
}
