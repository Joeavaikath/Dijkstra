#include <cstdio>
#include <iostream>
#include "dijkstra.h"
#include "aStar.h"
// #include "genGraph.h"
#include <chrono>
#include <algorithm>





void setCoordinates(std::vector<std::pair<int,int>> &coordinates, int matSize);
void initializeConnections(std::vector<std::pair<int,int>> &coordinates, int matSize, std::vector<std::vector<int>> &matrix, std::list<int> obstacles);
void visualizeGraph(int matSize, std::list<int> &obstacles, int obstacleChance, int source, int destination);
void visualizeGraph(int matSize, std::list<int> &obstacles);

int main() {
    
    srand(time(NULL));

    std::vector<std::vector<int>> matrix;
    std::list<int> obstacles;


    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);



    // PARAMETERS HERE:

    // Size, preferably in perfect squares.
    int matSize = 2500;   
    // Source and destination
    int source = 0;     
    int destination = 2499;
    int obstacleChance = 30;

    // GenGraph gg;

    // matrix = gg.adjMatrix;
    //obstacles = gg.obstacles;

    // source = rand() % 2500;
    // while(std::find(begin(obstacles), end(obstacles), source) !=  end(obstacles))
    //     source = rand() % 2500;
    
    // destination = rand() % 2500;

    // while(source == destination || std::find(begin(obstacles), end(obstacles), destination) !=  end(obstacles))
    //     destination = rand() % 2500;

    
    

    std::vector<std::pair<int,int>> coordinates;

    start = std::chrono::high_resolution_clock::now();

    //Code goes here
    setCoordinates(coordinates, matSize);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with setCoordinates %ld", duration.count());

    start = std::chrono::high_resolution_clock::now();
    
    //Code goes here
    visualizeGraph(matSize, obstacles, obstacleChance, source, destination);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with visualize graph %ld", duration.count());

    // Custom obstacles
    // obstacles = {51, 52, 53,54,55,45, 35, 25, 15};
    // visualizeGraph(matSize, obstacles);


    // printf("\n Obstacles are: ");
    // for(int i:obstacles)
    //     printf("%d ", i);
    


    start = std::chrono::high_resolution_clock::now();
    
    //Code goes here
    initializeConnections(coordinates, matSize, matrix, obstacles);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with connections %ld", duration.count());

    


    
    
    start = std::chrono::high_resolution_clock::now();
    Graph g(matrix, coordinates);
    stop = std::chrono::high_resolution_clock::now();

    


    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with graph stuff, time taken %ld", duration.count());


    Dijkstra dij;
    

    aStar star(1, 5);
    
    aStar star2(0, 5);
    
    

    start = std::chrono::high_resolution_clock::now();
    result answer = dij.pathFindDijkstra(g, source, destination);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with dijk %ld", duration.count());

    start = std::chrono::high_resolution_clock::now();
    result answer2 = star.pathFind_AStar(g, source ,destination);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with astar1 %ld", duration.count());

    start = std::chrono::high_resolution_clock::now();
    result answer3 = star2.pathFind_AStar(g, source ,destination);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with astar2 %ld", duration.count());

    printf("\n\n---------DIJKS---------\n\n");
    printf("\n Path Length: %d\n", (int)answer.path.size());
    for(int i: answer.path) {
        printf("%d-->", i);
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer.maxOpenSize, answer.maxCloseSize);


    printf("\n\n--------ASTAR---------\n\n");
    printf("\n Path Length: %d\n", (int)answer2.path.size());
    for(int i: answer2.path) {
        printf("%d-->", i);
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer2.maxOpenSize, answer2.maxCloseSize);

    printf("\n\n--------ASTAR---------\n\n");
    printf("\n Path Length: %d\n", (int)answer3.path.size());
    for(int i: answer3.path) {
        printf("%d-->", i);
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer3.maxOpenSize, answer3.maxCloseSize);


    return 0;
}

void setCoordinates(std::vector<std::pair<int,int>> &coordinates, int matSize) {

    // Set coordinates
    int row, col;
    row = 0;
    col = 0;
    for(int i=0;i<matSize;i++) {
        coordinates.push_back(std::make_pair(row, col));
        col++;
        int wrapper = sqrt(matSize);
        col %= wrapper;
        if(col == 0)
            row++;
    }

}

void visualizeGraph(int matSize, std::list<int> &obstacles, int obstacleChance, int source, int destination) {

    // Visualize graph
    for(int i=0;i<sqrt(matSize);i++) {
        printf("\n");
        for(int j=0;j<sqrt(matSize);j++) {

            int currentVertex = int(i*sqrt(matSize) + j);

            if(rand() % 100 < obstacleChance && currentVertex != source && currentVertex != destination) {
                printf("X\t");
                
                obstacles.push_back(currentVertex);
            }
            else
                printf("%d\t", currentVertex);

        }
    }
}

void visualizeGraph(int matSize, std::list<int> &obstacles) {

    // Visualize graph
    for(int i=0;i<sqrt(matSize);i++) {
        printf("\n");
        for(int j=0;j<sqrt(matSize);j++) {

            int currentVertex = int(i*sqrt(matSize) + j);

            if( std::find(begin(obstacles), end(obstacles), currentVertex) != std::end(obstacles) ) {
                printf("X\t");
                
            }
            else
                printf("%d\t", currentVertex);

        }
    }
}

void initializeConnections(std::vector<std::pair<int,int>> &coordinates, int matSize, std::vector<std::vector<int>> &matrix, std::list<int> obstacles)  {
    // Connections initialized
    for(int i=0;i<matSize;i++) {
        matrix.push_back(std::vector<int>(matSize, 0));
        for(int j=0;j<matSize;j++) {
            
            // Sideways connections
            if(coordinates[i].first == coordinates[j].first) {
                if(abs(coordinates[i].second - coordinates[j].second) == 1)
                
                matrix[i][j] = 1;
            }

            else if(coordinates[i].second == coordinates[j].second) {
                if(abs(coordinates[i].first - coordinates[j].first) == 1)
                
                matrix[i][j] = 1;
            }

            // Diagonal connections
            // else if(abs(coordinates[i].first - coordinates[j].first) == 1 && abs(coordinates[i].second - coordinates[j].second) == 1)
            //     matrix[i][j] = 1;
            
            // Set obstacles
            

            if(std::find(begin(obstacles), end(obstacles), i) != end(obstacles) || std::find(begin(obstacles), end(obstacles), j) != end(obstacles))
                matrix[i][j] = 0;


           
        }

    }
}