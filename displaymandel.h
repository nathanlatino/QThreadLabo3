#ifndef DISPLAYMANDEL_H
#define DISPLAYMANDEL_H

#include <QtWidgets>
#include <QPoint>
#include <QtCore>

class DisplayMandel : public QWidget
{
public:
    DisplayMandel(QColor** colorTab,int widthStart,int heightStart,int widthEnd,int heightEnd);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor** colorTab;
    int widthStart;
    int widthEnd;

    int heightStart;
    int heightEnd;
};

#endif // DISPLAYMANDEL_H
