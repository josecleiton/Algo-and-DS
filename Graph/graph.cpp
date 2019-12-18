#include "graph.hpp"
using namespace graph;

void test_undirected(void){
    char input[80][80] = {
        "Tokyo", // 0
        "Dallas", // 1 
        "Hong Kong", // 2
        "Aspen", // 3
        "Los Angeles" // 4
    };
    undirected_graph<string> ug;
    cout << "UNDIRECTED GRAPH" << endl << endl;
    ug.addEdge(input[0], input[1]);
    ug.addEdge(input[0], input[2]);
    ug.addEdge(input[1], input[3]);
    ug.addEdge(input[1], input[2]);
    ug.addEdge(input[1], input[4]);
    ug.addEdge(input[2], input[4]);

    ug.dfs(input[0]);
    cout << endl;
    ug.bfs(input[0]);
    cout << endl;
    ug.print();
}

void test_weighted(void){
    char input[80][80] = {
        "A", // 0
        "B", // 1 
        "C", // 2
        "D", // 3
        "E", // 4
        "F"
    };
    
    undirected_weigthed_graph<string> uwg;
    cout << "UNDIRECTED WEIGHTED GRAPH" << endl << endl;
    uwg.addEdge(input[0], input[1], 4); // A -> B
    uwg.addEdge(input[0], input[2], 2); // A -> C
    uwg.addEdge(input[1], input[4], 3); // B -> E 
    uwg.addEdge(input[2], input[3], 2); // C -> D
    uwg.addEdge(input[2], input[5], 4); // C -> F
    uwg.addEdge(input[3], input[5], 1); // D -> F
    uwg.addEdge(input[5], input[4], 1); // F -> E
    uwg.addEdge(input[4], input[3], 3); // E -> D

    uwg.print();
    cout << endl << endl;

    cout << "Shortest path " << input[0] << " -> " << input[5] << endl;
    auto path = uwg.dijkstra(input[0], input[4]); // A -> F
    for(auto v: path) cout << v << " -> ";
    cout << "/" << endl;
    cout << endl;


    uwg.dfs("D");
    cout << endl;
    uwg.bfs("D");
}

int main(void){
    test_undirected();
    cout << endl << endl;
    test_weighted();
    return 0;
}