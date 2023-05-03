#include <iostream>
#include <queue>
#include <list>
#include "readFile.h"
#include "BFS.h"

Graph::Graph(int num) {
    num_ = num;
    visualize_ = false;
    adjacent = new std::list<int>[num_];
}

Graph::~Graph() {
    delete[] adjacent;
}

void Graph::insert_edge(int vertex1, int vertex2) {
    adjacent[vertex1].push_back(vertex2);
}

std::queue<int> Graph::BFS(int start, bool visualize) {
    if (visualize) {
        std::cout << "------Breadth First Traversal------\n";
        std::cout << "Starting Vertex: " << start << '\n';
    }

    // initialize variables
    int vertex;
    std::queue<int> container, traversal;

    // initialize the flag of all vertices
    bool *visit_flag = new bool[num_];
    for (int i = 0; i < num_; ++i) {
        visit_flag[i] = false;
    }

    // enqueue the starting vertex
    visit_flag[start] = true;
    container.push(start);
    traversal.push(start);

    while (!container.empty()) {
        vertex = container.front();
        if (visualize) {
            std::cout << vertex << " ";
        }
        container.pop();

        for (std::list<int>::iterator itr = adjacent[vertex].begin(); itr != adjacent[vertex].end(); ++itr) {
            if (!visit_flag[*itr]) {
                visit_flag[*itr] = true;
                container.push(*itr);
                traversal.push(*itr);
            }
        }
    }
    
    if (visualize) {
        std::cout << "\n-----------------------------------\n";
    } else {
        std::cout << "Breadth First Traversal Finished!\n";
    }
    delete[] visit_flag;
    return traversal;
}

void routes_traversal(int start, bool visualize) {
    int source_id, destination_id;
    std::vector<std::string> input = file_to_vector("./data/input.dat");
    Graph routes(input.size());

    for (size_t i = 0; i < input.size()-1; ++i) {
        source_id = std::stoi(splitString(input[i])[1]);
        destination_id = std::stoi(splitString(input[i])[2]);
        routes.insert_edge(source_id, destination_id);
    }

	routes.BFS(start, visualize);
}