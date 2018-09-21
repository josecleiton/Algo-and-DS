#ifndef DYNAMIC
#define DYNAMIC

#define LIB
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
   friend bool operator==(const DynamicStruct &This, const DynamicStruct &Other);
   private:
     void Remove();
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
   void RemoveByName();
private:
   DynamicStruct* Search(string elementToFind) const;
   void Burn();
};

int Menu();
void ClearWindow();
void Pause();

#endif
