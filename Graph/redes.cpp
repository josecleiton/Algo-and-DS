#include <cctype>
#include <cstring>
#include <set>
#include <stack>
#include <unordered_map>

#include "graph.hpp"
void backtrackPath(const map<string, string> &pattern, const string node) {
  if (node.size()) {
    backtrackPath(pattern, pattern.at(node));
    cout << node << " -> ";
  }
};

int main(int argc, char *argv[]) {
  graph::undirected_weigthed_graph<string> graph;
  set<string> citySet{"ARACAJU", "SALVADOR", "MACEIO", "JUAZEIRO",
                      "FEIRA",   "MADRE",    "NATAL",  "CIDADENOVA"};

  graph.addEdge("ARACAJU", "MACEIO", 30);
  graph.addEdge("ARACAJU", "JUAZEIRO", 10);
  graph.addEdge("ARACAJU", "SALVADOR", 100);
  graph.addEdge("ARACAJU", "FEIRA", 110);
  graph.addEdge("ARACAJU", "MADRE", 150);
  graph.addEdge("ARACAJU", "NATAL", 300);

  graph.addEdge("MACEIO", "JUAZEIRO", 10);
  graph.addEdge("MACEIO", "SALVADOR", 20);
  graph.addEdge("MACEIO", "FEIRA", 45);
  graph.addEdge("MACEIO", "MADRE", 35);
  graph.addEdge("MACEIO", "NATAL", 200);

  graph.addEdge("SALVADOR", "FEIRA", 2);
  graph.addEdge("SALVADOR", "MADRE", 5);
  graph.addEdge("SALVADOR", "JUAZEIRO", 150);
  graph.addEdge("SALVADOR", "NATAL", 400);

  graph.addEdge("FEIRA", "MADRE", 6);
  graph.addEdge("FEIRA", "NATAL", 500);
  graph.addEdge("FEIRA", "ARACAJU", 200);
  graph.addEdge("FEIRA", "CIDADENOVA", 4);

  graph.print();
  cout << endl;

  cout << "Insira o par de interesse (CIDADE/LOCAL): " << endl;

  string ponto1, ponto2;
  cin >> ponto1 >> ponto2;

  auto toup = [](string &s) {
    for (auto &c : s)
      c = toupper(c);
  };
  toup(ponto1);
  toup(ponto2);

  if (!(citySet.count(ponto1) && citySet.count(ponto2))) {
    cout << endl << "Input inválido" << endl;
    return 1;
  }

  cout << endl
       << "A menor distancia entre {" << ponto1 << ", " << ponto2
       << "}: " << endl;
  if (argc > 1 && !strcmp(argv[1], "bellman")) {
    cout << "\nUSING BELLMAN-FORD ALGORITHM O(V*E):\n\n";
    const auto bellman = graph.bellmanFord(ponto1);
    cout << "distances from " << ponto1 << ":\n";
    for (const auto &distances : bellman.first) {
      cout << distances.first << " -> " << distances.second << '\n';
    }
    cout << "\nback tracking the minimium path:\n";
    {
      const auto pattern = bellman.second;
      backtrackPath(pattern, ponto2);
      cout << " /\n";
    }
  } else {
    cout << "\nUSING DIJKSTRA ALGORITHM O((E+V)*logV):\n\n";
    const auto shortestPath = graph.dijkstra(ponto1, ponto2);
    backtrackPath(shortestPath, ponto2);
    cout << " /\n";
  }
}
