#include "bossthread.h"

QSemaphore BossThread::semMain(1);
QSemaphore* BossThread::semThreadWorker;

BossThread::BossThread(QColor** _colorTab, int size, int _nbThread, int _nbBloc) {
    colorTab = _colorTab;
    rectScene = new QRect(0,0,size,size);
    nbThread = _nbThread;
    semThreadWorker = new QSemaphore(nbThread);
    nbRow = perfectRect(_nbBloc).x();
    nbColumn = perfectRect(_nbBloc).y();
    mLock = new QMutex();
}

QPoint BossThread::perfectRect(int nbBloc) {
    for(int i = sqrt(nbBloc); i > 1; i--){
        if(nbBloc % i  == 0) {
            return QPoint(nbBloc/i,i);
        }
    }
    return QPoint(nbBloc, 1);
}

void BossThread::run() {
    int activedThread = 0;
    int blocWidth = rectScene->width()/nbColumn;
    int blocHeight = rectScene->height()/nbRow;
    int lastRow = 0;
    int lastColumn = 0;
    for(int j = 0; j < nbRow && activedThread < nbThread; j++) {
        for(int i = 0; i < nbColumn && activedThread < nbThread; i++) {
            mLock->lock();
            semThreadWorker->acquire();
            tabThreads.append(new WorkerThread(activedThread+1,colorTab,rectScene->width(),rectScene->height(),i*blocWidth,j*blocHeight,(i+1)*blocWidth,(j+1)*blocHeight));
            tabThreads[activedThread]->start();
            mLock->unlock();
            activedThread++;
            lastColumn = i;

        }
        lastRow = j;
    }


    while(activedThread < nbRow*nbColumn){
            foreach (WorkerThread* w, tabThreads) {
                if(nbColumn*nbRow < activedThread){
                    break;
                }

                if(w->isFinished()){
                    lastColumn++;
                    if(lastColumn >= nbColumn){
                        lastColumn = 0;
                        lastRow++;
                    }
                    mLock->lock();
                    semThreadWorker->acquire();
                    w->update(lastColumn*blocWidth, lastRow*blocHeight, (lastColumn+1)*blocWidth, (lastRow+1)*blocHeight);
                    w->start();

                    activedThread++;
                    mLock->unlock();
                }
            }
        }
    semThreadWorker->acquire(nbThread);
    semThreadWorker->release(nbThread);

    semMain.release();
}
