#include "graph.hpp"
#include <cctype>
#include <unordered_map>

int main() {
   graph::undirected_weigthed_graph<string> graph;
   unordered_map<string, bool> tem {
      {"RECIFE", 1},
      {"SALVADOR", 1},
      {"MACEIO", 1},
      {"ARACAJU", 1},
      {"FEIRA", 1},
      {"MADRE", 1},
      {"NATAL", 1},
      {"CIDADENOVA", 1},
   };
   graph.addEdge("RECIFE", "MACEIO", 30);
   graph.addEdge("RECIFE", "ARACAJU", 10);
   graph.addEdge("RECIFE", "SALVADOR", 100);
   graph.addEdge("RECIFE", "FEIRA", 110);
   graph.addEdge("RECIFE", "MADRE", 150);
   graph.addEdge("RECIFE", "NATAL", 300);

   graph.addEdge("MACEIO", "ARACAJU", 10);
   graph.addEdge("MACEIO", "SALVADOR", 20);
   graph.addEdge("MACEIO", "FEIRA", 45);
   graph.addEdge("MACEIO", "MADRE", 35);
   graph.addEdge("MACEIO", "NATAL", 200);

   graph.addEdge("SALVADOR", "FEIRA", 2);
   graph.addEdge("SALVADOR", "MADRE", 5);
   graph.addEdge("SALVADOR", "ARACAJU", 150);
   graph.addEdge("SALVADOR", "NATAL", 400);

   graph.addEdge("FEIRA", "MADRE", 6);
   graph.addEdge("FEIRA", "NATAL", 500);
   graph.addEdge("FEIRA", "ARACAJU", 200);
   graph.addEdge("FEIRA", "CIDADENOVA", 4);

   graph.addEdge("ARACAJU", "MADRE", 220);
   graph.addEdge("ARACAJU", "NATAL", 300);

   graph.print();
   cout << endl;

   cout << "Insira o par de interesse (CIDADE/LOCAL): " << endl;
   string ponto1, ponto2;
   cin >> ponto1 >> ponto2;
   auto toup = [](string& s) {
      for(auto& c: s)
         c = toupper(c);
   };
   toup(ponto1);
   toup(ponto2);
   if(tem[ponto1] && tem[ponto2]) {
      cout << endl << "A menor distancia entre {" << ponto1 << ", " << ponto2 << "}: " << endl;
      auto shortestPath = graph.dijkstra(ponto1, ponto2);
      for(const auto e: shortestPath) cout << e << " -> ";
      cout << "/" << endl;
   } else {
      cout << endl << "Input inválido" << endl;
      return 1;
   }
   return 0;
}
