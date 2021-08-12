#include <vector.hpp>
#include <vector>

int main()
{
	std::vector<int> true_v = std::vector<int>(3, 42);
	ft::vector<int> mine_v = ft::vector<int>(3, 42);
	std::cout << "true capacity : " << true_v.capacity();
	std::cout << "true size : " << true_v.size();
	std::cout << "mine capacity : " << mine_v.capacity();
	std::cout << "mine size : " << mine_v.size();

	return 0;
}
