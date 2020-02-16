/*
 * =====================================================================================
 *
 *       Filename:  user.cpp
 *
 *    Description: j
 *
 *        Version:  1.0
 *        Created:  02/16/2020 07:16:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  José Cleiton Borges Correia (JCBC), jcleitonbc@gmail.com
 *   Organization:  UNEB
 *
 * =====================================================================================
 */

#include "user.hpp"


User::User(const std::string& _cpf, const std::string& _name, int _age): cpf(_cpf), name(_name), age(_age) {
   puts("Chamado");
}

