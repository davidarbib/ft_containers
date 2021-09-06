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

	template <typename T, T v>
	struct integral_constant
	{
		typedef T							value_type;
		typedef ft::integral_constant<T,v>	type;

		static value_type const value = v;
	};
	
	template <>
	struct integral_constant<bool, true>
	{
		typedef ft::integral_constant<bool, true> true_type;
	};

	template <>
	struct integral_constant<bool, false>
	{
		typedef ft::integral_constant<bool, false> false_type;
	};

	template <typename T>
	struct is_integral
	{
		static bool const value = false;
	};

	template <>
	struct is_integral<bool> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<char> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<char16_t> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<char32_t> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<wchar_t> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<short> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<int> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<long> 
	{
		static bool const value = true;
	};

	template <>
	struct is_integral<long long> 
	{
		static bool const value = true;
	};

	template <typename T>
	struct is_const
	{
		static bool const value = false;
	};

	template <typename T>
	struct is_const<const T>
	{
		static bool const value = true;
	};

	template <bool B, typename T, typename F>
	struct conditionnal
	{
	};

	template <typename T, typename F>
	struct conditionnal<true, T, F>
	{
		typedef T type;
	};

	template <typename T, typename F>
	struct conditionnal<false, T, F>
	{
		typedef F type;
	};
}
