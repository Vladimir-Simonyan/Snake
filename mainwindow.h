#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *elem[16][16];

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Update();
    void Step();
    void CreateApple();
    void Pause();
    void Plus();
    void End();
    void Up();
    void Down();
    void Left();
    void Right();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *tmr;

};

#endif // MAINWINDOW_H
