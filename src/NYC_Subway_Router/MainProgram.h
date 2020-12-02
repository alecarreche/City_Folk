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
#include <iomanip>
#include <random>
#include <QPalette>
#include <QColor>
using namespace std;

class MainProgram : public QMainWindow {
    Q_OBJECT

public:
    explicit MainProgram(QWidget *parent = nullptr);
    double startlong, startlat, destlong, destlat;
    vector<pair<double, double>> randlonglats;
    QPushButton *randlonglat;
    QPushButton *inlonglat;

public slots:
    void inputLongLat();
    void getLongLat();
};
