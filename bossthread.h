#pragma once
#include "workerthread.h"
#include <QPoint>
#include <QRect>
#include <QColor>

class BossThread : public QThread
{
public:
    BossThread(QColor**,int,int,int);
    void run();
    static QSemaphore semMain;
    static QSemaphore* semThreadWorker;
private :
    QMutex* mLock;
    QPoint perfectRect(int);
    QRect* rectScene;
    QColor** colorTab;
    int nbThread, nbColumn,nbRow;
    QList<WorkerThread*> tabThreads;
};
