#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		pair()
		: first(T1()), second(T2())
		{ }

		pair(const T1& x, const T2& y)
		: first(x), second(y)
		{ }

		template<class U, class V>
		pair(const pair<U, V> &p)
		: first(p.first), second(p.second)
		{ }
		
		virtual
		~pair(void)
		{
			std::cout << "pair " << this << " destruction : " << std::endl;
			//this->first.~T1();
			std::cout << "key destroyed" << std::endl;
			//this->second.~T2();
			std::cout << "mapped value destroyed" << std::endl;
		}

		pair&
		operator=(const pair& pr)
		{
			this->first.~T1();
			this->second.~T2();
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
	};

	template <class T1, class T2>
	bool
	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool
	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool
	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool
	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool
	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return rhs < lhs; }

	template <class T1, class T2>
	bool
	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs < rhs); }

	template <class T1, class T2>
  	pair<T1, T2>
	make_pair(const T1& x, const T2& y)
	{ return pair<T1, T2>(x, y); }
}

#endif
