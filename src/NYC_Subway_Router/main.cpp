
#include <fstream>
#include "graph.cpp"
#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

vector<pair<double, double>> generateRandomLoc(int n);

int main() {
    Graph g;
    g.importStations("data/station_data.csv");
    g.importEdges("data/edges.csv");

    pair<double, double> test = make_pair(40.748817, -73.985428);
    int closest = g.findClosestStation(test);
    cout << g.getStationName(closest);

    return 0;
}

vector<pair<double, double>> generateRandomLoc(int n, double lowerLat, double upperLat, 
                                                double lowerLong, double upperLong) {

    vector<pair<double, double>> result;
    uniform_real_distribution<double> LatUnif(lowerLat, upperLat);
    uniform_real_distribution<double> LongUnif(lowerLong, upperLong);
    default_random_engine r;

    for (int i = 0; i < n; i++) {
        double lat = LatUnif(r);
        double longit = LongUnif(r);

        result.push_back(make_pair(lat, longit));
    }

    return result;

}