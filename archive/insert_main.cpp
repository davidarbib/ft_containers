/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/11/17 17:57:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"
#include "vector.hpp"
#include <vector>

#ifndef TESTED_NS
# define TESTED_NS std
#endif

using namespace TESTED_NS;

template <class T>
void	print(vector<vector<T> >& lst)
{
	for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			cout << *it2 << ' ';
		cout << '\n';
	}
}

template <class T>
void	print(vector<T>& lst)
{
	for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << *it << ' ';
	cout << '\n';
}


int main ()
{
  vector<int> myvector (3,100);
  vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  cout << "before 300 insertion myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    cout << ' ' << *it;
  cout << '\n';

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  cout << "before range insertion myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    cout << ' ' << *it;
  cout << '\n';

  it = myvector.begin();

  vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  cout << "before array insertion myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    cout << ' ' << *it;
  cout << '\n';
  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    cout << ' ' << *it;
  cout << '\n';

  return 0;
}
