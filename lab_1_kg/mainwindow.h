#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0/*nullptr*/);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    qreal angle = 0;
    // Обработчик события перерисовки окна
    void paintEvent(QPaintEvent* event);
    void timerEvent( QTimerEvent* event );
};

#endif // MAINWINDOW_H

