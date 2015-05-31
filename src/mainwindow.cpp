#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout_Qt, SIGNAL(triggered()),    qApp,   SLOT(aboutQt()) );
    connect(ui->actionExit,     SIGNAL(triggered()),    qApp,   SLOT(quit())    );
}

MainWindow::~MainWindow()
{
    delete ui;
}
