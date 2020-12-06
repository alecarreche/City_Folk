#include "MainProgram.h"

// Constructor for MainProgram
MainProgram::MainProgram(QWidget *parent) : QMainWindow(parent){
    //sets size of window and window title
    this->setFixedSize(380, 120);
    this->setWindowTitle("Menu Options for Calculating Shortest Path");

    //creates the two buttons to either generate random longs and lats or input random longs and lats
    randlonglat = new QPushButton("Generate Random Longitudes and Latitudes", this);
    inlonglat = new QPushButton("Enter Starting and Destination", this);

    //sets size and location of buttons
    randlonglat->setGeometry(5, 10, 370, 50);
    inlonglat->setGeometry(5,60, 370, 50);

    //connects window buttons to functions
    QObject::connect(randlonglat, SIGNAL(clicked()), this, SLOT(getLongLat()));
    QObject::connect(inlonglat, SIGNAL(clicked()), this, SLOT(inputLongLat()));
}

// Function used when input button is pressed
void MainProgram::inputLongLat() {
    //hides initial menu
    this->hide();

    //creates new window
    QWidget win;
    win.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, win.size(), qApp->desktop()->availableGeometry()));

    double temp1, temp2, temp3, temp4;

    bool pressed1 = false;
    bool pressed2 = false;
    bool pressed3 = false;
    bool pressed4 = false;

    // if at any point in accepting the inputs, the user presses cancel, we do not continue accepting the remainder of inputs
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

    // if user pressed cancel at any point we show the menu again
    if (pressed1 == false || pressed2 == false || pressed3 == false || pressed4 == false) {
        this->show();
    }

    // else we comput the shortest path using both algorithms and plot the route
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

// function to randomly generate the 100,000 test data points
vector<pair<pair<double, double>, pair<double, double>>> generateRandomLoc(double lowerLat, double upperLat, double lowerLong, double upperLong) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<pair<pair<double, double>, pair<double, double>>> result;
    uniform_real_distribution<double> LatUnif(lowerLat, upperLat);
    uniform_real_distribution<double> LongUnif(lowerLong, upperLong);
    default_random_engine r(seed);

    for (int i = 0; i < 100000; i++) {
        double startlat = LatUnif(r);
        double startlong = LongUnif(r);

        double destlat = LatUnif(r);
        double destlong = LongUnif(r);

        result.push_back(make_pair(make_pair(startlat, startlong), make_pair(destlat, destlong)));
    }

    return result;
}

// calls the function that generates random 100,000 datapoints and computes dijkstras and A* and gets the time it takes
void MainProgram::getLongLat(){
    this->close();
    vector<pair<pair<double, double>, pair<double, double>>> randlonglats = generateRandomLoc(40.561627, 40.917625, -74.045376, -73.740905);

    for (auto i : randlonglats){
        // finds closest station
        int src = subway.findClosestStation(make_pair(i.first.first, i.first.second));
        int dest = subway.findClosestStation(make_pair(i.second.first, i.second.second));

        //starts clock, calculates shortest path, ends clock, calculates time
        auto startD = std::chrono::system_clock::now();
            vector<int> dsp = subway.dijkstra(src, dest);
        auto endD = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_secondsD = endD-startD;

        auto startA = std::chrono::system_clock::now();
            vector<int> asp = subway.aStar(src, dest);
        auto endA = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_secondsA = endA-startA;

        // summing up times across all the iterations
        totalTimeSecsDijkstras = totalTimeSecsDijkstras + elapsed_secondsD.count();
        totalTimeSecsAstar = totalTimeSecsAstar + elapsed_secondsA.count();
    }
    testProgram = true;
}
