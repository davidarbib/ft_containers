/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:40:13 by darbib            #+#    #+#             */
/*   Updated: 2021/05/11 15:07:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};	
	struct output_iterator_tag {};	
	struct forward_iterator_tag : input_iterator_tag, output_iterator_tag {};
	struct bidirectionnal_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectionnal_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, 
			 class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iter> 
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <class T>
	class Random_Access_Iterator
	: public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			Random_Access_Iterator();
			Random_Access_Iterator(Random_Access_Iterator const &src);
			virtual ~Random_Access_Iterator();
			Random_Access_Iterator &operator=(Random_Access_Iterator const &src);

			//typename ft::iterator<random_access_iterator_tag, T>::reference	operator*(void) const
			typename ft::iterator_traits<::reference	operator*(void) const
				{ return static_cast<reference>(this->_current_ptr); }

			pointer		operator->(void) const
				{ return this->_current_ptr; }

		protected :
			pointer		_current_ptr;


	};
}
