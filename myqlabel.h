#ifndef MYQLABEL_H
#define MYQLABEL_H
#include <QLabel>
#include <QEvent>
#include<QPainter>
#include<QDebug>
#include<QPen>
class myqlabel : public QLabel
{
Q_OBJECT
public:
explicit myqlabel(QWidget *parent = 0);
void Getpos(int x,int y)
{
    FLAG=x;
    posy=y;
}
void Getarea(int x,int y)
{
    l=x;
    r=y;

}
protected:
void paintEvent(QPaintEvent *);

public slots:

private:
int FLAG;
int posy;
int l;
int r;
};
#endif // MYQLABEL_H

