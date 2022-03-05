#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"
#include <bits/stdc++.h>
#include <set>
#include <queue>
#include <list>
#include <algorithm>

// Citation: AI For Games, Third Edition 2019. Section 4.2.3: Pseudo-Code (Dijkstra)
// What and why: Pseudocode helped implement good code.
// Citation: https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/


struct result {
        std::list<int> path;
        int maxCloseSize = 0;
        int maxOpenSize = 0;

};

// Vertex struct with distance
struct vertexDistance {
    int id;
    int distance;

    vertexDistance(int startNode, int distance) {
        this->id = startNode;
        this->distance = distance;
    }
};


class Dijkstra {


    

    
    public:
    // Returns the shortest path list
    result pathFindDijkstra(Graph graph, int startNode, int endNode) {

        
       
        // https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects
        // How to use priority queue for objects
        struct LessThanByCost
        {
            bool operator()(const vertexDistance& lhs, const vertexDistance& rhs) const
            {
                return lhs.distance < rhs.distance;
            }
        };   
        
        std::vector<std::vector<int>> matrix = graph.getAdjMat();
        result res;

        std::set<int> closedList;
        std::set<int> openList;

        // (Priority queue type, vector for storage, comparison operation)
        std::priority_queue<vertexDistance, std::vector<vertexDistance>, LessThanByCost> openQuery;

    
        int V = matrix.size();
    
        // printf("\n %d", V);
        // printf("\n %d", V);

        // Distances from startNode
        int dist[V];

        // Closed or not
        bool closed[V];

        // Parent vertices
        int parent[V];

        for (int i = 0; i < V; i++){
            parent[startNode] = -1;
            dist[i] = 999999;
            closed[i] = false;
        }
   
        // Distance of source vertex 
        // from itself is always 0
        dist[startNode] = 0;
    
        // Find shortest path
        // for all vertices

        openQuery.push(vertexDistance(startNode, 0));
        while(openQuery.size() > 0){

            // Pick the minimum distance
            // vertex from the set of
            // vertices not yet processed. 
            // u is always equal to src
            // in first iteration.
            while(closed[openQuery.top().id]) 
                openQuery.pop();
            
            int u = openQuery.top().id;


            // Destination node selected, we are done
            if(u == endNode) 
                break;
            
    
            // Mark the picked vertex 
            // as processed
            closed[u] = true;
            closedList.insert(u);
    
            // Update dist value of the 
            // adjacent vertices of the
            // picked vertex.
            for (int v = 0; v < V; v++){
    
                // Update dist[v] only if is
                // not in sptSet, there is
                // an edge from u to v, and 
                // total weight of path from
                // src to v through u is smaller
                // than current value of
                // dist[v]

                // printf("\n %d %d", closed[v], matrix[u][v]);
                // printf("\n %d %d %d", dist[u],  matrix[u][v], dist[v]);
            
                if (!closed[v] && matrix[u][v]!=0  && dist[u] + matrix[u][v] < dist[v])
                {   
                    
                    parent[v] = u;
                    if(openList.find(v) == openList.end())
                        openList.insert(v);
                    res.maxOpenSize++;
                    
                    dist[v] = dist[u] + matrix[u][v];
                    // Update element with vertex value v to new distance value v
                    openQuery.push(vertexDistance(v, dist[v]));
                } 
            }
        }

        
        

        while(endNode != -1) {
            // printf("\n %d %d", endNode, parent[endNode]);
            res.path.push_front(endNode);
            endNode = parent[endNode];
        }

        res.maxCloseSize = closedList.size();
        res.maxOpenSize = openList.size();

        return res;
   
    }

    int minDistance(int dist[], bool closed[], int size) {

        int min = INT_MAX;
        int minVertex = -1;

        for(int i=0;i<size;i++) {

            if(!closed[i]) {
                if(dist[i] < min) {
                    min = dist[i];
                    minVertex = i;
                }
            }
        }

        return minVertex;

    }


};

#endif