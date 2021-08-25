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
		typedef T false_value;
	};

	template <typename T>
	struct is_same<T, T>
	{
		typedef T true_value;
	};

	/*
	template <typename T>
	struct is_integral
	{
		static bool value;
		
		
		

	}
	*/
}
