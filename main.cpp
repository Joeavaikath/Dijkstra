#include <cstdio>
#include "dijkstra.h"
#include "aStar.h"


void setCoordinates(std::vector<std::pair<int,int>> &coordinates, int matSize);
void initializeConnections(std::vector<std::pair<int,int>> &coordinates, int matSize, std::vector<std::vector<int>> &matrix, std::list<int> obstacles);
void visualizeGraph(int matSize, std::list<int> &obstacles, int obstacleChance, int source, int destination);
void visualizeGraph(int matSize, std::list<int> &obstacles);

int main() {
    
    srand(time(NULL));

    std::vector<std::vector<int>> matrix;
    std::list<int> obstacles;

    // PARAMETERS HERE:

    // Size, preferably in perfect squares.
    int matSize = 100;   
    // Source and destination
    int source = 0;     
    int destination = 99;
    int obstacleChance = 40;

    std::vector<std::pair<int,int>> coordinates;

    setCoordinates(coordinates, matSize);

    // visualizeGraph(matSize, obstacles, obstacleChance, source, destination);

    // Custom obstacles
    obstacles = {51, 52, 53,54,55,45, 35, 25, 15};
    visualizeGraph(matSize, obstacles);

    printf("\n Obstacles are: ");
    for(int i:obstacles)
        printf("%d ", i);
    

    initializeConnections(coordinates, matSize, matrix, obstacles);
    

    Graph g(matrix, coordinates);


    Dijkstra dij;
    aStar star(1, 5);
    aStar star2(0, 5);
    

    
    result answer = dij.pathFindDijkstra(g, source, destination);
    result answer2 = star.pathFind_AStar(g, source ,destination);
    result answer3 = star2.pathFind_AStar(g, source ,destination);

    printf("\n\n---------DIJKS---------\n\n");
    for(int i: answer.path) {
        printf("%d-->", i);
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer.maxOpenSize, answer.maxCloseSize);


    printf("\n\n--------ASTAR---------\n\n");
    for(int i: answer2.path) {
        printf("%d-->", i);
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer2.maxOpenSize, answer2.maxCloseSize);

    printf("\n\n--------ASTAR---------\n\n");
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
            

            if(coordinates[i].first == coordinates[j].first) {
                if(abs(coordinates[i].second - coordinates[j].second) == 1)
                
                matrix[i][j] = 1;
            }

            if(coordinates[i].second == coordinates[j].second) {
                if(abs(coordinates[i].first - coordinates[j].first) == 1)
                
                matrix[i][j] = 1;
            }

            if(abs(coordinates[i].first - coordinates[j].first) == 1 && abs(coordinates[i].second - coordinates[j].second) == 1)
                matrix[i][j] = 1;
            
            // Set obstacles
            

            if(std::find(begin(obstacles), end(obstacles), i) != end(obstacles) || std::find(begin(obstacles), end(obstacles), j) != end(obstacles))
                matrix[i][j] = 0;


        }
    }
}