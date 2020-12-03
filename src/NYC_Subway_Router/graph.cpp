#include "graph.h"

string Graph::getStationName(int id) {
    return stationID[id].name;
}

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

int Graph::findClosestStation(pair<double, double> loc) {
    double result = -1;
    double dist = -1;

    for (auto iter = stationID.begin(); iter != stationID.end(); iter++) {
        double lat = iter->second.latitude;
        double longit = iter->second.longitude;

        double curDist = sqrt(pow(lat-loc.first, 2.0) + pow(longit-loc.second, 2.0));
        
        if (result == -1 || curDist < dist) {
            result = iter->first;
            dist = curDist;
        }
    }

    return result;
}
