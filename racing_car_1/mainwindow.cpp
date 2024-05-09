#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

/*
0 => init 遊戲被開啟
1 => playing 
2 => pause 
3 => timeout 
4 => die 
*/

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game_status = 0;

    //移動背景
    bg_pos = 0;
    object_timer = new QTimer(this);                                         //建立計時器
    connect(object_timer, SIGNAL(timeout()), this, SLOT(update_objects()));  //計時器與update_objects連結
    object_timer->start(10);

    // 更新時間
    time = 30;
    clock_timer = new QTimer(this);                                         // 建立計時器
    connect(clock_timer, SIGNAL(timeout()), this, SLOT(update_time()));     // 計時器與update_time連結
    clock_timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_objects()
{
    bg_pos -= 1;
    ui->background->setGeometry(QRect(bg_pos, 0, 4800, 512));   //背景位置

    if(bg_pos == -32){
        bg_pos = 0;
    }
}

void MainWindow::update_time()
{
    time -= 1;
    ui->lcd_clock->display(time);

    if(time == 0){
        game_status = 3;
        game_stop();
    }
}

void MainWindow::game_stop()
{
    object_timer->stop();
    clock_timer->stop();
}