#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AboutPandocProcess = new QProcess(this);
    connect(AboutPandocProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ),    this,   SLOT( AboutPandocMessageBox( int, QProcess::ExitStatus ) )  );
    connect(AboutPandocProcess, SIGNAL( error( QProcess::ProcessError )  ),         this,   SLOT( AboutPandocProcessError(QProcess::ProcessError) )     );

    connect(ui->actionExit,         SIGNAL( triggered() ),    qApp,   SLOT( quit()                      )   );
    connect(ui->actionAbout_Pandoc, SIGNAL( triggered() ),    this,   SLOT( AboutPandocProcessStart()   )   );
    connect(ui->actionAbout_Qt,     SIGNAL( triggered() ),    qApp,   SLOT( aboutQt()                   )   );

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* About Pandoc Section */

void MainWindow::AboutPandocProcessStart()
{
    QStringList arg;
    arg << "--version";
    AboutPandocProcess->start( "pandoc", arg );
}

void MainWindow::AboutPandocProcessError( QProcess::ProcessError Error )
{
    if ( Error == QProcess::FailedToStart )
    {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage("Can not start Pandoc proccess. Check the pandoc software availability.");
    }
}

void MainWindow::AboutPandocMessageBox( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage("Pandoc crashed.");
    }
    else if (ExitCode != 0)
    {
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage("Pandoc showing version information failed.");
    }

    QMessageBox::information(this,
                             tr("About Pandoc"),
                             AboutPandocProcess->readAllStandardOutput().data(),
                             QMessageBox::Ok
                             );


}
