#include <cstdio>
#include "dijkstra.h"

int main() {
    

    //printf("Hello World");
    std::vector<std::vector<int>> matrix = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
                        {0, 0, 4, 0, 10, 0, 2, 0, 0},
                        {0, 0, 0, 14, 0, 2, 0, 1, 6},
                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
                        {0, 0, 2, 0, 0, 0, 6, 7, 0}
                    };

    matrix =    {{0, 1, 3},
                {0, 0, 1},
                {0, 0, 0}
    };

    Graph g(matrix);

    
    

    Dijkstra dij;
    
    result answer = dij.pathFindDijkstra(g, 0, 2);

    for(int i: answer.path) {
        printf("%d\t", i);
        printf("\n");
    }

    printf("\n Max open list size: %d\n Max closed list size: %d", answer.maxOpenSize, answer.maxCloseSize);


    return 0;
}