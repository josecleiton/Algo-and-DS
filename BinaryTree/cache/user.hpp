/*
 * =====================================================================================
 *
 *       Filename:  user.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/16/2020 07:06:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  José Cleiton Borges Correia (JCBC), jcleitonbc@gmail.com
 *   Organization:  UNEB
 *
 * =====================================================================================
 */

#include <string>

class User {
  private:
   std::string cpf;

  public:
   std::string name;
   int age;

   User(const std::string&, const std::string&, int = -1);

   inline const std::string& getCpf(void) const { return cpf; }

   inline std::string_view firstName(void) const {
      const auto space = name.find_first_of(' ');
      if (space != std::string::npos) {
         return std::string_view(name.c_str(), name.find_first_of(' '));
      }
      return name;
   }
   inline std::string_view lastName(void) const {
      const auto space = name.find_first_of(' ');
      if (space != std::string::npos) {
         return std::string_view(name.c_str() + space + 1,
                                 name.size() - (space + 1));
      }
      return std::string_view(name.c_str() + name.size());
   }

   friend std::ostream& operator<<(std::ostream&, const User&);
};
