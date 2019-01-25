#include <QApplication>
#include <QGridLayout>
#include <QDebug>

#include "bossthread.h"
#include "displaymandel.h"
#include "workerthread.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int size=1000;
    if(argc != 3)
    {
        return EXIT_FAILURE;
    }
    int M = atoi(argv[1]); //nbr bloc
    int N = atoi(argv[2]); //nbr de thread

    if(M < N) {
        return EXIT_FAILURE;
    }

    QColor* colorTab[size];
    for (int i=0;i<size;i++)
        colorTab[i]=new QColor[size];

    QTime myTimer;
    myTimer.start();

    BossThread::semMain.acquire();
    BossThread* mainTh = new BossThread(colorTab,size,N,M);

    mainTh->start();

    BossThread::semMain.acquire();
    BossThread::semMain.release();

    int nMilliseconds = myTimer.elapsed();
    qDebug()<<"Cal in:"<<nMilliseconds;

    DisplayMandel* displayMander = new DisplayMandel(colorTab,0,0,size,size);

    QSize windowsSize(size,size);
    displayMander->resize(windowsSize);
    displayMander->show();

    QMessageBox msgTime;
    msgTime.setText(QString("temps : %1ms").arg(nMilliseconds));
    msgTime.show();



    return app.exec();
}
