#include "MainProgram.h"

MainProgram::MainProgram(QWidget *parent) : QMainWindow(parent){
    this->setFixedSize(310, 120);
    this->setWindowTitle("Menu Options for Calculating Shortest Path");

    randlonglat = new QPushButton("Generate Random Longitudes and Latitudes", this);
    inlonglat = new QPushButton("Enter Starting and Destination", this);

    randlonglat->setGeometry(5, 10, 300, 50);
    inlonglat->setGeometry(5,60, 300, 50);

    QObject::connect(randlonglat, SIGNAL(released()), this, SLOT(getLongLat()));
    QObject::connect(inlonglat, SIGNAL(released()), this, SLOT(inputLongLat()));
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

    temp1 = QInputDialog::getDouble(&win, "Input", "Starting Longitude (bounds: -74.266461, -73.740905)", 0, -74.266461,
                                    -73.740905, 6, &pressed1, Qt::WindowFlags(), 1);
    if (pressed1 == true) {
        temp2 = QInputDialog::getDouble(&win, "Input", "Starting Latitude (bounds: 40.498264, 40.917625)", 0, 40.498264,
                                        40.917625, 6, &pressed2, Qt::WindowFlags(), 1);
        if (pressed2 == true) {
            temp3 = QInputDialog::getDouble(&win, "Input", "Destination Longitude (bounds: -74.266461, -73.740905)", 0,
                                            -74.266461, -73.740905, 6, &pressed3, Qt::WindowFlags(), 1);
            if (pressed3 == true) {
                temp4 = QInputDialog::getDouble(&win, "Input", "Destination Latitude (bounds: 40.498264, 40.917625)", 0,
                                                40.498264, 40.917625, 6, &pressed4, Qt::WindowFlags(), 1);
            }
        }
    }

    win.show();

    if (pressed1 == false || pressed2 == false || pressed3 == false || pressed4 == false) {
        this->show();
    }

    if (pressed1 == true && pressed2 == true && pressed3 == true && pressed4 == true) {
        startlong = temp1;
        startlat = temp2;
        destlong = temp3;
        destlat = temp4;

        int src = subway.findClosestStation(make_pair(startlat, startlong));
        int dest = subway.findClosestStation(make_pair(destlat, destlong));
        vector<int> dsp = subway.dijkstra(src, dest);
        vector<int> asp = subway.aStar(src, dest);

        string dspStations = "";
        for (int i = 0; i < dsp.size() - 1; i++) {
            dspStations = dspStations + to_string(dsp[i]) + "->";
        }
        dspStations = dspStations + to_string(dsp[dsp.size()-1]);

        string aspStations = "";
        for (int i = 0; i < asp.size() - 1; i++) {
            aspStations = aspStations + to_string(asp[i]) + "->";
        }
        aspStations = aspStations + to_string(asp[asp.size()-1]);

        cout << "Dijkstra's Algorithm: " << dspStations << endl;
        cout << "A* Algorithm: " << aspStations << endl;
    }
}

vector<pair<pair<double, double>, pair<double, double>>> generateRandomLoc(int n, double lowerLat, double upperLat, double lowerLong, double upperLong) {

    vector<pair<pair<double, double>, pair<double, double>>> result;
    uniform_real_distribution<double> LatUnif(lowerLat, upperLat);
    uniform_real_distribution<double> LongUnif(lowerLong, upperLong);
    default_random_engine r;

    for (int i = 0; i < n; i++) {
        double startlat = LatUnif(r);
        double startlong = LongUnif(r);

        double destlat = LatUnif(r);
        double destlong = LongUnif(r);

        result.push_back(make_pair(make_pair(startlat, startlong), make_pair(destlat, destlong)));
    }

    return result;
}

void MainProgram::getLongLat(){
    randlonglats = generateRandomLoc(10, 40.498264, 40.917625, -74.266461, -73.740905);

    for (auto i : randlonglats){
        int src = subway.findClosestStation(make_pair(startlat, startlong));
        int dest = subway.findClosestStation(make_pair(destlat, destlong));

        vector<int> dsp = subway.dijkstra(src, dest);
        vector<int> asp = subway.aStar(src, dest);
    }
}
