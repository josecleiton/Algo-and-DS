#ifndef DYNAMIC
#define DYNAMIC

#include <iostream>
#include <list>
#include <string>
#include <cstring>
using namespace std;

class Field{
   friend class Record;
   string Name{};
   string Type{};
   void* Key{};

   ~Field();

   void Insert();
   friend ostream &operator <<(ostream &out, const Field &Other);
   friend bool operator==(const Field &This, const Field &Other);
   private:
     void Remove();
};

class Record{
   list<Field*> Values;
public:
   ~Record(){
      Burn();
   }
   void MergeAndInsert();
   void FindByName();
   void AreUSure(); // Pergunta antes de destruir o registro
   void RemoveByName();
   void FindAll();
private:
   Field* Search(string elementToFind) const;
   void Burn();
};

int Menu();
void ClearWindow();
void Pause();

#endif
