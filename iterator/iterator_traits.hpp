namespace ft
{
	template <typename T> 
	struct iterator_traits
	{
		typedef typename T::value_type       	value_type;
		typedef typename T::pointer          	pointer;
		typedef typename T::reference        	reference;
		typedef typename T::difference_type  	difference_type;
		typedef typename T::iterator_category	iterator_category;
	};

	template <typename T> 
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t						difference_type;
		typedef random_access_iterator_tag		iterator_category;
	};
}
