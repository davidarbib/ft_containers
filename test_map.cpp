#include <iostream>
#include <map>
#include "map.hpp"
#include "rbtree.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

int main()
{
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
