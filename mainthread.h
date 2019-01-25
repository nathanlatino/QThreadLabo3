#pragma once
#include "workerthread.h"
#include <QPoint>
#include <QRect>
#include <QColor>

class MainThread
{
public:
    MainThread(QColor**,int,int,int);
    void run();
    static bool isFinish;
private :
    QPoint perfectRect(int);
    QRect* rectScene;
    QColor** colorTab;
    int nbThread, nbColumn,nbRow;
    QList<WorkerThread*> tabThreads;
};
