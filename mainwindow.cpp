//   Copyright © 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com | GPL v3.0   //


#include <QtGui>
#include <QWidget>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int N = 16, M = 16;
int apple[2];
int snake[100][2];
int snake_len;
int snake_dir;
bool pause = false;
bool ended = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
          elem[i][j] = new QWidget(this);
          elem[i][j]->setGeometry(5+j*28,5+i*28,26,26);
          elem[i][j]->setStyleSheet("background-color:lightgray;");
        }
    }

    tmr = new QTimer;
    tmr->setInterval(350);
    connect(tmr, SIGNAL(timeout()), this, SLOT(Step()));
    tmr->start();

    MainWindow::End();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_8 || event->key() == Qt::Key_W) {MainWindow::Up();}
    else if(event->key() == Qt::Key_2 || event->key() == Qt::Key_S) {MainWindow::Down();}
    else if(event->key() == Qt::Key_6 || event->key() == Qt::Key_D) {MainWindow::Right();}
    else if(event->key() == Qt::Key_4 || event->key() == Qt::Key_A) {MainWindow::Left();}
    else if(event->key() == Qt::Key_P) {MainWindow::Pause();}
    QMainWindow::keyPressEvent(event);
}

void MainWindow::Step() {
    if(!pause) {
        if(snake[0][0] == apple[0] && snake[0][1] == apple[1]) MainWindow::Plus();
        if(snake_dir == 0) {
            if (snake[0][0]+1 > N-1) { MainWindow::End(); }
            else{
                for(int i = snake_len-1; i > 0; i--) {
                    snake[i][0] = snake[i-1][0];
                    snake[i][1] = snake[i-1][1];
                }
                snake[0][0] = snake[0][0]+1;
            }
        }
        else if(snake_dir == 1) {
            if (snake[0][1]-1 < 0) { MainWindow::End(); }
            else{
                for(int i = snake_len-1; i > 0; i--) {
                    snake[i][0] = snake[i-1][0];
                    snake[i][1] = snake[i-1][1];
                }
                snake[0][1] = snake[0][1]-1;
            }
        }
        else if(snake_dir == 2) {
            if (snake[0][0]-1 < 0) { MainWindow::End(); }
            else{
                for(int i = snake_len-1; i > 0; i--) {
                    snake[i][0] = snake[i-1][0];
                    snake[i][1] = snake[i-1][1];
                }
                snake[0][0] = snake[0][0]-1;
            }
        }
        else if(snake_dir == 3) {
            if (snake[0][1]+1 > M-1) { MainWindow::End(); }
            else{
                for(int i = snake_len-1; i > 0; i--) {
                    snake[i][0] = snake[i-1][0];
                    snake[i][1] = snake[i-1][1];
                }
                snake[0][1] = snake[0][1]+1;
            }
        }
        for (int j = 1; j < snake_len; j++)
            if (snake[0][0] == snake[j][0] && snake[0][1] == snake[j][1]) {
                MainWindow::End();
                break;
            }
        MainWindow::Update();
    }
}

void MainWindow::Update() {
    if(ended) {
        ended = false;
        tmr->setInterval(350);
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
              elem[i][j]->setStyleSheet("background-color:red;");
            }
        }
    }
    else {
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
              elem[i][j]->setStyleSheet("background-color:lightgray;");
            }
        }
        elem[apple[0]][apple[1]]->setStyleSheet("background-color:orange;");
        for(int i = 0; i < snake_len; i++) {
            elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-color:black;");
        }
    }
}

void MainWindow::CreateApple() {
    while(true) {
        apple[0] = rand()%N;
        apple[1] = rand()%M;
        bool flag = true;
        for(int i = 0; i < snake_len; i++)
            if(snake[i][0] == apple[0] && snake[i][1] == apple[1]) flag = false;
        if(flag) break;
    }
}

void MainWindow::Pause() {
    pause = !pause;
}

void MainWindow::Plus() {
    MainWindow::CreateApple();
    snake_len++;

    if (snake_len >= 5 && snake_len < 10) tmr->setInterval(250);
    else if (snake_len >= 10 && snake_len < 15) tmr->setInterval(200);
    else if (snake_len >= 15 && snake_len < 20) tmr->setInterval(150);
    else if (snake_len >= 20 && snake_len < 25) tmr->setInterval(100);
    else if (snake_len >= 25) tmr->setInterval(75);
}

void MainWindow::End() {
    ended = true;
    tmr->setInterval(750);
    snake_len = 2;
    snake_dir = 0;
    snake[0][0] = 5;
    snake[0][1] = 7;
    MainWindow::CreateApple();
}

void MainWindow::Up() {
    if(snake_dir != 0) snake_dir = 2;
    if(pause) pause = !pause;
}

void MainWindow::Down() {
    if(snake_dir != 2) snake_dir = 0;
    if(pause) pause = !pause;
}

void MainWindow::Left() {
    if(snake_dir != 3) snake_dir = 1;
    if(pause) pause = !pause;
}

void MainWindow::Right() {
    if(snake_dir != 1) snake_dir = 3;
    if(pause) pause = !pause;
}
