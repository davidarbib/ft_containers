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

	//std::cout << "true way" << std::endl;
	//for (true_it = true_v.end(); true_it != true_v.begin(); true_it--)
	//	std::cout << *true_it << std::endl;

	//std::cout << "my way" << std::endl;
	//for (mine_it = mine_v.end(); mine_it != mine_v.begin(); mine_it--)
	//	std::cout << *mine_it << std::endl;

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
	true_vpush.push_back(2);
	true_vpush.push_back(-35);
	true_vpush.push_back(73);
	true_vpush.push_back(45);
	//
	std::cout << "true vector size : " << true_vpush.size() << std::endl;
	std::cout << "true vector capacity : " << true_vpush.capacity() << std::endl;

	for (std::vector<int>::iterator it = true_vpush.begin(); it != true_vpush.end(); it++)
		std::cout << *it << std::endl;

	mine_vpush.push_back(-100);
	mine_vpush.push_back(2);
	mine_vpush.push_back(-35);
	mine_vpush.push_back(73);
	mine_vpush.push_back(45);

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

	true_resize_v.resize(2);
	mine_resize_v.resize(2);

	std::cout << "----------after resize----------" << std::endl;

	//std::cout << "true try access  : " << true_resize_v[2] << std::endl;
//	std::vector<int>::iterator end = true_resize_v.end();
//	std::cout << *end << std::endl;
	std::cout << "true vector size : " << true_resize_v.size() << std::endl;
	std::cout << "true vector capacity : " << true_resize_v.capacity() << std::endl;

	for (std::vector<int>::iterator it = true_resize_v.begin();
			it != true_resize_v.end(); it++)
		std::cout << *it << std::endl;

	//std::cout << "mine try access  : " << mine_resize_v[2] << std::endl;
	std::cout << "mine vector size : " << mine_resize_v.size() << std::endl;
	std::cout << "mine vector capacity : " << mine_resize_v.capacity() << std::endl;

	for (ft::vector<int>::iterator it = mine_resize_v.begin();
			it != mine_resize_v.end(); it++)
		std::cout << *it << std::endl;

	
	std::cout << "----------max_size----------" << std::endl;

	std::cout << "true max_size------" << std::endl;
	std::vector<int> int_v;
	std::cout << int_v.max_size() << std::endl;
	std::vector<long> long_v;
	std::cout << long_v.max_size() << std::endl;
	std::vector<char> char_v;
	std::cout << char_v.max_size() << std::endl;
	std::vector<float> float_v;
	std::cout << float_v.max_size() << std::endl;
	std::vector<double> double_v;
	std::cout << double_v.max_size() << std::endl;

	std::cout << "mine max_size------" << std::endl;
	ft::vector<int> int_vm;
	std::cout << int_vm.max_size() << std::endl;
	ft::vector<long> long_vm;
	std::cout << long_vm.max_size() << std::endl;
	ft::vector<char> char_vm;
	std::cout << char_vm.max_size() << std::endl;
	ft::vector<float> float_vm;
	std::cout << float_vm.max_size() << std::endl;
	ft::vector<double> double_vm;
	std::cout << double_vm.max_size() << std::endl;

	std::cout << "----------swap----------" << std::endl;

	std::vector<int> v1;
	std::vector<int> v2;

	ft::vector<int> vm1;
	ft::vector<int> vm2;
	
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

//	v2.push_back(-1);
//	v2.push_back(-2);
//	v2.push_back(-3);
//	v2.push_back(-4);
//	v2.push_back(-5);

	vm1.push_back(1);
	vm1.push_back(2);
	vm1.push_back(3);

//	vm2.push_back(-1);
//	vm2.push_back(-2);
//	vm2.push_back(-3);
//	vm2.push_back(-4);
//	vm2.push_back(-5);

	std::cout << "true vector elems : " << std::endl;
	for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "true vector size : " << v1.size() << std::endl;
	std::cout << "true vector capacity : " << v1.capacity() << std::endl;

	std::cout << "mine vector elems : " << std::endl;
	for (ft::vector<int>::iterator it = vm1.begin(); it != vm1.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "mine vector size : " << vm1.size() << std::endl;
	std::cout << "mine vector capacity : " << vm1.capacity() << std::endl;
	
	v1.swap(v2);
	vm1.swap(vm2);
	std::cout << "after swap---------" << std::endl;

	for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "true vector size : " << v1.size() << std::endl;
	std::cout << "true vector capacity : " << v1.capacity() << std::endl;

	for (ft::vector<int>::iterator it = vm1.begin(); it != vm1.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "mine vector size : " << vm1.size() << std::endl;
	std::cout << "mine vector capacity : " << vm1.capacity() << std::endl;

	std::cout << "----------simple insert----------" << std::endl;

	std::vector<int> v_sinsert;
	std::vector<int> v_empty;
	ft::vector<int> vm_sinsert;
	ft::vector<int> vm_empty;
	
	v_sinsert.push_back(1); 
	v_sinsert.push_back(2); 
	v_sinsert.push_back(3); 
	v_sinsert.push_back(4); 

	vm_sinsert.push_back(1); 
	vm_sinsert.push_back(2); 
	vm_sinsert.push_back(3); 
	vm_sinsert.push_back(4); 
	
	std::cout << "true----------" << std::endl;
	std::vector<int>::iterator pos = v_sinsert.insert(v_sinsert.begin() + 1, -42);
	std::cout << *pos << std::endl;

	for (std::vector<int>::iterator it = v_sinsert.begin(); it != v_sinsert.end(); it++)
		std::cout << *it << std::endl;
	
	//std::vector<int>::iterator random_pos = v_sinsert.insert(v_empty.begin(), -42);
	//(void)random_pos;

	std::cout << "mine----------" << std::endl;
	std::cout << "before----------" << std::endl;
	std::cout << "size : " << vm_sinsert.size() << std::endl;
	std::cout << "capacity : " << vm_sinsert.capacity() << std::endl;

	for (ft::vector<int>::iterator mit = vm_sinsert.begin();
			mit != vm_sinsert.end(); mit++)
		std::cout << *mit << std::endl;

	ft::vector<int>::iterator mpos = vm_sinsert.insert(vm_sinsert.begin() + 1, -42);
	std::cout << "after----------" << std::endl;
	std::cout << "pos : " << *pos << std::endl;

	for (ft::vector<int>::iterator mit = vm_sinsert.begin();
			mit != vm_sinsert.end(); mit++)
		std::cout << *mit << std::endl;
	std::cout << "size : " << vm_sinsert.size() << std::endl;
	std::cout << "capacity : " << vm_sinsert.capacity() << std::endl;

	std::cout << "----------multiple insert----------" << std::endl;

	
	std::vector<int> v_minsert;
	ft::vector<int> vm_minsert;
	
	v_minsert.push_back(1); 
	v_minsert.push_back(2); 
	v_minsert.push_back(3); 
	v_minsert.push_back(4); 

	vm_minsert.push_back(1); 
	vm_minsert.push_back(2); 
	vm_minsert.push_back(3); 
	vm_minsert.push_back(4); 
	
	std::cout << "true----------" << std::endl;
	std::cout << "before : " << std::endl;
	for (std::vector<int>::iterator it = v_minsert.begin(); it != v_minsert.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "size : " << v_minsert.size() << std::endl;
	std::cout << "capacity : " << v_minsert.capacity() << std::endl;

	v_minsert.insert(v_minsert.begin() + 1, 2, -42);
	std::cout << "after : " << std::endl;

	for (std::vector<int>::iterator it = v_minsert.begin(); it != v_minsert.end(); it++)
		std::cout << *it << std::endl;
	
	std::cout << "size : " << v_minsert.size() << std::endl;
	std::cout << "capacity : " << v_minsert.capacity() << std::endl;

	std::cout << "mine----------" << std::endl;
	std::cout << "before :" << std::endl;
	std::cout << "size : " << vm_minsert.size() << std::endl;
	std::cout << "capacity : " << vm_minsert.capacity() << std::endl;

	for (ft::vector<int>::iterator mit = vm_minsert.begin();
			mit != vm_minsert.end(); mit++)
		std::cout << *mit << std::endl;

	vm_minsert.insert(vm_minsert.begin() + 1, 2, -42);
	std::cout << "after : " << std::endl;

	for (ft::vector<int>::iterator mit = vm_minsert.begin();
			mit != vm_minsert.end(); mit++)
		std::cout << *mit << std::endl;
	std::cout << "size : " << vm_minsert.size() << std::endl;
	std::cout << "capacity : " << vm_minsert.capacity() << std::endl;

	std::cout << "--------------operator=----------------" << std::endl;
	
	std::vector<int> v_src;
	v_src.push_back(1);
	v_src.push_back(2);
	v_src.push_back(3);
	v_src.push_back(4);

	std::vector<int> v_dest;
	v_dest = v_src;
	for (std::vector<int>::iterator it = v_dest.begin(); it != v_dest.end(); it++)
		std::cout << *it << std::endl;

	ft::vector<int> vm_src;
	vm_src.push_back(1);
	vm_src.push_back(2);
	vm_src.push_back(3);
	vm_src.push_back(4);

	ft::vector<int> vm_dest;
	vm_dest = vm_src;
	//for (ft::vector<int>::iterator it = vm_dest.begin(); it != vm_dest.end(); it++)
	//	std::cout << *it << std::endl;
	
	std::cout << "----------range insert----------" << std::endl;

	std::list<int>l_in;
	l_in.push_back(-555);
	l_in.push_back(444);
	l_in.push_back(-777);
	l_in.push_back(777);
	std::vector<int> v_rinsert;
	ft::vector<int> vm_rinsert;
	
	v_rinsert.push_back(1); 
	v_rinsert.push_back(2); 
	v_rinsert.push_back(3); 
	v_rinsert.push_back(4); 

	vm_rinsert.push_back(1); 
	vm_rinsert.push_back(2); 
	vm_rinsert.push_back(3); 
	vm_rinsert.push_back(4); 
	
	std::cout << "true----------" << std::endl;
	std::cout << "before : " << std::endl;
	for (std::vector<int>::iterator it = v_rinsert.begin(); it != v_rinsert.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "size : " << v_rinsert.size() << std::endl;
	std::cout << "capacity : " << v_rinsert.capacity() << std::endl;

	v_rinsert.insert(v_rinsert.begin() + 1, l_in.begin(), l_in.end());
	std::cout << "after : " << std::endl;

	for (std::vector<int>::iterator it = v_rinsert.begin(); it != v_rinsert.end(); it++)
		std::cout << *it << std::endl;
	
	std::cout << "size : " << v_rinsert.size() << std::endl;
	std::cout << "capacity : " << v_rinsert.capacity() << std::endl;

	std::cout << "mine----------" << std::endl;
	std::cout << "before :" << std::endl;
	std::cout << "size : " << vm_rinsert.size() << std::endl;
	std::cout << "capacity : " << vm_rinsert.capacity() << std::endl;

	for (ft::vector<int>::iterator mit = vm_rinsert.begin();
			mit != vm_rinsert.end(); mit++)
		std::cout << *mit << std::endl;

	vm_rinsert.insert(vm_rinsert.begin() + 1, l_in.begin(), l_in.end());
	std::cout << "after : " << std::endl;

	for (ft::vector<int>::iterator mit = vm_rinsert.begin();
			mit != vm_rinsert.end(); mit++)
		std::cout << *mit << std::endl;
	std::cout << "size : " << vm_rinsert.size() << std::endl;
	std::cout << "capacity : " << vm_rinsert.capacity() << std::endl;

	return 0;
}

