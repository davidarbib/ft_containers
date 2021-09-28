/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:22:14 by darbib            #+#    #+#             */
/*   Updated: 2021/09/28 20:28:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"

namespace ft
{
	template <class T>
	struct rbnode
	{
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
		T						value;
		bool					red;
	};
}

#endif
