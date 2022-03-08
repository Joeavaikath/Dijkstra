#ifndef ASTAR_H
#define ASTAR_H
#include "graph.h"
#include <bits/stdc++.h>
#include <set>
#include <queue>
#include <list>
#include <algorithm>

// Citation: AI For Games, Third Edition 2019. Section 4.2.3: Pseudo-Code (Dijkstra)
// What and why: Pseudocode helped implement good code.
// Citation: https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/





class aStar {


    int type;
    int epsilon;

    public:
    aStar(int type, int epsilon) {
        this->type = type;
        this->epsilon = epsilon;
    }

    
    // Returns the shortest path list
    result pathFind_AStar(Graph graph, int startNode, int endNode) {

        
       
        // https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects
        // How to use priority queue for objects
        struct LessThanByEstimatedCost
        {
            bool operator()(const vertexDistance& lhs, const vertexDistance& rhs) const
            {
                return lhs.estimatedTotalCost > rhs.estimatedTotalCost;
            }
        };   
        
        std::vector<std::vector<int>> matrix = graph.getAdjMat();
        std::vector<std::vector<adjListNode>> adjList = graph.getAdjList();
        std::vector<std::pair<int,int>>  coordinates = graph.getCoordinates();
        result res;

        std::set<int> closedList;
        std::set<int> openList;

        // (Priority queue type, vector for storage, comparison operation)
        std::priority_queue<vertexDistance, std::vector<vertexDistance>, LessThanByEstimatedCost> openQuery;

    
        int V = matrix.size();
    
        // printf("\n %d", V);
        // printf("\n %d", V);

        // Distances from startNode
        int dist[V];
        int estimatedDist[V];

        // Closed or not
        bool closed[V];

        // Parent vertices
        int parent[V];

        for (int i = 0; i < V; i++){
            parent[startNode] = -1;
            dist[i] = 999999;
            closed[i] = false;
            estimatedDist[i] = 999999;
        }
   
        // Distance of source vertex 
        // from itself is always 0
        dist[startNode] = 0;
        estimatedDist[startNode] = heuristic(startNode, endNode, coordinates, type);
    
        // Find shortest path
        // for all vertices

        openQuery.push(vertexDistance(startNode,dist[startNode], estimatedDist[startNode]));

        int debug = 0;
        while(openQuery.size() > 0)
        // for (int count = 0; count < V - 1; count++)
        {


            
            int u = openQuery.top().id;
            openQuery.pop();
            // int u = minDistance(estimatedDist, closed, V);


            // Destination node selected, we are done
            if(u == endNode) 
                break;
            
    
            
            closed[u] = true;
            closedList.insert(u);
            openList.erase(u);

             
            // for (int v = 0; v < V; v++){
            for (int i=0;i<adjList[u].size();i++){

            debug++;

            int v = adjList[u][i].id;
    
                
            
                if (matrix[u][v]!=0  && dist[u] + matrix[u][v] < dist[v])
                {   
                    
                    parent[v] = u;
                    if(openList.find(v) == openList.end())
                        openList.insert(v);

                    res.maxOpenSize = std::max((int)openList.size(), res.maxOpenSize);

                    
                    dist[v] = dist[u] + matrix[u][v];
                    estimatedDist[v] = dist[v] + heuristic(v, endNode, coordinates,type);
                    // Update element with vertex value v to new distance value v
                    openQuery.push(vertexDistance(v, dist[v], estimatedDist[v]));
                } 
            }
            
        }

        
        
        printf("\n debug: %d", debug);
        while(endNode != -1) {
            // printf("\n %d %d", endNode, parent[endNode]);
            res.path.push_front(endNode);
            endNode = parent[endNode];
        }

        res.maxCloseSize = closedList.size();


        // printf("\n Open set contents: ");
        // for(int i:openList) {
        //     printf("%d, ", i);
        // }

        // printf("\n Closed set contents: ");
        // for(int i:closedList) {
        //     printf("%d, ", i);
        // }

        

        

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

    int heuristic(int source, int destination, std::vector<std::pair<int,int>> coordinates, int type) {

        // Calculates and returns the heuristic estimation between the source and destination


        int x = coordinates[source].first - coordinates[destination].first;
        int y = coordinates[source].second - coordinates[destination].second;

        if(type == 0)
        // Manhattan distance
            return  epsilon * (abs(x) + abs(y));
        else if(type == 1)
        // Euclidean distance
            return epsilon * (sqrt(pow(x,2) + pow(y,2)));
        else 
            return -1;
    }


};

#endif