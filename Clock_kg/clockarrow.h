#ifndef CLOCKARROW_H
#define CLOCKARROW_H
#include <QPainter>
#include "matrix.h"

class ClockArrow
{
private:
    //typedef long double t_base;
    QPolygonF arrow;
    qreal anglePerSec;

    QColor outline, color;
public:
    void build(QPointF p1,
                    QPointF p2,
                    QPointF p3,
                    QPointF p4,
                    qreal anglePerSec, QColor outline, QColor color);
   void build(vector<QPointF> p, qreal anglePerSec, QColor outline, QColor color);


    ClockArrow();
    ClockArrow(QPointF p1,
                         QPointF p2,
                         QPointF p3,
                         QPointF p4,
                         qreal anglePerSec, QColor outline, QColor color);
    ClockArrow(vector<QPointF> p, qreal anglePerSec, QColor outline, QColor color);

    qreal getRotAngle();
    QPolygonF getPolygon();

    void setColors(QColor outline, QColor color);
    void setWidth(qreal width);
    void setHeight(qreal height);

    qreal width(); qreal height();

    void draw(QPainter* painter);

    void moveByBottom(QPointF lLow, QPointF rLow);
    void moveByTop(QPointF lTop, QPointF rTop);

    void rotate(QPointF O = QPointF(0, 0));//A shape will rotate around O-point

};


#endif // CLOCKARROW_H
