#include <cstdio>
#include <iostream>
#include "dijkstra.h"
#include "aStar.h"
// #include "genGraph.h"
#include <chrono>
#include <algorithm>





void setCoordinates(std::vector<std::pair<int,int>> &coordinates, int matSize);
void initializeConnections(std::vector<std::pair<int,int>> &coordinates, int matSize, std::vector<std::vector<int>> &matrix, std::unordered_set<int> obstacles);
void visualizeGraph(int matSize, std::unordered_set<int> &obstacles, int obstacleChance, int source, int destination);
void visualizeGraph(int matSize, std::unordered_set<int> &obstacles);
void readIntoList(std::vector<std::vector<adjListNode>> &readList);

int main() {
    
    srand(time(NULL));

    std::vector<std::vector<int>> matrix;
    std::unordered_set<int> obstacles;


    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto durationDijk = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto durationAStarA = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);




    // PARAMETERS HERE:

    // Size, preferably in perfect squares.
    int matSize = 10000;   
    // Source and destination
    int source = 0;     
    int destination = 9999;
    int obstacleChance = 25;

    source = rand() % matSize;
    destination = rand() % matSize;

    while(std::find(begin(obstacles), end(obstacles), source) != end(obstacles))
        source = rand() % matSize;

    while(std::find(begin(obstacles), end(obstacles), destination) != end(obstacles))
        destination = rand() % matSize;

    

    std::vector<std::pair<int,int>> coordinates;

    start = std::chrono::high_resolution_clock::now();
    //Code goes here
    setCoordinates(coordinates, matSize);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with setCoordinates %ld", duration.count());

    

    // start = std::chrono::high_resolution_clock::now();
    // //Code goes here
    // visualizeGraph(matSize, obstacles, obstacleChance, source, destination);
    // stop = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // printf("\n Done with visualize graph %ld", duration.count());

    // // Custom obstacles

    // // Border
    // for(int i=0;i<=49;i++) {
    //     obstacles.insert(i);
    //     obstacles.insert(i+2450);

    // }
    
    // for(int i=99;i<=2449;i+=50) {
    //     obstacles.insert(i);
    //     obstacles.insert(i-49);
    // }

    
    // // Wall 1
    // for(int i=9;i<2500;i+=50) {
    //     if(i>1100 && i<1300)
    //         continue;
    //     obstacles.insert(i);
    // }


    // // Wall 2
    // for(int i=29;i<2500;i+=50) {
    //     if(i>700 && i<900)
    //         continue;
    //     if(i>1500 && i<1700)
    //         continue;
        
    //     obstacles.insert(i);
    // }

    // for(int i=1279;i<1300;i++)
    //         obstacles.insert(i);

    // for(int i=665;i<675;i++) {
    //     for(int j=0;j<500;j+=50) {
    //         obstacles.insert(i+j);
    //     }

    //     for(int j=700;j<1200;j+=50) {
    //         obstacles.insert(i+j);
            
    //     }

    //     for(int j=1400;j<1900;j+=50) {
    //         obstacles.insert(i+j);
            
    //     }
    // }

    // for(int i=184;i<197;i++) {
    //     obstacles.insert(i);
    // }
    // for(int i=234;i<1000;i+=50) {
    //     obstacles.insert(i);
    // }

    // // Inter-walls for room 1
    // for(int i=1451;i<=1458;i++){
    //     if(i == 1455 || i == 1456)
    //         continue;
    //     obstacles.insert(i);
    // }

    // for(int i=2001;i<=2008;i++){
    //     if(i == 2003 || i == 2004)
    //         continue;
    //     obstacles.insert(i);
    // }

    // for(int i=651;i<=658;i++){
    //     if(i == 651 || i == 652)
    //         continue;
    //     obstacles.insert(i);
    // }

    // for(int i=251;i<=258;i++){
    //     if(i == 257 || i == 258)
    //         continue;
    //     obstacles.insert(i);
    // }

    // //Inverse L on room 2
    // for(int i=787;i<=792;i++)
    //     obstacles.insert(i);
    
    // for(int i=342;i<=800;i+=50)
    //     obstacles.insert(i);

    // // Long walls, room 3
    // for(int i=1333;i<=2333;i+=50)
    //     obstacles.insert(i);
    // for(int i=1436;i<=2436;i+=50)
    //     obstacles.insert(i);
    // for(int i=1439;i<=2339;i+=50)
    //     obstacles.insert(i);




    

    
    

    // visualizeGraph(matSize, obstacles);


    // printf("\n Obstacles are: ");
    // for(int i:obstacles)
    //     printf("%d ", i);
    


    // start = std::chrono::high_resolution_clock::now();
    // //Code goes here
    // initializeConnections(coordinates, matSize, matrix, obstacles);
    // stop = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // printf("\n Done with connections %ld", duration.count());

    



    std::vector<std::vector<adjListNode>> readList(matSize);

    readIntoList(readList);


    
    start = std::chrono::high_resolution_clock::now();
    Graph g(readList, coordinates);
    // Graph g(matrix, coordinates);
    stop = std::chrono::high_resolution_clock::now();

    
    

    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("\n Done with graph stuff, time taken %ld", duration.count());

    printf("\n Source: %d Destination: %d", source, destination);



    Dijkstra dij;
    

    aStar star(1, 5);
    
    aStar star2(1, 1);


    int runs = 2;
    
    std::ofstream file1("outputs/dijkstra.txt", std::ios_base::app);
    std::ofstream file2("outputs/astarI.txt", std::ios_base::app);
    std::ofstream file3("outputs/astarA.txt", std::ios_base::app);

    while(runs-- >0) {

        printf("\n--------- RUN %d--------", runs);


        source = rand() % matSize;
        destination = rand() % matSize;

        while(std::find(begin(obstacles), end(obstacles), source) != end(obstacles))
            source = rand() % matSize;

        while(destination == source || std::find(begin(obstacles), end(obstacles), destination) != end(obstacles))
            destination = rand() % matSize;

        printf("\n Source: %d Destination: %d", source, destination);
    
    

        start = std::chrono::high_resolution_clock::now();
        result answer = dij.pathFindDijkstra(g, source, destination);
        stop = std::chrono::high_resolution_clock::now();
        durationDijk = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        start = std::chrono::high_resolution_clock::now();
        result answer2 = star.pathFind_AStar(g, source ,destination);
        stop = std::chrono::high_resolution_clock::now();
        durationAStar = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        start = std::chrono::high_resolution_clock::now();
        result answer3 = star2.pathFind_AStar(g, source ,destination);
        stop = std::chrono::high_resolution_clock::now();
        durationAStarA = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        printf("\n\n---------DIJKS---------\n\n");
        printf("\n Done with Dijkstra : %ld", durationDijk.count());
        printf("\n Path Length: %d\n", (int)answer.path.size());
        for(int i: answer.path) {
            printf("%d-->", i);
        }

        printf("\n Max open list size: %d\n Max closed list size: %d", answer.maxOpenSize, answer.maxCloseSize);


        printf("\n\n--------ASTAR---------\n\n");
        printf("\n Done with A-Star (Inadmissable) : %ld", durationAStar.count());
        printf("\n Path Length: %d\n", (int)answer2.path.size());
        for(int i: answer2.path) {
            printf("%d-->", i);
        }

        printf("\n Max open list size: %d\n Max closed list size: %d", answer2.maxOpenSize, answer2.maxCloseSize);

        printf("\n\n--------ASTAR---------\n\n");
        printf("\n Done with A-Star (Admissable) : %ld", durationAStarA.count());
        printf("\n Path Length: %d\n", (int)answer3.path.size());
        for(int i: answer3.path) {
            printf("%d-->", i);
        }

        printf("\n Max open list size: %d\n Max closed list size: %d", answer3.maxOpenSize, answer3.maxCloseSize);


        printf("\n\n \t\tRun Summary:\n\n");
        printf("\n \tSource: %d ----------------> Destination: %d\n\n", source, destination);
        printf("\n\tDijkstra\tA-Star-I\tA-Star-A");
        printf("\nTime:\t%ld\t\t%ld\t\t%ld", durationDijk.count(), durationAStar.count(), durationAStarA.count());
        printf("\nPath:\t%d\t\t%d\t\t%d", (int)answer.path.size(), (int)answer2.path.size(), (int)answer3.path.size());
        printf("\nOpen:\t%d\t\t%d\t\t%d", answer.maxOpenSize, answer2.maxOpenSize, answer3.maxOpenSize);
        printf("\nClose:\t%d\t\t%d\t\t%d", answer.maxCloseSize, answer2.maxCloseSize, answer3.maxCloseSize);
        printf("\n-----------------------------------------------------------------------");

        file1 << durationDijk.count();
        file1 <<" ";
        file1 <<(int)answer.path.size();
        file1 << " ";
        file1 <<answer.maxOpenSize;
        file1 << " ";
        file1 <<answer.maxCloseSize;
        file1 << "\n";

        file2 << durationAStar.count();
        file2 <<" ";
        file2 <<(int)answer2.path.size();
        file2 << " ";
        file2 <<answer2.maxOpenSize;
        file2 << " ";
        file2 <<answer2.maxCloseSize;
        file2 << "\n";

        file3 << durationAStarA.count();
        file3 <<" ";
        file3 <<(int)answer3.path.size();
        file3 << " ";
        file3 <<answer3.maxOpenSize;
        file3 << " ";
        file3 <<answer3.maxCloseSize;
        file3 << "\n";


        

    }

    file1.close();
    file2.close();
    file3.close();

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

void visualizeGraph(int matSize, std::unordered_set<int> &obstacles, int obstacleChance, int source, int destination) {

    std::ofstream file("obstacles.txt");

    // Visualize graph
    for(int i=0;i<sqrt(matSize);i++) {
        // printf("\n");
        for(int j=0;j<sqrt(matSize);j++) {

            int currentVertex = int(i*sqrt(matSize) + j);

            if(rand() % 100 < obstacleChance && currentVertex != source && currentVertex != destination) {
                // printf("X\t");
                
                obstacles.insert(currentVertex);
                file << currentVertex;
                file << " ";

            }
            // else
                // printf("%d\t", currentVertex);

        }
    }

    file.close();
}

void visualizeGraph(int matSize, std::unordered_set<int> &obstacles) {

    std::ofstream file("obstacles.txt");

    // Visualize graph
    for(int i=0;i<sqrt(matSize);i++) {
        //printf("\n");
        for(int j=0;j<sqrt(matSize);j++) {

            int currentVertex = int(i*sqrt(matSize) + j);

            if( std::find(begin(obstacles), end(obstacles), currentVertex) != std::end(obstacles) ) {
                //printf("X\t");

                file << currentVertex;
                file << " ";
                
            }
            

        }
    }

    file.close();
}

void initializeConnections(std::vector<std::pair<int,int>> &coordinates, int matSize, std::vector<std::vector<int>> &matrix, std::unordered_set<int> obstacles)  {
    // Connections initialized
    for(int i=0;i<matSize;i++) {
        matrix.push_back(std::vector<int>(matSize, 0));

        if(std::find(begin(obstacles), end(obstacles), i) != end(obstacles))
            continue;

        for(int j=0;j<matSize;j++) {


            if(std::find(begin(obstacles), end(obstacles), j) != end(obstacles)){
                matrix[i][j] = 0;
                continue;
            }
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

            else if(abs(coordinates[i].first - coordinates[j].first) == 1 && abs(coordinates[i].second - coordinates[j].second) == 1)
                matrix[i][j] = 1;
            
            // Set obstacles
            

            


           
        }

    }
}

// Read contents of file into adjacency list object
void readIntoList(std::vector<std::vector<adjListNode>> &readList) {

    std::ifstream file;



    file.open("adjList.txt");

    



    if(!file) {
        //cout << "Error unable to open file";
    }

    int source, destination, weight;
    source = destination = weight = 0;

    

    // Read data till eof
    while(!file.eof()) {

        

        file >> source;
        file >> destination;
        file >> weight;

        
        

        readList[source].push_back(adjListNode(destination, weight));

    }

    file.close();





}