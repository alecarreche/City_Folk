#include <iostream>
#include "MainProgram.h"
using namespace std;

int main(int argc, char **argv){
    QApplication app (argc, argv);
    MainProgram win;
    win.subway.importStations("/Users/annahampton/Documents/COP3530/City_Folk/data/station_data.csv");
    win.subway.importEdges("/Users/annahampton/Documents/COP3530/City_Folk/data/edges.csv");

    win.show();
    return app.exec();
}
