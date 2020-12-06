#include <iostream>
#include "MainProgram.h"
using namespace std;

int main(int argc, char **argv){
    QApplication app (argc, argv);
    MainProgram win;
    win.subway.importStations("station_data.csv");
    win.subway.importEdges("edges.csv");

    win.show();
    app.exec();

    QWidget *DSP = new QWidget;
    QWidget *ASP = new QWidget;
    DSP->setWindowTitle("Shortest Path");
    ASP->setWindowTitle("Shortest Path");
    QLabel dijkstras("Dijkstra's: \n" + QString::fromStdString(win.dspStations));
    QLabel astar("A*: \n" + QString::fromStdString(win.aspStations));

    QVBoxLayout *layoutD = new QVBoxLayout;
    layoutD->addWidget(&dijkstras);
    DSP->setLayout(layoutD);

    QVBoxLayout *layoutA = new QVBoxLayout;
    layoutA->addWidget(&astar);
    ASP->setLayout(layoutA);

    if (win.testInput == true){
        DSP->show();
        ASP->show();
        app.exec();
    }

    QWidget *analysis = new QWidget;
    analysis->setWindowTitle("Computation Time for 100 locations");
    QLabel dijkstras2(QString::fromStdString("Total time Dijskstra's: " + to_string(win.totalTimeSecsDijkstras) + "s"));
    QLabel dijkstras3(QString::fromStdString("Average time per iteration Dijskstra's: " + to_string((win.totalTimeSecsDijkstras/100)) + "s"));
    QLabel astar2(QString::fromStdString("Total time A*: " + to_string(win.totalTimeSecsAstar) + "s"));
    QLabel astar3(QString::fromStdString("Average time per iteration A*: " + to_string((win.totalTimeSecsAstar/100)) + "s"));

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(&dijkstras2);
    layout2->addWidget(&dijkstras3);
    layout2->addWidget(&astar2);
    layout2->addWidget(&astar3);
    analysis->setLayout(layout2);
    if (win.testProgram == true) {
        analysis->show();
        app.exec();
    }
}
