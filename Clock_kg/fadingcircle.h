#ifndef FADINGCIRCLe_H
#define FADINGCIRCLe_H
#include <QPainter>
#include <QMessageBox>
#include "matrix.h"


class FadingCircle
{
    QPolygonF circle; //if it was QPolygon with QPoint's there will be warped circle like coma
    qreal radius;
    QColor c;
    QPointF centerPoint;
    unsigned countPoints;
    bool NO_VISIBLE;

    void moveByVector(QPointF delta); //moves polygon without its center
public:
    FadingCircle(qreal radius);

    bool isNoVisible();

    qreal getRadius();
    void setCenter(qreal cx, qreal cy);

    QPointF center();

    void setOpacity(int alpha);
    int opacity();
    void draw(QPainter* painter, QColor c);

    void scale(qreal k, QPointF O);
    void fade();

    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
};


#endif // FADINGCIRCLE_H
