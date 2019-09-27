#include "myqlabel.h"
extern int mouse_row;
myqlabel::myqlabel(QWidget *parent) :
QLabel(parent)
{

}
void myqlabel::paintEvent(QPaintEvent *evt)
{
   // qDebug()<<"??????\n";
    QLabel::paintEvent(evt);
    QPainter painter(this);
    if(FLAG)
    {
     int nx=1;
     if(posy)nx=posy*10-1;
    // qDebug()<<"lalalallala"<<mouse_row<<"\n";
     painter.drawLine(QPointF(nx,0), QPointF(nx,30));
    }
    if(l<=r&&r)
    {
        QPen pen;
        pen.setColor(QColor(255,246,71,80));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.setBrush(QBrush(QColor(255,246,71,80),Qt::SolidPattern));
        painter.drawRect(l*10,0,(r-l)*10,30);
    }
}
