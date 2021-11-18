/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:22:14 by darbib            #+#    #+#             */
/*   Updated: 2021/11/18 18:32:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
# define RBNODE_HPP

#include "pair.hpp"

//TODO apple padding, put bool to end if linux
#ifdef __APPLE__
namespace ft
{
	template <class T>
	struct rbnode
	{
		T						value;
		bool					red;
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
	};
}

#else
namespace ft
{
	template <class T>
	struct rbnode
	{
		T						value;
		struct rbnode			*left_child;
		struct rbnode			*right_child;
		struct rbnode			*parent;
		bool					red;
	};
}


#endif
