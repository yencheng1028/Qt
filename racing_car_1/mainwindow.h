#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {

class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void keyPressEvent(QKeyEvent* );

    private slots:
        void update_objects();  //移動物件
        void update_time();

        void on_button_start_game_clicked();

    private:
        Ui::MainWindow *ui;

        int game_status;
        int bg_pos;             //背景水平位置
        int time;
        int car_pos;
        int car_direction;
        float car_distance;

        QTimer *object_timer;   //移動計時器
        QTimer *clock_timer;

        void game_start();
        void game_pause();
        void game_stop();
        void move_car();
};

#endif // MAINWINDOW_H
