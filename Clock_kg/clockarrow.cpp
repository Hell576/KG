#include "clockarrow.h"
#include <QDebug>
#include <QTextStream>
#include <vector>
#include <iostream>
void ClockArrow::build(QPointF p1,
                       QPointF p2,
                       QPointF p3,
                       QPointF p4,
                       qreal anglePerSec, QColor outline, QColor color)
{
    setColors(outline, color);
    this->anglePerSec = anglePerSec;
    arrow << p1 << p2 << p3 << p4;
}

void ClockArrow::build(vector<QPointF> p, qreal anglePerSec, QColor outline, QColor color)
{
    setColors(outline, color);
    this->anglePerSec = anglePerSec;
    arrow << p[0] << p[1] << p[2] << p[3];
}

ClockArrow::ClockArrow(){}

ClockArrow::ClockArrow(QPointF p1,
                       QPointF p2,
                       QPointF p3,
                       QPointF p4,
                       qreal anglePerSec, QColor outline, QColor color)
{   build(p1, p2, p3, p4, anglePerSec, outline, color); }

ClockArrow::ClockArrow(vector<QPointF> p, qreal anglePerSec, QColor outline, QColor color)
{  build(p, anglePerSec, outline, color); }


qreal ClockArrow::getRotAngle() {return anglePerSec;}

QPolygonF ClockArrow::getPolygon()
{
    return arrow;
}

void ClockArrow::setColors(QColor outline, QColor color) //builer_patt
{ this->outline = outline; this->color = color;}



void ClockArrow::rotate(QPointF O) //A shape will rotate around O-point
{
    //static QPointF previousO(0, 0); ///GLAZE!!!
    static Matrix<qreal> M(3, 3);

  //  bool isChanged = previousO != O;

  //  if (isChanged)
    {
        M = Matrix<qreal>::transferMat(O.x(), O.y()) *
            Matrix<qreal>::rotateMat(anglePerSec) *
            Matrix<qreal>::transferMat(-O.x(), -O.y());
    }

 /*  for (int i = 0; i < 3; i++)
   {
       for (int j = 0; j < 3; j++)
           cout << M[i][j] << "\t";
       cout << endl;
   }*/

    for (int i =0; i < arrow.size(); i++)
        arrow[i]  = Matrix<qreal>::getChangedPointF(arrow[i], &M);

}

void ClockArrow::draw(QPainter* painter)
{
    painter->setPen(outline);
    painter->setBrush(color);
    painter->drawPolygon(arrow);
}
