#include <iostream>
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    try
    {
        w.show();
    }
    catch(...)
    {
        std::cout<<"Unhandled exception.";
    }


    return a.exec();
}
