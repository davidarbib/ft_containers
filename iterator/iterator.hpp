/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:40:13 by darbib            #+#    #+#             */
/*   Updated: 2021/05/10 17:43:56 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	struct input_iterator_tag {};	
	struct output_iterator_tag {};	
	struct forward_iterator_tag : input_iterator_tag, output_iterator_tag {};
	struct bidirectionnal_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectionnal_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, 
			 class Pointer = T*, class Reference = T&> class iterator;	
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	public Random_Access_Iterator
	: public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			Random_Access_Iterator();
			Random_Access_Iterator(ft::Random_Access_Iterator const &src);
			virtual ~Random_Access_Iterator_tag();
			Random_Access_Iterator &operator=(ft::Random_Access_Iterator const &src);

	}
}
