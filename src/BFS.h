#pragma once
#include <iostream>
#include <queue>
#include <list>

class Graph {
    public:
        // constructor
        Graph(int num);

        // destructor
        ~Graph();

        // insert edge to graph
        void insert_edge(int vertex1, int vertex2);

        // BFS traversal
        std::queue<int> BFS(int start, bool visualize);
    
    private:
        // number of vertices
        int num_;

        // visualization
        bool visualize_;

        // adjacency lists
        std::list<int> *adjacent;
};

void routes_traversal(int start, bool visualize);