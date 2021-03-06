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
        
        // std::vector<std::vector<int>> matrix = graph.getAdjMat();
        std::vector<std::vector<adjListNode>> adjList = graph.getAdjList();
        std::vector<std::pair<int,int>>  coordinates = graph.getCoordinates();
        result res;

        std::set<int> closedList;
        std::set<int> openList;

        // (Priority queue type, vector for storage, comparison operation)
        std::priority_queue<vertexDistance, std::vector<vertexDistance>, LessThanByEstimatedCost> openQuery;

    
        int V = adjList.size();
    
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

        // X and Y coordinate differences
        int x = coordinates[startNode].first - coordinates[endNode].first;
        int y = coordinates[startNode].second - coordinates[endNode].second;
        
        int subRes; 

        // 0 for Manhattan, 1 for Euclidean
        if(type == 0)
        // Manhattan distance
            subRes =   epsilon * (abs(x) + abs(y));
        else if(type == 1)
        // Euclidean distance
            subRes =  epsilon * (sqrt(pow(x,2) + pow(y,2)));
        else 
                subRes =  -1;
        
        // Initial estimate from source to destination
        estimatedDist[startNode] = subRes;
    
        // Find shortest path
        // for all vertices

        openQuery.push(vertexDistance(startNode,dist[startNode], estimatedDist[startNode]));

        int debug = 0;
        int openListruns = 0;
        while(openQuery.size() > 0)
        // for (int count = 0; count < V - 1; count++)
        {
            openListruns++;

            
            int u = openQuery.top().id;
            openQuery.pop();
            // int u = minDistance(estimatedDist, closed, V);


            // Destination node selected, we are done
            if(u == endNode) 
                break;
            
    
            
            closed[u] = true;
            closedList.insert(u);
            openList.erase(u);

             
            for (int i=0;i<adjList[u].size();i++){

            debug++;

            int v = adjList[u][i].id;
    
                

                if (dist[u] + adjList[u][i].distance < dist[v])
                {   
                    
                    parent[v] = u;
                    if(openList.find(v) == openList.end())
                        openList.insert(v);

                    res.maxOpenSize = std::max((int)openList.size(), res.maxOpenSize);

                    
                    dist[v] = dist[u] + adjList[u][i].distance;


                    /*  Calculate heruristic value - made inline because 
                     *  performance was taking a hit.
                    */

                    // X and Y coordinate differences
                    int x = coordinates[v].first - coordinates[endNode].first;
                    int y = coordinates[v].second - coordinates[endNode].second;
                    
                    int subRes; 

                    // 0 for Manhattan, 1 for Euclidean
                    if(type == 0)
                    // Manhattan distance
                        subRes =   epsilon * (abs(x) + abs(y));
                    else if(type == 1)
                    // Euclidean distance
                        subRes =  epsilon * (sqrt(pow(x,2) + pow(y,2)));
                    else 
                         subRes =  -1;



                
                    estimatedDist[v] = dist[v] + subRes;
                    // Update element with vertex value v to new distance value v
                    /*  The std library implementation for priority queue does not
                        allow removal of elements; the workaround is pushing in the 
                        same valued vertex with updated values. This is guarenteed to
                        work as new values will be lower than old values, so the heap
                        will always fetch the newest value.
                    */
                    openQuery.push(vertexDistance(v, dist[v], estimatedDist[v]));
                } 

                
            }
            
        }

        
        // ---Debug info for how many runs--- 
        // printf("\n debug: %d openListRuns: %d ", debug, openListruns);


        // Save the path to the result object
        while(endNode != -1) {
            // printf("\n %d %d", endNode, parent[endNode]);
            res.path.push_front(endNode);
            endNode = parent[endNode];
        }

        // Save closed list size to result object
        res.maxCloseSize = closedList.size();

        return res;
   
    }

};

#endif