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
   ~Record(){
      Burn();
   }
   void MergeAndInsert();
   void FindByName();
   void AreUSure(); // Pergunta antes de destruir o registro
private:
   DynamicStruct* Search(string elementToFind) const;
   void Burn();
};

int Menu();
void ClearWindow();
void Pause();

#endif
