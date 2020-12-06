#pragma once
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QInputDialog>
#include <QCloseEvent>
#include <QStyle>
#include <QDesktopWidget>
#include <QBoxLayout>
#include <QLabel>
#include <sys/time.h>
#include <sys/resource.h>
#include <chrono>
#include "graph.h"
using namespace std;

class MainProgram : public QMainWindow {
    Q_OBJECT
public:
    explicit MainProgram(QWidget *parent = nullptr);
    vector<pair<pair<double, double>, pair<double, double>>> randlonglats;
    QPushButton *randlonglat, *inlonglat, *mapNY;
    Graph subway;
    string dspStations = "";
    string aspStations = "";
    bool testInput = false;
    bool testProgram = false;
    double totalTimeSecsDijkstras = 0;
    double totalTimeSecsAstar = 0;

public slots:
    void inputLongLat();
    void getLongLat();
};
