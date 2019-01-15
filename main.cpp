//
//  main.cpp
//  Gallegos-Michael-PA5
//
//  Created by Michael Gallegos on 12/4/18.
//  Copyright © 2018 Michael Gallegos. All rights reserved.
//

#include "Graph.h"

int main() {
    vector<float> inputVector = {};
    float numberOfElements = 0;
    ifstream infile("/Users/Snowspeeder/Documents/School/CSCE 221/PA5/Gallegos-Michael-PA5/Gallegos-Michael-PA5/graph.txt");
    string file_contents { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
    stringstream ssin(file_contents);
    while (ssin.good()) {
        string x = "";
        ssin >> x;
        inputVector.push_back(stof(x));
        numberOfElements++;
    }
    
    float numberOfVerticies = inputVector[0];
    float pathToFrom1 = inputVector[numberOfElements-2];
    // Cut out the bottom/top lines, add 1 to get the number of elements and then take from the bottom line
    float pathToFrom2 = inputVector[numberOfElements - 1];
    float numberOfLines = (numberOfElements-4)/3 + 2;
    cout << "Number of lines in input file: " << numberOfLines << endl;
    cout << "Number of verticies to deal with: " << numberOfVerticies << endl;
    cout << "Path from " << pathToFrom1 << " going to " << pathToFrom2 << endl;
    
    // initialize edges as per above diagram
    vector<Edge> edges = {};
    // This is to print, define, and push the verticies and edge weights to the vector
    for (float i = 0; i < (numberOfLines) - 2; i++){ // Don't include the first or last line
        float source = inputVector[3*i + 2]; // This way it gets the element at the right spot
        float dest = inputVector[3*i + 3]; // Some of this was trial and error
        float wt = inputVector[3*i + 4];
        edges.push_back({source, dest, wt});
        cout << "Pushing: "<< source << " " << dest << " " << wt << endl;
    }
    Graph graph(edges, numberOfVerticies); // Use the graph class
    graph.shortestPath(0, numberOfVerticies, inputVector[numberOfElements - 1]);
    // You want the shortest path between the desired element and the element at the end of the vector
    return 0;
}
