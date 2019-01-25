#pragma once

//#include "bossthread.h"
#include <QThread>
#include <QDebug>
#include <QColor>
#include <QPoint>
#include <QtCore>
#include <complex>


using namespace std;

class WorkerThread: public QThread
{
    Q_OBJECT
public:
    WorkerThread(int _id,QColor** _colorTab,int _width,int _height,int _widthStart,int _heightStart,int _widthEnd,int _heightEnd);
    int value(int x, int y);
    void update(int, int, int, int);
    void run();

private:
    int id;
    QColor** colorTab;
    int width;
    int height;

    int widthStart;
    int widthEnd;

    int heightStart;
    int heightEnd;
};
