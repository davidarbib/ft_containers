#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"

namespace ft
{
	template <class Key, class T>
	struct rbnode
	{
		ft::pair<const Key, T>	pair;
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
		bool					red;
	};
}

#endif
