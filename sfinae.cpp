#include <string>
#include <iostream>

void f(std::string s) // int can't be convert into a string.
{ std::cout << "string version" << std::endl; }
/*
void f(double d) // int can be implicitly convert into a double, so this version could be selected, but...
{ std::cout << "double version" << std::endl; }
void f(int i) // ... this version using the type int directly is even more close!
{ std::cout << "int version" << std::endl; }

std::string f(...) // Variadic functions are so "untyped" that... 
{ std::cout << "variadic version" << std::endl; return NULL; }
template <typename T> std::string f(const T& t) // ...this templated function got the precedence!
{ std::cout << "template version" << std::endl; return NULL; }
*/

/*
 The compiler will try this overload since it's less generic than the variadic.
 T will be replace by int which gives us void f(const int& t, int::iterator* b = nullptr);
 int doesn't have an iterator sub-type, but the compiler doesn't throw a bunch of errors.
 It simply tries the next overload.
template <typename T> void f(const T& t, typename T::iterator* it = nullptr)
{
	std::cout << "template with iterator version" << std::endl;
}

// The sink-hole.
void f(...)
{
	std::cout << "sink hole" << std::endl;
}
*/

/*
// The compiler will be really unhappy when it will later discover the call to hahahaICrash. 
template <typename T> void f(T t) { t.hahahaICrash(); }
void f(...) { } // The sink-hole wasn't even considered.

*/


/*
int main()
{
	f(1);
	return 0;
}
	*/

/*
typedef char type_test[42];
type_test& f();

int main()
{
	// In the following lines f won't even be truly called but we can still access to the size of its return type.
	// Thanks to the "fake evaluation" of the sizeof operator.
	char arrayTest[sizeof(f())];
	std::cout << sizeof(f()) << std::endl; // Output 42.
	return 0;
}
*/

typedef char yes; // Size: 1 byte.
typedef yes no[2]; // Size: 2 bytes.

// Two functions using our type with different size.
yes& f1();
no& f2();

int main()
{
std::cout << (sizeof(f1()) == sizeof(f2())) << std::endl; // Output 0.
std::cout << (sizeof(f1()) == sizeof(f1())) << std::endl; // Output 1.
return 0;
}
