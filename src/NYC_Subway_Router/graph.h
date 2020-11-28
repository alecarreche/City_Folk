#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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

private:
    map<int, Station> stationID;
    map<int, vector<pair<int, pair<string, double>>>> adjList;
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

        // Stop ID
        getline(row, cell, ',');
        int ID = stoi(cell);

        // Stop Name
        getline(row, cell, ',');
        curStation.name = cell;

        // Lat
        getline(row, cell, ',');
        curStation.latitude = stod(cell);

        // Long
        getline(row, cell, ',');
        curStation.longitude = stod(cell);

        stationID.emplace(ID, curStation);
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
        string route = cell;

        // To
        getline(row, cell, ',');
        int to = stoi(cell);

        // From
        getline(row, cell, ',');
        int from = stoi(cell);

        // Dist
        getline(row, cell, ',');
        double distance = stod(cell);

        // "to" direction
        pair<string, double> routeDist = make_pair(route, distance);
        pair<int, pair<string, double>> edge = make_pair(to, routeDist);

        if(adjList.find(from) == adjList.end()) {
            adjList[from] = {edge};
        } else {
            adjList[from].push_back(edge);
        }

        // "from" direction
        pair<int, pair<string, double>> reverseEdge = make_pair(from, routeDist);

        if(adjList.find(to) == adjList.end()) {
            adjList[to] = {reverseEdge};
        } else {
            adjList[to].push_back(reverseEdge);
        }

    }

}

