#include "mainthread.h"

bool MainThread::isFinish = false;

MainThread::MainThread(QColor** _colorTab, int size, int _nbThread, int _nbBloc) {
    colorTab = _colorTab;
    rectScene = new QRect(0,0,size,size);
    nbThread = _nbThread;
    nbRow = perfectRect(_nbBloc).x();
    nbColumn = perfectRect(_nbBloc).y();
    isFinish = false;
}

QPoint MainThread::perfectRect(int nbBloc) {
    for(int i = sqrt(nbBloc); i > 1; i--){
        if(nbBloc % i  == 0) {
            return QPoint(nbBloc/i,i);
        }
    }
    return QPoint(nbBloc, 1);
}

void MainThread::run() {
    int activedThread = 0;
    int blocWidth = rectScene->width()/nbColumn;
    int blocHeight = rectScene->height()/nbRow;
    int lastRow = 0;
    int lastColumn = 0;
    for(int j = 0; j < nbRow && activedThread < nbThread; j++) {
        for(int i = 0; i < nbColumn && activedThread < nbThread; i++) {
            tabThreads.append(new WorkerThread(activedThread+1,colorTab,rectScene->width(),rectScene->height(),i*blocWidth,j*blocHeight,(i+1)*blocWidth,(j+1)*blocHeight));
            tabThreads[activedThread]->start();
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
                    w->update(lastColumn*blocWidth, lastRow*blocHeight, (lastColumn+1)*blocWidth, (lastRow+1)*blocHeight);
                    w->start();
                    activedThread++;
                }

            }
        }
    foreach (WorkerThread* w, tabThreads) {
        //while(!w->isFinished()){}
        w->wait();
    }

    isFinish=true;
}
