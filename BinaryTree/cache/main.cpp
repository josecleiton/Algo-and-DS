/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/16/2020 07:15:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  José Cleiton Borges Correia (JCBC), jcleitonbc@gmail.com
 *   Organization:  UNEB
 *
 * =====================================================================================
 */

#include <iostream>

#include "cache.hpp"
#include "user.hpp"

#define MAX 300

int main() {
   Cache<User> c(2, 3);
   c.push(User("01203132", "José Cleiton"));
   c.push(User("01203132", "Maria José"));
   c.push(User("01203132", "Ana Claudia"));
   c.push(User("01203132", "Ana Maria"));
   c.push(User("01203132", "Ana Rita"));
   return 0;
}

