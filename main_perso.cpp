#include <vector.hpp>
#include <vector>

int main()
{
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
	
	std::cout << std::endl << "----------------------------------------------";
	std::cout << std::endl;


	return 0;
}
