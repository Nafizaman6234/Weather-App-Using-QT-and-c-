#include "mainwindow.h"

#include <QApplication>
#include<QLabel>
#include <QWidget>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Weather Application");

    QWidget window;
    window.resize(700,750);





    w.show();
    return a.exec();
}
