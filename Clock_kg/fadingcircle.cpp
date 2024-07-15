#include "fadingcircle.h"
#include <QMessageBox>
#include <QDebug>
#include <QPolygon>

FadingCircle::FadingCircle(qreal radius)
{
   this->countPoints = 32;
   this->radius = radius;
   this->centerPoint = QPointF(0, 0);
   this->NO_VISIBLE = 0;

   Matrix<qreal> rotMat = Matrix<qreal>::transferMat(-centerPoint.x(), -centerPoint.y()) *
                     Matrix<qreal>::rotateMat((360./ this->countPoints)  * (M_PI / 180)) *
                     Matrix<qreal>::transferMat(centerPoint.x(), centerPoint.y());

   QPointF lastP(centerPoint.x(), centerPoint.y() - radius);
   circle.reserve(countPoints);
   for (int i = 0; i < countPoints; i++)//bug i < countPoints - 1
   {
       circle << lastP;
       lastP = Matrix<qreal>::getChangedPointF(lastP, &rotMat);
   }
  // countPoints++;
}

bool FadingCircle::isNoVisible()
{return NO_VISIBLE? 1 : 0;}

qreal FadingCircle::getRadius() {return this->radius;}

void FadingCircle::setCenter(qreal cx, qreal cy)
{
    QPointF delta(QPointF(cx, cy) - this->centerPoint);
   /* if (fabs(delta.x()) < 1 && fabs(delta.y()) < 1) // this vas invented to move back the figure after its scaling
    {
        delta = QPointF(QPointF(cx, cy) - QPointF(circle[0].x(), circle[0].y() + this->radius));
    }*/

    this->centerPoint = QPoint(cx, cy);
    moveByVector(delta);
}

void FadingCircle::moveByVector(QPointF delta) //moves polygon without its center
{
    Matrix<qreal> transMat = Matrix<qreal>::transferMat(delta.x(), delta.y());

   //tranfering poly points
    for (int i = 0; i < this->countPoints; i++)
        circle[i] = Matrix<qreal>::getChangedPointF(circle[i], &transMat);
}

QPointF FadingCircle::center()
{return this->centerPoint;}

void FadingCircle::setOpacity(int alpha)
{
    try{
        c.setAlpha(alpha);
       // if (c.alpha() > 0xff)
       //     throw -1;
    }
    catch (...) {
        QMessageBox err("Wrong Value",
        "\"You set alpha\" value more than 255. It will be recalculated by mod operation",
        QMessageBox::Warning, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        err.exec();
        alpha %= 0xff;
    }
}

int FadingCircle::opacity(){return c.alpha();}

void FadingCircle::draw(QPainter* painter, QColor c)
{
     painter->setPen(c);
     painter->setBrush(c);
     if (this->countPoints == 1) //draw point
     {
       qreal r = 20;
       QRectF point(center().x() - r, center().y() - r, 2*r, 2*r);
       painter->drawEllipse(point);
     }
     else
        painter->drawPolygon(circle);
}



void FadingCircle::scale(qreal k, QPointF O)
{
    this->radius *= k; //vliyalo na circle - nr doljno
    Matrix<qreal> M = Matrix<qreal>::transferMat(-O.x(), -O.y()) *
                      Matrix<qreal>::scalingMat(k, k) *
                      Matrix<qreal>::transferMat(O.x(), O.y());

    //this->centerPoint = Matrix<qreal>::getChangedPoint(centerPoint, &M); //ceter change must not but without him it worked incorrectly
    for (int i = 0; i < circle.size(); i++)
    {
        circle[i] = Matrix<qreal>::getChangedPointF(circle[i], &M);
    }

    moveByVector(QPointF(this->centerPoint - QPointF(circle[0].x(), circle[0].y() + this->radius)));
}

void FadingCircle::fade()
{
    this->scale(0.9, this->center());
    if (this->radius < 2)
    {
        NO_VISIBLE = 1;
    }
}
