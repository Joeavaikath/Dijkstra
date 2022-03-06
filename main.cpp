#include <cstdio>
#include "dijkstra.h"
#include "aStar.h"

int main() {
    

    //printf("Hello World");
    std::vector<std::vector<int>> matrix;
    int matSize = 64;

    std::vector<std::pair<int,int>> coordinates;

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
            std::list<int> obstacles = {8, 13, 18, 16, 17};

            if(std::find(begin(obstacles), end(obstacles), i) != end(obstacles) || std::find(begin(obstacles), end(obstacles), j) != end(obstacles))
                matrix[i][j] = 0;


        }
    }


    for(int i=0;i<matSize;i++) {
        printf("Row %d :" ,i);
        for(int j=0;j<matSize;j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    

    Graph g(matrix, coordinates);

    
    

    Dijkstra dij;
    aStar star;
    
    result answer = dij.pathFindDijkstra(g, 0, 24);
    // result answer = star.pathFind_AStar(g, 0 ,24);

    for(int i: answer.path) {
        printf("%d\t", i);
        printf("\n");
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer.maxOpenSize, answer.maxCloseSize);


    return 0;
}