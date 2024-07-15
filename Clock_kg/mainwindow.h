#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fadingcircle.h"

#include "clockface.h"
#include "clockarrow.h"
#include "matrix.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ClockFace cface;
    QVector<ClockArrow> clockArrows;

    QVector<FadingCircle*> circles;
    unsigned startCount;

    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
};

#endif // MAINWINDOW_H
