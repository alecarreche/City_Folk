
#include <fstream>
#include "graph.h"
using namespace std;

int main() {
    Graph g;
    g.importStations("data/station_data.csv");
    g.importEdges("data/edges.csv");

    return 0;
}