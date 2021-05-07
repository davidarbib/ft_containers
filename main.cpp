/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:17:19 by darbib            #+#    #+#             */
/*   Updated: 2021/05/07 15:57:25 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int main()
{
	std::vector<int> *v = new std::vector<int>(33);
	std::cout << v->max_size() << std::endl;
	std::cout << v->capacity() << std::endl;
	std::cout << v->size() << std::endl;
	delete v;
}
