#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>

// Citation: AI For Games, Third Edition 2019. Section 4.1.5: Representation
// What and why: Pseudocode helped implement good code.
// Im making use of an adjacency matrix, and replacing all uses of arrays with vectors.

struct result {
        std::list<int> path;
        int maxCloseSize = 0;
        int maxOpenSize = 0;

};

// Vertex struct with distance
struct vertexDistance {
    int id;
    int distance;
    int estimatedTotalCost;

    vertexDistance(int startNode, int distance) {
        this->id = startNode;
        this->distance = distance;
        this->estimatedTotalCost = 0;
    }
};

class Graph {

    std::vector<std::vector<int>> adjMat; // Adjacency matrix for the graph
    std::vector<std::pair<int,int>>  coordinates; // Coordinates for the graph

    public:
    Graph(std::vector<std::vector<int>> adjMat, std::vector<std::pair<int,int>> coordinates) {

        this->adjMat = adjMat;
        this->coordinates = coordinates;

    }

    std::vector<std::vector<int>> getAdjMat() {

        return adjMat;
    }

    std::vector<std::pair<int,int>> getCoordinates() {

        return coordinates;
    }

};



#endif