#include "head.h" 
#include "SimpleHeap.h" 
#include "BinomialHeap.h" 
#include "FibHeap.h" 
#include <ctime> 
#include <chrono>
#include <random>

extern int dist[MAX]; // Store distances from the source node
extern int _prev[MAX]; // Store the previous node in the shortest path
extern bool vis[MAX]; // Track visited nodes

const int TestSize = 10000; // Size of the test
const int PickSize = 1000; // Size of the pick

int main()
{
    Graph G = CreateGraph(); // Create a graph object G
    for (int i = 0; i < MAX; i++) 
    {
        dist[i] = INF; // Initialize distance to infinity
        _prev[i] = -1; // Initialize previous node to -1 indicating no previous node)
        vis[i] = false; // Mark all nodes as not visited
    }

    Heap *FibonacciHeap = new FibHeap(); 
    Heap *SimpHeap = new SimpleHeap(); 
    Heap *BinoHeap = new BinomialHeap();

    // Test SimpleHeap
    clock_t start; // Define a clock variable to measure time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Generate a seed
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, TestSize); // Define a uniform distribution for random integers from 1 to TestSize

    cout << "SimpHeap\n"; 
    start = clock(); // Get the current time
    dijkstra(SimpHeap, G, 1); // Perform Dijkstra's algorithm using the SimpleHeap
    std::cout << "SimpHeap costs: "
              << (clock() - start) * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl; 

    // Test BinomialHeap
    for (int i = 0; i < MAX; i++) 
    {
        dist[i] = INF; // Reset distance to infinity
        _prev[i] = -1; // Reset previous node to -1
        vis[i] = false; // Mark all nodes as not visited
    }

    cout << "BinoHeap\n"; 
    start = clock(); // Get the current time
    dijkstra(BinoHeap, G, 1); // Perform Dijkstra's algorithm using the BinomialHeap
    std::cout << "BinoHeap costs: "
              << (clock() - start) * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl; 

    // Test FibonacciHeap
    for (int i = 0; i < MAX; i++) 
    {
        dist[i] = INF; // Reset distance to infinity
        _prev[i] = -1; // Reset previous node to -1
        vis[i] = false; // Mark all nodes as not visited
    }

    cout << "FibHeap\n";
    start = clock(); // Get the current time
    dijkstra(FibonacciHeap, G, 1); // Perform Dijkstra's algorithm using the FibonacciHeap
    std::cout << "FibHeap costs: "
              << (clock() - start) * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0; 
}

