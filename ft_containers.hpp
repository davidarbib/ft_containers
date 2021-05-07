/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:44:59 by darbib            #+#    #+#             */
/*   Updated: 2021/05/06 13:56:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> > class vector;  
	template <class T> class list;  
	template <class T> class map;  
	template <class T> class stack;  
	template <class T> class queue;  
}
