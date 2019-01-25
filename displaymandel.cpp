#include "displaymandel.h"

DisplayMandel::DisplayMandel(QColor** _colorTab,int _widthStart,int _heightStart,int _widthEnd,int _heightEnd)
{
    colorTab = _colorTab;
    widthStart = _widthStart;
    widthEnd = _widthEnd;
    heightStart = _heightStart;
    heightEnd = _heightEnd;
}

void DisplayMandel::paintEvent(QPaintEvent*) {
   QPainter painter(this);
    for (int i = widthStart; i < widthEnd; ++i) {
        for (int j = heightStart; j < heightEnd; ++j) {

                painter.setPen(colorTab[i][j]);
                painter.drawPoint(i-widthStart, j-heightStart);
        }
    }
}
