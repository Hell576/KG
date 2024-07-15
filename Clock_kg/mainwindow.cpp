#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVector>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int count = 3;
    clockArrows.resize(count);

    circles.resize(12);
        for (int i = 0; i < circles.size(); i++)
            circles[i] = NULL;

    startCount = 0;
    ui->setupUi(this);
    startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Создаём объект-живописец
    //рисуем циферблат
    cface.drawClockFace(&painter, width(), height());


    static bool initialized = 0;

    if (!initialized)
    {
        QPointF center(0.5*width(), 0.5*height());
        //cface.drawClockFace(nullptr, width(), height());
        qreal r3 = 0.5 * cface.getHeight(2);


        qreal toRad = M_PI / 180;

        qreal w[3] = {0.5, 1, 2};
        qreal h[3] = {0.73*r3, r3, 0.6*r3};
        vector <vector<QPointF>> P(3);
         for (vector<QPointF>::size_type i = 0; i < P.size(); i++)
         {
             P[i].resize(4);
             P[i][0] = QPointF(center.x() - w[i], center.y());
             P[i][1] = QPointF(center.x() + w[i], center.y());
             P[i][2] = QPointF(center.x() + w[i], center.y() - h[i]);
             P[i][3] = QPointF(center.x() - w[i], center.y() - h[i]);
         }


        clockArrows[0].build(P[0], 6 * toRad, Qt::red, Qt::red); //секундная
        clockArrows[1].build(P[1], /*0.017*/0.1  * toRad, Qt::blue, Qt::blue); //минутная
        clockArrows[2].build(P[2], 0.008* toRad, Qt::green, Qt::green); //часовая

        initialized = 1;
    }
    //рисуем стрелки
    for (int i = clockArrows.size() - 1; i >= 0; i--)
        clockArrows[i].draw(&painter);

    //рисуем круги
    for (int i = 0; i < circles.size(); i++)
        {
            if (circles[i] != NULL)
            {
                circles[i]->draw(&painter, Qt::red);
            }
        }
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    //rotation of clockarrows
    QPointF center(0.5*width(), 0.5*height());
    for (int i = 0; i < clockArrows.size(); i++)
        clockArrows[i].rotate(center);




    //circle fading control - fadeNBack
    for (int i = 0; i < circles.size(); i++)
        if (circles[i] != NULL)
        {
             if (circles[i]->isNoVisible())
             {
                  delete circles[i];
                  circles[i] = NULL;
             }
             else
                  circles[i]->fade();
        }

    unsigned clock = 5;
    if ((startCount + 1) % clock == 0 &&
            (/*startCount + 1 != 0*/ circles[((startCount + 1) / clock) - 1] == NULL))
          //  || startCount != 0 && circles[])))////
    {
            size_t ck = ((startCount + 1) / clock) - 1;
            circles[ck] = new FadingCircle(25);

            QPointF P1 = QPointF(clockArrows[0].getPolygon()[2].x(),
                                 clockArrows[0].getPolygon()[2].y());

            QPointF P2 = QPointF(clockArrows[0].getPolygon()[3].x(),
                                 clockArrows[0].getPolygon()[3].y());
            QPointF centerP = (P1 + P2) * 0.5;
            circles[ck]->setCenter(centerP.x(), centerP.y());
    }
    startCount = (startCount + 1) % 60;
    repaint();
}
