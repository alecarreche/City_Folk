#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

class Graph {

public:
    struct Station {
        string name;
        double latitude;
        double longitude;
    };

    void importStations(string fileName);
    void importEdges(string fileName);
    int findClosestStation(pair<double, double> loc);
    string getStationName(int id);

private:
    map<int, Station> stationID;
    map<int, vector<pair<int, pair<string, double>>>> adjList;
    // first -> int: "from" ID
    // second -> vector
    //           pair<int, pair>
    //                "to" ID
    //                      pair<string, double>
    //                           string = Route Identifier
    //                           double = distance (weight)

};
