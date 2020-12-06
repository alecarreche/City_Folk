#include "MainProgram.h"

MainProgram::MainProgram(QWidget *parent) : QMainWindow(parent){
    this->setFixedSize(380, 120);
    this->setWindowTitle("Menu Options for Calculating Shortest Path");

    randlonglat = new QPushButton("Generate Random Longitudes and Latitudes", this);
    inlonglat = new QPushButton("Enter Starting and Destination", this);

    randlonglat->setGeometry(5, 10, 370, 50);
    inlonglat->setGeometry(5,60, 370, 50);

    QObject::connect(randlonglat, SIGNAL(clicked()), this, SLOT(getLongLat()));
    QObject::connect(inlonglat, SIGNAL(clicked()), this, SLOT(inputLongLat()));
}

void MainProgram::inputLongLat() {
    this->hide();
    QWidget win;
    win.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, win.size(), qApp->desktop()->availableGeometry()));

    double temp1, temp2, temp3, temp4;

    bool pressed1 = false;
    bool pressed2 = false;
    bool pressed3 = false;
    bool pressed4 = false;

    temp1 = QInputDialog::getDouble(&win, "Input", "Starting Longitude (bounds: -74.045376, -73.740905)", 0, -74.045376, -73.740905, 6, &pressed1, Qt::WindowFlags(), 1);
    if (pressed1 == true) {
        temp2 = QInputDialog::getDouble(&win, "Input", "Starting Latitude (bounds: 40.561627, 40.917625)", 0, 40.561627, 40.917625, 6, &pressed2, Qt::WindowFlags(), 1);
        if (pressed2 == true) {
            temp3 = QInputDialog::getDouble(&win, "Input", "Destination Longitude (bounds: -74.045376, -73.740905)", 0,-74.045376, -73.740905, 6, &pressed3, Qt::WindowFlags(), 1);
            if (pressed3 == true) {
                temp4 = QInputDialog::getDouble(&win, "Input", "Destination Latitude (bounds: 40.561627, 40.917625)", 0,40.561627, 40.917625, 6, &pressed4, Qt::WindowFlags(), 1);
            }
        }
    }

    win.show();

    if (pressed1 == false || pressed2 == false || pressed3 == false || pressed4 == false) {
        this->show();
    }

    if (pressed1 == true && pressed2 == true && pressed3 == true && pressed4 == true) {
        testInput = true;

        int src = subway.findClosestStation(make_pair(temp2, temp1));
        int dest = subway.findClosestStation(make_pair(temp4, temp3));
        vector<int> dsp = subway.dijkstra(src, dest);
        vector<int> asp = subway.aStar(src, dest);

        dspStations = subway.findSwitches(dsp);
        aspStations = subway.findSwitches(asp);

        subway.plotroute(dsp);
    }
}

vector<pair<pair<double, double>, pair<double, double>>> generateRandomLoc(int n, double lowerLat, double upperLat, double lowerLong, double upperLong) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<pair<pair<double, double>, pair<double, double>>> result;
    uniform_real_distribution<double> LatUnif(lowerLat, upperLat);
    uniform_real_distribution<double> LongUnif(lowerLong, upperLong);
    default_random_engine r(seed);

    for (int i = 0; i < n; i++) {
        double startlat = LatUnif(r);
        double startlong = LongUnif(r);

        double destlat = LatUnif(r);
        double destlong = LongUnif(r);

        result.push_back(make_pair(make_pair(startlat, startlong), make_pair(destlat, destlong)));
    }

    return result;
}

/*pair<double, double> MainProgram::getElapsedTime(int src, int dest){
    auto startD = std::chrono::system_clock::now();
        vector<int> dsp = subway.dijkstra(src, dest);
    auto endD = std::chrono::system_clock::now();

    auto startA = std::chrono::system_clock::now();
        vector<int> asp = subway.aStar(src, dest);
    auto endA = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_secondsD = endD-startD;
    std::chrono::duration<double> elapsed_secondsA = endA-startA;

    return make_pair(elapsed_secondsD.count(), elapsed_secondsA.count());
}*/


void MainProgram::getLongLat(){
    this->close();
    randlonglats = generateRandomLoc(100000, 40.561627, 40.917625, -74.045376, -73.740905);

    for (auto i : randlonglats){
        int src = subway.findClosestStation(make_pair(i.first.first, i.first.second));
        int dest = subway.findClosestStation(make_pair(i.second.first, i.second.second));

        vector<int> dsp = subway.dijkstra(src, dest);
        vector<int> asp = subway.aStar(src, dest);

        totalTimeSecsDijkstras = totalTimeSecsDijkstras + subway.dTime;
        totalTimeSecsAstar = totalTimeSecsAstar + subway.aTime;
    }
    testProgram = true;
}
