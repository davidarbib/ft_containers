#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"

namespace ft
{
	template <class Pair>
	struct rbnode
	{
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
		Pair					pair;
		bool					red;
		int						nb;
	};
}

#endif
