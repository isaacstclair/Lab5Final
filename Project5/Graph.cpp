
#include <iostream>
#include "Graph.h"

Graph::Graph(std::vector<Rule> Rules){
    std::set<int> newSet;
    for(int i=0; i<int(Rules.size()); i++){
        adjacencyList.insert(std::pair<int, std::set<int>>(i, newSet));
    }

    for(int i=0; i<int(Rules.size()); i++){
        visited.push_back(false);
    }

}

Graph::~Graph(){
    Rules.clear();
    adjacencyList.clear();
}

void Graph::AddEdge(int from, int to){
    adjacencyList.at(from).insert(to);
}

std::vector<int> Graph::dfsPostOrder(int vertex){
    visited.at(vertex) = true;
    std::set<int>::iterator set_it;
    for(set_it = adjacencyList.at(vertex).begin(); set_it != adjacencyList.at(vertex).end(); ++set_it) {
        if(!visited.at(*set_it)){
            dfsPostOrder(*set_it);
        }
    }
    postorder.push_back(vertex);
    return(postorder);
}

std::vector<int> Graph::dfsSearchTree(int vertex) {
    std::set<int>::iterator set_it;
    visited.at(vertex) = true;

    for (set_it = adjacencyList.at(vertex).begin(); set_it != adjacencyList.at(vertex).end(); ++set_it)
        if (!visited.at(*set_it)) {
            dfsSearchTree(*set_it);
        }

    searchtree.push_back(vertex);

    return(searchtree);
}

std::vector<std::vector<int>> Graph::dfsForestPostOrder(){
    for(int i=0; i<int(visited.size()); i++){
        postorder.clear();
        if(!visited.at(i)){
            std::vector<int> postordervector = dfsPostOrder(i);
            postorderforest.push_back(postordervector);
        }
    }
    return(postorderforest);
}


std::vector<std::set<int>> Graph::dfsForestSCC(std::vector<int> postorder){
    std::vector<std::set<int>> sccs;
    std::vector<int> toRun = GetReversePostOrder(postorder);
    for(int i=0; i<int(visited.size()); i++){
        searchtree.clear();
        if(!visited.at(toRun.at(i))){
            std::vector<int> sccVect = dfsSearchTree(toRun.at(i));
            std::set<int> scc;
            for(int j=0; j<int(searchtree.size()); j++){
                scc.insert(searchtree.at(j));
            }
            sccs.push_back(scc);
        }
    }

    return(sccs);
}

void Graph::PrintAdjList(){
    std::map<int, std::set<int>>::iterator map_it;
    std::set<int>::iterator set_it;

    for(map_it = adjacencyList.begin(); map_it != adjacencyList.end(); ++map_it){
        std::cout << "R" << map_it->first << ":";

        for(set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it)
            if(set_it == map_it->second.begin()){
                std::cout << "R" << *set_it;
            } else{
                std::cout << ",R" << *set_it;
            }

        std::cout << std::endl;
    }
}

std::vector<int> Graph::GetReversePostOrder(std::vector<int> normalorder){


    std::vector<int> reversedpostorder;
    for(int i=int(normalorder.size())-1; i>=0; i--){
        reversedpostorder.push_back(normalorder.at(i));
    }

    return(reversedpostorder);
}


bool Graph::HasItself(int node){
    std::set<int>::iterator set_it;
    std::set<int> thisSet = adjacencyList.at(node);
    for(set_it = thisSet.begin(); set_it != thisSet.end(); ++set_it){
        if(*set_it == node){
            return true;
        }
    }
    return false;
}