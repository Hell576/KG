#ifndef CLOCKFACE_H
#define CLOCKFACE_H
#include <QPainter>
#include <QDebug>
#include <iostream>
#include "matrix.h"
#include <QLabel>

class ClockFace
{
private:
    static const int n = 4;
    QVector<QRectF> circles4;


    QRectF drawCircle(QPainter* painter, QPointF startP, qreal r, QColor c)
    {
        QRectF Circle(startP.x() - r, startP.y() - r, r*2, r*2);
        if (painter != nullptr)
        {
            painter->setPen(Qt::black);
            painter->setBrush(c);
            painter->drawEllipse(Circle);
        }


        return Circle;
    }
public:
    friend class ClockArrow;

    ClockFace()
    {circles4.resize(n); }

    QVector<QRectF> getCircles()
    {return circles4;}

    qreal getHeight(unsigned circleNum)//The biggest circle is the 1st
    {return circles4[circleNum % n].height();} //count from zero

    void drawClockFace(QPainter* painter, int W, int H)
    {
      QVector<qreal> r(4);

       if (W >= H) // Если ширина окна больше высоты
           r[0] = (H - 20) / 2; // Отступ от краёв - 10 пикселей
       else
           r[0] = (W - 20) / 2;

       // Если размеры окна маленькие, ничего не выводить
       if (W < 30 || H < 30)
        return;

       QPointF center = QPointF(W / 2, H / 2);

       circles4[0] = drawCircle(painter, center, r[0], QColor(51, 151, 255));


       //QTextStream cout(stdout);
       //cout << circles4[0].center().x() << Qt::endl;
       //qDebug() << "circle 0"  << circles4[0].center().x()<< ":"  << circles4[0].center().y() << Qt::endl;


       float d = 10;
       for (int i = 0; i < r.size() - 1; i++)
       {
           r[i+1] = r[i] - d;
           circles4[i+1] = drawCircle(painter, center, r[i+1], QColor(0xFF, 0xFF, 0xFF));

           d += d + 5;
       }

       //risovanie deleniy
       unsigned countNum = 60;
       qreal angle = 360./countNum * (M_PI/180);

       QPointF startP(circles4[3].center().x(), circles4[3].center().y() - 0.5*circles4[2].height());////- circles4[1].height() bug
       QLineF trait(startP, QPointF(startP.x(), startP.y() + 15));

       Matrix<qreal> M(3, 3);
       M = Matrix<qreal>::transferMat(circles4[3].center().x(), circles4[3].center().y()) *
           Matrix<qreal>::rotateMat(angle) *
           Matrix<qreal>::transferMat(-circles4[3].center().x(), -circles4[3].center().y());

       QPointF lastP2 = trait.p2();
       QPointF lastSmallP2 = QPointF(startP.x(), startP.y() + 5);
       painter->setPen(Qt::black);

       QString digits; unsigned count = 1;
       painter->drawText(trait.p1().x(), trait.p1().y() - 2, digits);

       for (int i = 0; i < countNum; i++)
       {
           painter->drawLine(trait);


           trait.setP1(Matrix<qreal>::getChangedPointF(trait.p1(), &M));

           lastP2 = Matrix<qreal>::getChangedPointF(lastP2, &M);
           lastSmallP2 = Matrix<qreal>::getChangedPointF(lastSmallP2, &M);

           if ( (i+1) % 5 != 0)
               trait.setP2(lastSmallP2);
           else
           {
               trait.setP2(lastP2);
               QTextStream(&digits) << count++;
               painter->drawText(trait.p1().x(), trait.p1().y() - 2, digits);
               digits.clear();
           }




       }

    }
};

#endif // CLOCKFACE_H
