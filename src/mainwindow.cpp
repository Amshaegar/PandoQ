#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout_Qt, SIGNAL(triggered()),    qApp,   SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
