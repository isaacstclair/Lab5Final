#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <stack>
#include <map>
#include "Rule.h"


class Graph {

private:
    std::vector<Rule> Rules;
    std::map<int, std::set<int>> adjacencyList;
    std::vector<bool> visited;
    std::stack<int> topologicalSort;
    std::vector<int> postorder;
    std::vector<std::vector<int>> postorderforest;
    std::vector<int> searchtree;
public:
    Graph(std::vector<Rule> Rules);
    ~Graph();
    void AddEdge(int from, int to);
    std::vector<int> dfsPostOrder(int vertex);
    std::vector<int> dfsSearchTree(int vertex);
    std::vector<std::vector<int>> dfsForestPostOrder();
    std::vector<std::set<int>> dfsForestSCC(std::vector<int> postorder);
    void PrintAdjList();
    std::vector<int> GetReversePostOrder(std::vector<int> normalorder);
    bool HasItself(int node);

};


#endif //GRAPH_H
