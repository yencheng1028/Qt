#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDoubleValidator* double_validator = new QDoubleValidator();
    ui->lineEdit_height->setValidator(double_validator);
    ui->lineEdit_weight->setValidator(double_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_calc_clicked()
{
    bool check;
    QString result;

    height = ui->lineEdit_height->text().toDouble(&check);
    if(!check) {
        result = "輸入錯誤";
        ui->label_result->setText(result);
        return;
    }

    weight = ui->lineEdit_weight->text().toDouble(&check);
    if(!check) {
        result = "輸入錯誤";
        ui->label_result->setText(result);
        return;
    }

    double bmi_value = weight / ( (height/100) * (height/100) );

    result ="結果: " +QString::number(bmi_value);

    result += "  您的體位: ";
    if(bmi_value < 18.5)
        result += "過輕";
    else if(bmi_value < 24)
        result += "正常";
    else if(bmi_value < 27)
        result += "過重";
    else if(bmi_value < 30)
        result += "輕度肥胖";
    else if(bmi_value < 35)
        result += "中度肥胖";
    else
        result += "重度肥胖";

    ui->label_result->setText(result);
}




