#include <vector.hpp>
#include <vector>

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
	return 0;
}
