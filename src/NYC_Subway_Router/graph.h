#pragma once
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <unordered_set>
#include <stack>
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
    vector<int> dijkstra(int src, int dest);
    double distance(int src, int dest);
    vector<int> aStar(int stc, int dest);
    double dTime = 0;
    double aTime = 0;
    vector<string> getStationNameVector(vector<int> vi);
    string convertVectorToString(vector<string> vs);
    string findSwitches(vector<int> vi);
    void plotroute(vector<int> vi);

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
