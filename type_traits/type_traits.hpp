namespace ft
{
	template <bool, typename T = void>
	struct enable_if
	{ };

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T, typename U>
	struct is_same
	{
		static bool const value = false;
	};

	template <typename T>
	struct is_same<T, T>
	{
		static bool const value = true;
	};

	template <typename T>
	struct is_integral : public ft::is_same<T, int>
	{
	};
	/*
	template <typename T>
	struct is_integral
	{
		static bool value;
		
		
		

	}
	*/
}
