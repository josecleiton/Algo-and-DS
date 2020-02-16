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

#include <chrono>
#include <iostream>
#include <thread>

#include "cache.hpp"
#include "user.hpp"

#define MAX 2
#define GAP 3 // max difference (in seconds) between now and oldest object in cache

inline void sleep() {
   std::cout << "Waiting for 2 seconds\n";
   std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
   Cache<User> c(MAX, GAP);
   c.push(User("01203132", "José Cleiton"), "teste2");
   std::cout << "Pushed User in " << std::time(nullptr) << "\n";
   sleep();
   c.push(User("01203132", "Maria José"));
   std::cout << "Pushed User in " << std::time(nullptr) << "\n";
   sleep();
   c.push(User("01203132", "Ana Claudia"));
   std::cout << "Pushed User in " << std::time(nullptr) << "\n";
   sleep();
   c.push(User("01203132", "Ana Maria"));
   std::cout << "Pushed User in " << std::time(nullptr) << "\n";
   sleep();
   c.push(User("01203132", "Ana Rita"), "teste");
   std::cout << "Pushed User in " << std::time(nullptr) << "\n";
   sleep();
   c.push(User("01203132", "Ana"), "teste1");
   std::cout << "Pushed User in " << std::time(nullptr) << "\n\n"
             << "KEY 'test': " << *c.get("teste") << '\n'
             << "KEY 'test1': " << *c.get("teste1") << '\n'
             << "KEY 'test2': " << c.get("cleiton") << '\n'
             << "Quantity of objects managed by caching system: " << c.size()
             << '\n';
   return 0;
}

