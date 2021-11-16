#ifndef STACK_HPP
# define STACK_HPP
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class stack {
			public:
				typedef typename Container::value_type	value_type;
				typedef typename Container::size_type	size_type;
				typedef          Container				container_type;

			protected:
					Container _base_c;

			public:
					stack(const Container& c = Container())
					: _base_c(c)
					{ }

					bool
					empty() const
					{ return _base_c.empty(); }

					size_type
					size()  const
					{ return _base_c.size(); }

					value_type&
					top()
					{ return _base_c.back(); }

					const value_type&
					top() const
					{ return _base_c.back(); }

					void
					push(const value_type& x)
					{ _base_c.push_back(x); }

					void
					pop()
					{ _base_c.pop_back(); }

					friend
					bool operator==(const stack<T, Container>& x,
									const stack<T, Container>& y)
					{ return x._base_c == y._base_c; }

					friend
					bool operator<(const stack<T, Container>& x,
									const stack<T, Container>& y)
					{ return x._base_c < y._base_c; }

		};
		template <class T, class Container>
		bool operator!=(const stack<T, Container>& x,
			 			const stack<T, Container>& y)
		{ return !(x == y); }

		template <class T, class Container>
		bool operator> (const stack<T, Container>& x,
						const stack<T, Container>& y)
		{ return y < x; }
		template <class T, class Container>
		bool operator>=(const stack<T, Container>& x,
						const stack<T, Container>& y)
		{ return x == y || x > y; }
		template <class T, class Container>
		bool operator<=(const stack<T, Container>& x,
						const stack<T, Container>& y)
		{ return x == y || x < y; }
}
#endif
