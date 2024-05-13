#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

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
    //clock_timer->start(1000);
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

    if(game_status==1){
        car_distance += 1;
        ui->label_distance->setText("行駛距離: " + QString::number(car_distance, 'f',0)+ "公尺");
        move_car();
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

void MainWindow::on_button_start_game_clicked()
{
  game_start();
}

void MainWindow::game_start()
{
    game_status = 1;
    ui->label_title->setVisible(false);
    ui->button_start_game->setVisible(false);
    clock_timer->start(1000);
    time = 30;
    ui->lcd_clock->display(time);

    car_pos = 220;
    car_distance = 0;
    car_direction = 0;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        car_direction = -1;
        qDebug()<<"up";
        break;

    case Qt::Key_Down:
        car_direction = 1;
        qDebug()<<"down";
        break;
    }
}

void MainWindow::move_car()
{
    int car_new_pos = car_pos + car_direction;

    if((car_new_pos) >= 30 && (car_new_pos) <= 410){

        car_pos = car_new_pos;
        ui->car->setGeometry(QRect(10, car_pos, 237, 71));

    } else {
        game_status = 4;
        game_stop();
    }
}
