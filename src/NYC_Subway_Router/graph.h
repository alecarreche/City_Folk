#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Graph {

public:
    struct Station {
        double latitude;
        double longitude;
    };

    void importStations(string fileName);
    void importEdges(string fileName);

private:
    map<string, Station> stationID;
    map<string, vector<pair<string, pair<char, double>>>> adjList;
};

void Graph::importStations(string fileName) {
    ifstream stations;
    stations.open(fileName);

    string curRow;
    
    // skip header row
    getline(stations, curRow);

    while(getline(stations, curRow)) {

        Station curStation;
        string cell;
        stringstream row(curRow);
        
        // skip index col
        getline(row, cell, ',');

        // Stop Name
        getline(row, cell, ',');
        string stopName = cell;

        // Lat
        getline(row, cell, ',');
        curStation.latitude = stod(cell);

        // Long
        getline(row, cell, ',');
        curStation.longitude = stod(cell);

        stationID.emplace(stopName, curStation);
    }
}

void Graph::importEdges(string fileName) {
    ifstream edges;
    edges.open(fileName);

    string curRow;

    // skip header row
    getline(edges, curRow);
    
    while(getline(edges, curRow)) {

        string cell;
        stringstream row(curRow);

        // skip index col 
        getline(row, cell, ',');

        // Route
        getline(row, cell, ',');
        char route = cell[0];

        // To
        getline(row, cell, ',');
        string to = cell;

        // From
        getline(row, cell, ',');
        string from = cell;

        // Dist
        getline(row, cell, ',');
        double distance = stod(cell);

        // "to" direction
        pair<char, double> routeDist = make_pair(route, distance);
        pair<string, pair<char, double>> edge = make_pair(to, routeDist);

        if(adjList.find(from) == adjList.end()) {
            adjList[from] = {edge};
        } else {
            adjList[from].push_back(edge);
        }

        // "from" direction
        pair<string, pair<char, double>> reverseEdge = make_pair(from, routeDist);

        if(adjList.find(to) == adjList.end()) {
            adjList[to] = {reverseEdge};
        } else {
            adjList[to].push_back(reverseEdge);
        }

    }

}

