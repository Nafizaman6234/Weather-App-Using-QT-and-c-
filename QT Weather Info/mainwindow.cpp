#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();
    SecondWindow secondwindow;
    secondwindow.setModal(true);
    secondwindow.exec();
}

