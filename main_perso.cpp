//#define __IT_LIFE_DEBUG__ 1

#include <vector.hpp>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
//namespace ft = std;

int main()
{
	std::cout << "|---------------------------------------|" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|              ctors testing            |" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|---------------------------------------|" << std::endl;

	std::vector<int> true_v(3, 42);
	ft::vector<int> mine_v(static_cast<size_t>(3), 42);
	std::cout << "true capacity : " << true_v.capacity() << std::endl;
	std::cout << "true size : " << true_v.size() << std::endl;
	std::cout << "mine capacity : " << mine_v.capacity() << std::endl;
	std::cout << "mine size : " << mine_v.size() << std::endl;
	
	std::cout << true_v[0] << std::endl;
	std::cout << true_v[1] << std::endl;
	std::cout << true_v[2] << std::endl;
	std::cout << mine_v[0] << std::endl;
	std::cout << mine_v[1] << std::endl;
	std::cout << mine_v[2] << std::endl;
	
	std::vector<int> true_empty(0, 42);
	ft::vector<int> mine_empty(static_cast<size_t>(0), 42);
	std::cout << "true capacity : " << true_empty.capacity() << std::endl;
	std::cout << "true size : " << true_empty.size() << std::endl;
	std::cout << "mine capacity : " << mine_empty.capacity() << std::endl;
	std::cout << "mine size : " << mine_empty.size() << std::endl;
	
	std::cout << "----------------------------------------------";
	std::cout << std::endl;

	std::cout << "|---------------------------------------|" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|         iterator use testing          |" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|---------------------------------------|" << std::endl;

	true_v[0] = 4;
	true_v[1] = 12;
	true_v[2] = -5;
	mine_v[0] = 4;
	mine_v[1] = 12;
	mine_v[2] = -5;
	
	std::vector<int>::iterator true_it = true_v.begin();
	ft::vector<int>::iterator mine_it = mine_v.begin();

	std::cout << std::endl << "---------postfix inc---------" << std::endl;

	std::cout << "true way" << std::endl;
	for (true_it = true_v.begin(); true_it != true_v.end(); true_it++)
		std::cout << *true_it << std::endl;

	std::cout << "my way" << std::endl;
	for (mine_it = mine_v.begin(); mine_it != mine_v.end(); mine_it++)
		std::cout << *mine_it << std::endl;
	
	std::cout << std::endl << "---------prefix inc---------" << std::endl;

	std::cout << "true way" << std::endl;
	for (true_it = true_v.begin(); true_it != true_v.end(); ++true_it)
		std::cout << *true_it << std::endl;

	std::cout << "my way" << std::endl;
	for (mine_it = mine_v.begin(); mine_it != mine_v.end(); ++mine_it)
		std::cout << *mine_it << std::endl;

	std::cout << std::endl << "---------postfix dec---------" << std::endl;

	std::cout << "true way" << std::endl;
	for (true_it = true_v.end(); true_it != true_v.begin(); true_it--)
		std::cout << *true_it << std::endl;

	std::cout << "my way" << std::endl;
	for (mine_it = mine_v.end(); mine_it != mine_v.begin(); mine_it--)
		std::cout << *mine_it << std::endl;

	std::cout << std::endl;
	std::cout << "|---------------------------------------|" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|            vector functions           |" << std::endl;
	std::cout << "|                                       |" << std::endl;
	std::cout << "|---------------------------------------|" << std::endl;

	std::cout << std::endl << "---------assign---------" << std::endl;
	std::vector<int> true_v1;
	ft::vector<int> mine_v1;
	std::list<int> true_l1;
	
	true_l1.push_back(3);
	true_l1.push_back(-31);
	true_l1.push_back(8);
	true_l1.push_back(-7);
	true_l1.push_back(1);

	true_v1.assign(true_l1.begin(), true_l1.end());
	for (std::vector<int>::iterator it = true_v1.begin(); it != true_v1.end(); it++)
		std::cout << *it << std::endl;
	
	std::cout << mine_v1.capacity() << std::endl;	
	mine_v1.assign(true_l1.begin(), true_l1.end());
	ft::vector<int>::iterator it = mine_v1.begin();
	for (; it != mine_v1.end(); it++)
		std::cout << *it << std::endl;

	std::cout << std::endl << "---------push_back---------" << std::endl;
	std::vector<int> true_vpush;
	ft::vector<int> mine_vpush;

	true_vpush.push_back(-100);
	//true_vpush.push_back(2);
	//true_vpush.push_back(-35);
	//true_vpush.push_back(73);
	//true_vpush.push_back(45);
	//
	std::cout << "true vector size : " << true_vpush.size() << std::endl;
	std::cout << "true vector capacity : " << true_vpush.capacity() << std::endl;

	for (std::vector<int>::iterator it = true_vpush.begin(); it != true_vpush.end(); it++)
		std::cout << *it << std::endl;

	mine_vpush.push_back(-100);
	//mine_vpush.push_back(2);
	//mine_vpush.push_back(-35);
	//mine_vpush.push_back(73);
	//mine_vpush.push_back(45);

	std::cout << "my vector size : " << mine_vpush.size() << std::endl;
	std::cout << "my vector capacity : " << mine_vpush.capacity() << std::endl;
	for (ft::vector<int>::iterator it = mine_vpush.begin(); it != mine_vpush.end(); it++)
		std::cout << *it << std::endl;

	std::cout << std::endl << "---------resize---------" << std::endl;

	std::vector<int> true_resize_v;
	true_resize_v.push_back(1);
	true_resize_v.push_back(2);
	true_resize_v.push_back(3);
	
	for (std::vector<int>::iterator it = true_resize_v.begin(); it != true_resize_v.end(); it++)
		std::cout << *it << std::endl;

	ft::vector<int> mine_resize_v;
	mine_resize_v.push_back(1);
	mine_resize_v.push_back(2);
	mine_resize_v.push_back(3);
	
	for (ft::vector<int>::iterator it = mine_resize_v.begin(); it != mine_resize_v.end(); it++)
		std::cout << *it << std::endl;

	true_resize_v.resize(0);
	mine_resize_v.resize(0);


	std::cout << "----------after resize----------" << std::endl;

	std::cout << "true try access  : " << true_resize_v[2] << std::endl;
	std::cout << "true vector size : " << true_resize_v.size() << std::endl;
	std::cout << "true vector capacity : " << true_resize_v.capacity() << std::endl;

	for (std::vector<int>::iterator it = true_resize_v.begin(); it != true_resize_v.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "mine try access  : " << mine_resize_v[2] << std::endl;
	std::cout << "mine vector size : " << mine_resize_v.size() << std::endl;
	std::cout << "mine vector capacity : " << mine_resize_v.capacity() << std::endl;

	for (ft::vector<int>::iterator it = mine_resize_v.begin(); it != mine_resize_v.end(); it++)
		std::cout << *it << std::endl;
	
	return 0;
}

