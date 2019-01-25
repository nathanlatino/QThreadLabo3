#include "workerthread.h"
#include "bossthread.h"

WorkerThread::WorkerThread(int _id,QColor** _colorTab,int _width,int _height,int _widthStart,int _heightStart,int _widthEnd,int _heightEnd)
{
    id = _id;
    colorTab = _colorTab;
    width = _width;
    height = _height;
    widthStart = _widthStart;
    widthEnd = _widthEnd;
    heightStart = _heightStart;
    heightEnd = _heightEnd;
}

int WorkerThread::value (int x, int y)  {
    complex<float> point((float)x/width-1.5, (float)y/height-0.5);
    complex<float> z(0, 0);
    int nb_iter = 0;
    while (abs (z) < 2 && nb_iter <= 20) {
        z = z * z + point;
        nb_iter++;
    }
    if (nb_iter < 20)
       return (255*nb_iter)/20;
    else
       return 0;
}

void WorkerThread::update(int _widthStart,int _heightStart,int _widthEnd,int _heightEnd)
{
    widthStart = _widthStart;
    heightStart = _heightStart;
    widthEnd = _widthEnd;
    heightEnd = _heightEnd;
}

void WorkerThread::run()
{
    qDebug()<<"Thread:"<<id<<" start";
    for (int i = widthStart; i < widthEnd; ++i) {
        for (int j = heightStart; j < heightEnd; ++j) {
            colorTab[i][j]=QColor(value(i,j),(id%2)*20,(id%3)*50);
        }
    }
    qDebug()<<"Thread:"<<id<<" end";
    BossThread::semThreadWorker->release();
}
