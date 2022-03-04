#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

// Citation: AI For Games, Third Edition 2019. Section 4.1.5: Representation
// What and why: Pseudocode helped implement good code.
// Im making use of an adjacency matrix, and replacing all uses of arrays with vectors.

class Graph {

    std::vector<std::vector<int>> adjMat; // Adjacency matrix for the graph

    public:
    Graph(std::vector<std::vector<int>> adjMat) {

        this->adjMat = adjMat;

    }

    std::vector<std::vector<int>> getAdjMat() {

        return adjMat;
    }

};



#endif