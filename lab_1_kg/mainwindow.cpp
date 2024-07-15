#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startTimer(60);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void drawTriangle(QPainter& painter, QVector <QPointF> p,
                  QColor penColor, QColor brushColor){
    QPolygonF triag(p);
    painter.setPen(penColor);
    painter.setBrush(brushColor);
    painter.drawPolygon(triag);
}

QVector <QPointF> drawTriangle(QPainter& painter, QPointF p1, QPointF p2, QPointF p3,
                  QColor penColor, QColor brushColor){
    QPolygonF triag;
    triag << p1 << p2 << p3;
    painter.setPen(penColor);
    painter.setBrush(brushColor);
    painter.drawPolygon(triag);

    QVector <QPointF> p(3);
    p[0] = p1, p[1] = p2, p[2] = p3;
    return p;
}

/*void resize(unsigned len, double radius, const int wframe, const int hframe)
{
    // Вычисляем радиус окружности
    if (wframe > hframe) // Если ширина окна больше высоты
        radius = (hframe - 20) / 2; // Отступ от краёв - 10 пикселей
    else radius = (wframe - 20) / 2;


    // Если размеры окна маленькие, ничего не выводить
    if (width() < 30 || height() < 30)
    return;
}
*/

/*class CoordsConverter
{
    QRect scr;
    double x1, x2, y1, y2;
public:
    QPoint toScreen(double x, double y)
    {

    }
};
*/

void MainWindow::paintEvent(QPaintEvent* event)
{

    QPainter painter(this); // Создаём объект-живописец
    qreal mainR;


   if (width() >= height()) // Если ширина окна больше высоты
       mainR = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
   else
       mainR = (width() - 20) / 2;

   // Если размеры окна маленькие, ничего не выводить
   if (width() < 30 || height() < 30)
    return;




   QPointF center = QPointF(width() / 2, height() / 2);
   QRectF mainDrawAr(0, 0, width(), height());
   painter.setOpacity(0.0);
   painter.drawEllipse(mainDrawAr);
   painter.setOpacity(1.0);


   unsigned n = 5;
   qreal len =  2 * mainR / 3;



    //DrawCenterRectInC

    QRectF rect = QRectF(mainDrawAr.center().x() -0.5*len, mainDrawAr.center().y(), len, len);
    QColor brown(153, 100, 0);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(brown));
    painter.drawRect(rect);


    //drawFlag

    double middleX = rect.topLeft().x() + 0.5*len;
    QPointF topPoint(middleX, rect.top() - len);
    QLineF straightStick( QPointF(middleX, topPoint.y() + len), topPoint),
          obligueStick(topPoint, rect.topRight());

    painter.setPen(brown);
    painter.drawLine(straightStick);
    painter.drawLine(obligueStick);

    QPointF midEdge( 0.5*(topPoint + (topPoint + QPointF(0, 0.33*len))) - QPointF(0.33*len, 0));
    drawTriangle(painter, topPoint, topPoint + QPointF(0, 0.33*len), midEdge, Qt::black, Qt::red);



    //Triangle color
    QColor yellow(255, 230, 0);


    // drawLeftTriangle
    QVector <QPointF> lTriagPoints(3);
    lTriagPoints = drawTriangle(painter, rect.topLeft(),
                   QPointF(rect.topLeft().x() - len, rect.topLeft().y()), rect.bottomLeft(),
                   Qt::black, yellow);



    //drawRightTriangle
    QVector <QPointF> rTriagPoints(3);
    rTriagPoints = drawTriangle(painter, rect.topRight(),
               QPointF(rect.topRight().x() + len, rect.topRight().y()), rect.bottomRight(),
                  Qt::black, yellow);




    // drawMotorchik(QPainter& ptr, unsigned n, QPointF point, unsigned radius)
    double x0 = 0.5*(lTriagPoints[1].x() + lTriagPoints[2].x()),
           y0 = 0.5*(lTriagPoints[1].y() + lTriagPoints[2].y());

    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::cyan));

    double radius = 0.25*len;
    QRectF drawArea(x0 - radius, y0 - radius, 2*radius, 2*radius);
    int spanAngle = (16*360)/n;
    int startAngle = angle;


    for (unsigned i = 0; i < n; ++i)
    {
        painter.drawPie(drawArea, startAngle, spanAngle);
        startAngle += spanAngle;
    }

}

void MainWindow::timerEvent(QTimerEvent* event)
{
    //painter.rotate(angle);
    angle -= 50;
    repaint();
}

