#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Edge {
public:
    float origin;
    float desired;
    float weight;
};

class Graph {
    vector<vector<Edge>> adjList = {}; // Setup an adjacency list by using edge class vectors
    // Vector of vectors, use as adjacent list
public:
    
    Graph(vector<Edge> const &edges, float N) { // This is the constructor
        adjList.resize(N);
        for (Edge const &edge: edges)
            adjList[edge.origin].push_back(edge); // Push it to the adjacent list vector
    }
    
    ~Graph(){
        cout << "Destructor for graph class called." << endl;
    }
    
    void print_route(vector<float> const &prev, float i) {
        // Setup a condition so it doesnt loop. Xcode said so.
        if (i < 0)
            return;
        // End of index, so print backwards
        print_route(prev, prev[i]); // This uses recursion to step backwards and print it in reverse order
        cout << i << " ";
    }
    
    // Need this for the heap
    struct Node {
        float vertex;
        float weight;
    };
    
    // Comparison object to be used to order the heap
    struct comp {
        bool operator()(const Node &lhs, const Node &rhs) const {
            return lhs.weight > rhs.weight;
        }
    };
    
    void shortestPath(float source, float N, float desired) {
        
        priority_queue<Node, vector<Node>, comp> minHeap; // Learned this min heap implementation from geeksforgeeks
        
        /* I couldn't figure out how to implement the min heap using the provided header file, so I went with a suggestion from GeeksForGeeks and used the priority queue from the library */
        
        minHeap.push({source, 0}); // Push the source to the minheap
        float maxInf = 99999; // Treat this as infinity
        vector<float> distanceVector(N, maxInf); // Set the default distance vector with the max
        distanceVector[source] = 0;
        vector<float> prev(N, - 1); // The previous is going to range from
        vector<bool> visited(N, false); // Checking if it's been visited or not
        visited[0] = true; // Set the source to zero
        while (!minHeap.empty()) { // Keep going until you've exhausted the heap nodes
            Node node = minHeap.top(); // The node is the top, and then pop it off
            minHeap.pop(); // Now go though the neighbors of the adjacency list
            for (auto lookedAtEdge: this->adjList[node.vertex]){ // Go through for each node's neighbors. Hi neighbor.
                float v = lookedAtEdge.desired;
                float weight = lookedAtEdge.weight;
                if ((distanceVector[node.vertex] + weight) < distanceVector[v] && !visited[v]){ // And it hasn't been visited
                    distanceVector[v] = distanceVector[node.vertex] + weight;
                    prev[v] = node.vertex; // The previous for that desired vertex
                    minHeap.push({v, distanceVector[v]}); // Now push it to the minheap
                }
            }
            // Now you can mark the node as visited, and go to the next node
            visited[node.vertex] = true;
        }
        
        for (float i = 0; i < N; ++i) { // This prints the route when calling for the shortest path
            if (i == desired) { // You can ask it to print all the verticies, if you wanted to.
                // Instead we only want to print for the desired vertex
                cout << "Shortest path for " << source << " to " << i << ": " << endl;
                print_route(prev, i);
                cout << endl;
            }
        }
    }
};

#endif
