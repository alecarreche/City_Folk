#include <iostream>
#include "MainProgram.h"
using namespace std;

int main(int argc, char **argv){
    QApplication app (argc, argv);
    MainProgram win;
    win.subway.importStations("station_data.csv");
    win.subway.importEdges("edges.csv");

    //Shows the initial menu
    win.show();
    app.exec();

    //Creates windows to show directions based on the two algorithms
    QWidget *DSP = new QWidget;
    QWidget *ASP = new QWidget;
    DSP->setWindowTitle("Shortest Path");
    ASP->setWindowTitle("Shortest Path");
    QLabel dijkstras("Dijkstra's: \n\n" + QString::fromStdString(win.dspStations));
    QLabel astar("A*: \n\n" + QString::fromStdString(win.aspStations));

    //adds layout to windows
    QVBoxLayout *layoutD = new QVBoxLayout;
    layoutD->addWidget(&dijkstras);
    DSP->setLayout(layoutD);

    QVBoxLayout *layoutA = new QVBoxLayout;
    layoutA->addWidget(&astar);
    ASP->setLayout(layoutA);

    //If we clicked the input button, we show these two windows.
    if (win.testInput == true){
        DSP->show();
        ASP->show();
        app.exec();
    }

    // We create the window for the time analysis of the algorithms.
    QWidget *analysis = new QWidget;
    analysis->setWindowTitle("Computation Time for 100,000 locations");
    QLabel dijkstras2(QString::fromStdString("Total time Dijskstra's: " + to_string(win.totalTimeSecsDijkstras) + "s"));
    QLabel dijkstras3(QString::fromStdString("Average time per iteration Dijskstra's: " + to_string((win.totalTimeSecsDijkstras/100000)) + "s"));
    QLabel astar2(QString::fromStdString("Total time A*: " + to_string(win.totalTimeSecsAstar) + "s"));
    QLabel astar3(QString::fromStdString("Average time per iteration A*: " + to_string((win.totalTimeSecsAstar/100000)) + "s"));

    // create the layout for analysis window
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(&dijkstras2);
    layout2->addWidget(&dijkstras3);
    layout2->addWidget(&astar2);
    layout2->addWidget(&astar3);
    analysis->setLayout(layout2);

    //If we click the button to do the analysis, we show the window.
    if (win.testProgram == true) {
        analysis->show();
        app.exec();
    }
}
