#include <iostream>
#include <type_traits>
#include "type_traits.hpp"

int main()
{
	std::cout << "---------------------integral_constant-----------------------" << std::endl;

	std::cout << "true --------------------------------" << std::endl;
	std::cout << std::integral_constant<int, 42>::value << std::endl;
	std::cout << "mine --------------------------------" << std::endl;
	std::cout << ft::integral_constant<int, 42>::value << std::endl;

	std::cout << "---------------------is_integral-----------------------" << std::endl;

	std::cout << "true --------------------------------" << std::endl;
	std::cout << std::is_integral<int>::value << std::endl;
	std::cout << std::is_integral<char>::value << std::endl;
	std::cout << std::is_integral<long>::value << std::endl;
	std::cout << std::is_integral<long long>::value << std::endl;
	std::cout << std::is_integral<bool>::value << std::endl;
	std::cout << std::is_integral<short>::value << std::endl;
	std::cout << std::is_integral<char16_t>::value << std::endl;
	std::cout << std::is_integral<char32_t>::value << std::endl;
	std::cout << std::is_integral<wchar_t>::value << std::endl;
	std::cout << std::is_integral<std::string>::value << std::endl;

	std::cout << "mine --------------------------------" << std::endl;
	std::cout << ft::is_integral<int>::value << std::endl;
	std::cout << ft::is_integral<char>::value << std::endl;
	std::cout << ft::is_integral<long>::value << std::endl;
	std::cout << ft::is_integral<long long>::value << std::endl;
	std::cout << ft::is_integral<bool>::value << std::endl;
	std::cout << ft::is_integral<short>::value << std::endl;
	std::cout << ft::is_integral<char16_t>::value << std::endl;
	std::cout << ft::is_integral<char32_t>::value << std::endl;
	std::cout << ft::is_integral<wchar_t>::value << std::endl;
	std::cout << ft::is_integral<std::string>::value << std::endl;

	return 0;
}
