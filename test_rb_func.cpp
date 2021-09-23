#include "map.hpp"
#include "map_iterator.hpp"
#include <map>
#include <iostream>

int main()
{
	typedef	ft::map<int, int>				map_type;
	typedef ft::map<int, int>::node_pointer	node_ptr;

	map_type mp;
	map_type::iterator mit= mp.begin();
	
	for (; mit != mp.end(); mit++)
		std::cout << mit->nb << std::endl;
	
	std::cout << "---------------------------------------" << std::endl;
	
	node_ptr tree = mp.tree();
	node_ptr node_to_rot = rightmost(tree)->left_child; //node 10
	node_ptr node_nine = node_to_rot->parent;
	node_ptr node_six = node_nine->parent;
	node_ptr node_eleven = node_to_rot->left_child;
	node_ptr node_twelve = node_to_rot->right_child;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "node_to_rot : " << node_to_rot << std::endl;
	std::cout << "node_six : " << node_six << std::endl;
	std::cout << "node_nine : " << node_nine << std::endl;
	std::cout << "node_eleven : " << node_eleven << std::endl;
	std::cout << "node_twelve : " << node_twelve << std::endl;
	std::cout << "---------------------------------------" << std::endl;

	std::cout << node_to_rot->nb << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	ft::rotRight(node_to_rot);
	std::cout << (node_six->right_child == node_to_rot) << std::endl;
	std::cout << (node_to_rot->right_child == node_nine) << std::endl;
	std::cout << (node_to_rot->left_child == node_eleven) << std::endl;
	std::cout << (node_to_rot->parent == node_six) << std::endl;
	std::cout << (node_nine->parent == node_to_rot) << std::endl;
	std::cout << (node_nine->left_child == node_twelve) << std::endl;
	std::cout << (node_nine->right_child == NULL) << std::endl;
	std::cout << "---------------------------------------" << std::endl;

	for (mit = mp.begin(); mit != mp.end(); mit++)
		std::cout << mit->nb << std::endl;
	
	return 0;
}
