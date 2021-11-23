#include <iostream>
#include "type_traits.hpp"
//#include <type_traits>

void foo(double a, double b)
{
	std::cout << "specific" << std::endl;
}

//template <typename T, typename ft::enable_if<std::is_unsigned<T>::value>::type>
//void foo(T a, typename ft::enable_if<std::is_unsigned<T>::value>::type = 0)
/*
   void foo(T a, typename ft::enable_if<true>::type = 0)
   {
   std::cout << "unsigned int" << std::endl;
   }
   */

template <typename T>
//void foo(T a, T b,
//		typename ft::enable_if<!ft::is_same<T, int>::value>::type* = 0)
//void foo(T a, T b)
void foo(T a, T b,
		typename ft::enable_if<!ft::is_integral<T>::value>::type* = 0)
{
	std::cout << "template" << std::endl;
}

int main()
{
	foo(42, 3);
//	foo("ok", "kfjd");
	return 0;
}
