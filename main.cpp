#include <QApplication>
#include <QGridLayout>
#include <QDebug>

#include "mainthread.h"
#include "displaymandel.h"
#include "workerthread.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    int size=1000;
//    if(argc < 2)
//    {
//        return EXIT_FAILURE;
//    }
    int N = 1000; //nbr de thread
    int M = 1000000; //nbr bloc

    if(M < N) {
        return EXIT_FAILURE;
    }


    QColor* colorTab[size];
    for (int i=0;i<size;i++)
        colorTab[i]=new QColor[size];

    QTime myTimer;
    myTimer.start();

    MainThread* mainTh = new MainThread(colorTab,size,N,M);

    mainTh->run();

    while (!mainTh->isFinish) {
        QThread::sleep(1);
    }

    int nMilliseconds = myTimer.elapsed();
    qDebug()<<"Cal in:"<<nMilliseconds;

    DisplayMandel* displayMander = new DisplayMandel(colorTab,0,0,size,size);
    QSize windowsSize(size,size);
    qDebug() << "aftersize";
    displayMander->resize(windowsSize);
    qDebug() << "resize";
    displayMander->show();
    qDebug() << "show";

    return app.exec();
}
