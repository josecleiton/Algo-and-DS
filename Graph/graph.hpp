#ifndef _GRAPH_HPP
#define _GRAPH_HPP
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "../BinaryTree/MinHeap.hpp"
using namespace std;

namespace graph {

template <typename ValueType> class Graph {
protected:
  map<ValueType, deque<ValueType>> adj_list;
  void addVertex(ValueType v) { adj_list[v]; }
  virtual void popVertex(ValueType v) {}
  virtual void addEdge(ValueType v1, ValueType v2) {}

public:
  virtual void dfs(ValueType key) {}
  virtual void bfs(ValueType key) {}

  bool isVertex(ValueType v) { return adj_list.find(v) != adj_list.end(); }

  bool isEmpty(void) { return adj_list.empty(); }

  size_t size(void) { return adj_list.size(); }

public:
  void print(void) {
    cout << "Printing the Adjacency List: " << endl;
    for (auto vertex : Graph<ValueType>::adj_list) {
      cout << vertex.first << ": ";
      for (auto edge : vertex.second)
        cout << edge << " -> ";
      cout << "/" << endl;
    }
  }
};

template <typename ValueType> class undirected_graph : public Graph<ValueType> {
protected:
  // TRAVERSAL UTILS
  deque<ValueType> results;
  map<ValueType, bool> visited;

public:
  void popVertex(ValueType v) {
    Graph<ValueType>::adj_list.erase(v);
    for (auto &vertex : Graph<ValueType>::adj_list) {
      auto toFind = find(vertex.second.begin(), vertex.second.end(), v);
      if (toFind != vertex.second.end())
        vertex.second.erase(toFind);
    }
  }

  void addEdge(ValueType v1, ValueType v2) {
    Graph<ValueType>::adj_list[v1].push_back(v2);
    Graph<ValueType>::adj_list[v2].push_back(v1);
  }

  void popEdge(ValueType v1, ValueType v2) {
    if (!this->isVertex(v1) or !this->isVertex(v2))
      return;
    auto find_in_v1 = find(Graph<ValueType>::adj_list[v1].begin(),
                           Graph<ValueType>::adj_list[v1].end(), v2);
    auto find_in_v2 = find(Graph<ValueType>::adj_list[v2].begin(),
                           Graph<ValueType>::adj_list[v2].end(), v1);
    if (find_in_v1 != Graph<ValueType>::adj_list[v1].end() and
        find_in_v2 != Graph<ValueType>::adj_list[v2].end()) {
      Graph<ValueType>::adj_list[v1].erase(find_in_v1);
      Graph<ValueType>::adj_list[v2].erase(find_in_v2);
    }
  }

  void dfsUtil(ValueType &root) {
    results.push_back(root);
    visited[root] = true;
    for (auto &nbh : Graph<ValueType>::adj_list[root])
      if (!visited[nbh])
        dfsUtil(nbh);
  }

  void bfsUtil(ValueType &root) {
    queue<ValueType> auxQueue;
    auxQueue.push(root);
    visited[root] = true;
    ValueType currentVertex;
    while (!auxQueue.empty()) {
      currentVertex = auxQueue.front();
      auxQueue.pop();
      results.push_back(currentVertex);
      for (auto &nbh : Graph<ValueType>::adj_list[currentVertex]) {
        if (!visited[nbh]) {
          auxQueue.push(nbh);
          visited[nbh] = true;
        }
      }
    }
  }

public:
  void dfs(ValueType key) {
    if (Graph<ValueType>::adj_list.find(key) ==
        Graph<ValueType>::adj_list.end())
      return;
    visited.clear();
    results.clear();
    cout << "DFS (root: " << key << ")" << endl;
    dfsUtil(key);
    for (auto item : results)
      cout << item << " -> ";
    cout << "/" << endl;
  }

  void bfs(ValueType key) {
    if (Graph<ValueType>::adj_list.find(key) ==
        Graph<ValueType>::adj_list.end())
      return;
    visited.clear();
    results.clear();
    cout << "BFS (root: " << key << ")" << endl;
    bfsUtil(key);
    for (auto item : results)
      cout << item << " -> ";
    cout << "/" << endl;
  }

  // void dikjstra(ValueType v1, ValueType v2)
};

template <typename ValueType> class weighted_graph {
public:
  struct Node {
    ValueType data;
    int weight;
    Node(ValueType _data = ValueType(), int _w = 0) : data(_data), weight(_w) {}
  };

public:
  void addVertex(ValueType v) { adj_list[v]; }
  virtual void popVertex(ValueType v) {}
  virtual void addEdge(ValueType v1, ValueType v2, int weight = 0) {}

  void print(void) {
    cout << "Printing the Adjacency List: " << endl;
    for (auto vertex : adj_list) {
      cout << vertex.first << ": ";
      for (auto edge : vertex.second)
        cout << "{" << edge.data << "+" << edge.weight << "} ";
      cout << endl;
    }
  }

protected:
  map<ValueType, deque<Node>> adj_list;
};

template <typename ValueType>
class undirected_weigthed_graph : public weighted_graph<ValueType> {
protected:
  deque<ValueType> results;
  map<ValueType, bool> visited;

public:
  void popVertex(ValueType v) {
    weighted_graph<ValueType>::adj_list.erase(v);
    auto needle = typename weighted_graph<ValueType>::Node(v);
    for (auto &vertex : weighted_graph<ValueType>::adj_list) {
      int i = 0;
      for (auto &edge : vertex.second) {
        if (edge.data != v)
          i++;
        else {
          vertex.second.erase(vertex.second.begin() + i);
          break;
        }
      }
    }
  }
  void addEdge(ValueType v1, ValueType v2, int weight = 0) {
    weighted_graph<ValueType>::adj_list[v1].push_back(
        typename weighted_graph<ValueType>::Node(v2, weight));
    weighted_graph<ValueType>::adj_list[v2].push_back(
        typename weighted_graph<ValueType>::Node(v1, weight));
  }

  void popEdge(ValueType v1, ValueType v2) {
    int i = 0;
    bool exists = false;
    for (auto &edge : weighted_graph<ValueType>::adj_list[v1]) {
      if (edge.data == v2) {
        exists = true;
        weighted_graph<ValueType>::adj_list[v1].erase(
            weighted_graph<ValueType>::adj_list[v1].begin() + i);
        break;
      }
      i++;
    }
    if (exists) {
      i = 0;
      for (auto &edge : weighted_graph<ValueType>::adj_list[v2]) {
        if (edge.data == v1) {
          weighted_graph<ValueType>::adj_list[v2].erase(
              weighted_graph<ValueType>::adj_list[v2].begin() + i);
          break;
        }
        i++;
      }
    }
  }

  // O((E + V)*log(V))
  map<ValueType, ValueType> dijkstra(ValueType start, ValueType finish) {
    using pvt = pair<int, ValueType>;
    // heap auxiliar
    priority_queue<pvt, vector<pvt>, greater<pvt>> priorityq;
    // distances (inicialmente tudo infinito, menos source)
    unordered_map<ValueType, int> distances;
    // mantenha a origem de cada nó
    map<ValueType, ValueType> previous;
    // vetor dinamico para reconstruir o caminho minimo resultante
    for (auto vertex : weighted_graph<ValueType>::adj_list) {
      previous[vertex.first];
      distances[vertex.first] = (vertex.first != start) ? INT32_MAX : 0;
      priorityq.push(make_pair(distances[vertex.first], vertex.first));
    }
    while (!priorityq.empty()) {
      auto smallest = priorityq.top();
      priorityq.pop();
      if (smallest.second == finish) {
        /* while (previous[smallest.second] != ValueType()) { */
        /*    result.push_front(smallest.second); */
        /*    smallest.second = previous[smallest.second]; */
        /* } */
        /* result.push_front(smallest.second); */
        /* break; */
        return previous;
      }
      for (auto &nbh : weighted_graph<ValueType>::adj_list[smallest.second]) {
        int candidate = distances[smallest.second] + nbh.weight;
        if (candidate < distances[nbh.data]) {
          distances[nbh.data] = candidate;
          previous[nbh.data] = smallest.second;
          priorityq.push(make_pair(candidate, nbh.data));
        }
      }
    }
    return {};
  }
  pair<map<ValueType, int>, map<ValueType, ValueType>>
  bellmanFord(ValueType start) {
    map<ValueType, int> distances;
    map<ValueType, ValueType> previous;
    for (auto vertex : weighted_graph<ValueType>::adj_list) {
      previous[vertex.first];
      distances[vertex.first] = INT16_MAX;
    }
    distances[start] = 0;
    const size_t V = weighted_graph<ValueType>::adj_list.size();
    for (unsigned i = 0; i < V - 1; i++) {
      for (auto &node : weighted_graph<ValueType>::adj_list) {
        const ValueType u = node.first;
        for (auto &nbh : weighted_graph<ValueType>::adj_list[u]) {
          const ValueType v = nbh.data;
          const int possibleMinDist = nbh.weight + distances[u];
          if (possibleMinDist < distances[v]) {
            distances[v] = possibleMinDist;
            previous[v] = u;
          }
        }
      }
    }
    for (auto &node : weighted_graph<ValueType>::adj_list) {
      const ValueType u = node.first;
      for (auto &nbh : weighted_graph<ValueType>::adj_list[u]) {
        const ValueType v = nbh.data;
        const int possibleMinDist = nbh.weight + distances[u];
        if (possibleMinDist < distances[v]) {
          return {}; // negative weight cycle
        }
      }
    }
    return make_pair(distances, previous);
  }
  void bfs(ValueType key) {
    if (weighted_graph<ValueType>::adj_list.find(key) ==
        weighted_graph<ValueType>::adj_list.end())
      return;
    visited.clear();
    results.clear();
    cout << "BFS (root: " << key << ")" << endl;
    bfsUtil(key);
    for (auto v : results)
      cout << v << " -> ";
    cout << "/" << endl;
  }
  void dfs(ValueType key) {
    if (weighted_graph<ValueType>::adj_list.find(key) ==
        weighted_graph<ValueType>::adj_list.end())
      return;
    visited.clear();
    results.clear();
    cout << "DFS (root: " << key << ")" << endl;
    dfsUtil(key);
    for (auto v : results)
      cout << v << " -> ";
    cout << "/" << endl;
  }

protected:
  void dfsUtil(ValueType &root) {
    results.push_back(root);
    visited[root] = true;
    for (auto &nbh : weighted_graph<ValueType>::adj_list[root])
      if (!visited[nbh.data])
        dfsUtil(nbh.data);
  }

  void bfsUtil(ValueType &root) {
    queue<ValueType> auxQueue;
    auxQueue.push(root);
    visited[root] = true;
    ValueType currentVertex;
    while (!auxQueue.empty()) {
      currentVertex = auxQueue.front();
      auxQueue.pop();
      results.push_back(currentVertex);
      for (auto &nbh : weighted_graph<ValueType>::adj_list[currentVertex]) {
        if (!visited[nbh.data]) {
          auxQueue.push(nbh.data);
          visited[nbh.data] = true;
        }
      }
    }
  }
};

template <typename ValueType>
bool operator>(const pair<ValueType, int> &a, const pair<ValueType, int> &b) {
  return a.second < b.second;
}

} // namespace graph

#endif //_GRAPH_HPP
