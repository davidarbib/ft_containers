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
	tree.insert(3);
	tree.print_tree();
	tree.insert(7);
	tree.print_tree();
	tree.insert(2);
	tree.print_tree();
	tree.insert(1);
	tree.print_tree();
	tree.insert(13);
	tree.print_tree();
	tree.insert(14);
	tree.print_tree();
	tree.insert(11);
	tree.print_tree();
	tree.insert(12);
	tree.print_tree();

	ft::rbTree<int>::node_pointer node = tree.get_node_whose_value(tree.root(), 7);
	std::cout << node << std::endl;
	std::cout << node->parent->value << std::endl;
	std::cout << tree.sibling(tree.get_node_whose_value(tree.root(), 13))->value;
	std::cout << std::endl;

	tree._erase_(12);
	tree.print_tree();
	tree._erase_(13);
	tree.print_tree();
	tree._erase_(10);
	tree.print_tree();

	return 0;
}
