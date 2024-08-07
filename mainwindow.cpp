#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


double firstNum;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()),this, SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus, SIGNAL(released()),this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percentage, SIGNAL(released()),this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()),this, SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    labelNumber = (ui->label->text() + button->text()).toDouble();

    newLabel = QString::number(labelNumber,'g',15);

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dot_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);
    }

    else if(button->text() == "%"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber*0.01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }
}


void MainWindow::on_pushButton_clear_released()
{
    ui->label->setText("");
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
}


void MainWindow::on_pushButton_equals_released()
{
    double labelNumber, secondNum;

    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        if(secondNum==0){
            QMessageBox::critical(this, "Error", "Division by zero not valid");
            return;
        }
        else{
            labelNumber = firstNum / secondNum;
        }
        ui->pushButton_divide->setChecked(false);
    }
    else{
        labelNumber = firstNum * secondNum;
        ui->pushButton_multiply->setChecked(false);
    }
    QString newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton*)sender();

    button->setChecked(true);

    firstNum = ui->label->text().toDouble();
    ui->label->setText("");
}


void MainWindow::on_pushButton_del_released()
{
    double labelNumber = ui->label->text().toInt()/10;
    QString newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);
}

