#ifndef DYNAMIC
#define DYNAMIC
#include <iostream>
#include <list>
#include <string>
#include <cstring>
using namespace std;

class DynamicStruct{
   friend class Record;
   string Name{};
   string Type{};
   void* Key{};

   ~DynamicStruct(){
      delete this->Key;
   }

   void Insert();
   friend ostream &operator <<(ostream &out, const DynamicStruct &Other);
};

class Record{
   list<DynamicStruct*> Values;

public:
   void MergeAndInsert();
   void FindByName();
private:
   DynamicStruct* Search(string elementToFind) const;
};

int Menu();
void ClearWindow();
void Pause();

#endif
