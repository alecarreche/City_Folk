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
