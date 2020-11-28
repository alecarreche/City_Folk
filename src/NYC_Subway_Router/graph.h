#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Graph {

public:
    struct Station {
        string stopName;
        double latitude;
        double longitude;
        vector<char> routes;
    };

    void importStations(string fileName);
    void importEdges(string fileName);

private:
    map<string, Station> stationID;
    map<int, pair<int, int>> adjList;
};

void Graph::importStations(string fileName) {

}

void Graph::importEdges(string fileName) {
    
}

