/*
 * PandoQ is the Qt GUI frontend for Pandoc written by using C++ language.
 *
 * Copyright 2015,2018 Maxim Fedotov  (fedotovmo@gmail.com)
 *
 * This file is part of PandoQ.
 *
 * PandoQ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PandoQ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PandoQ.  If not, see <https://www.gnu.org/licenses/>.
 */

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
    connect(ui->actionAbout_PandoQ, SIGNAL( triggered() ),    this,   SLOT( aboutPandoQ()               )   );
    connect(ui->actionAbout_Qt,     SIGNAL( triggered() ),    qApp,   SLOT( aboutQt()                   )   );

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* About Section */

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

void MainWindow::aboutPandoQ()
{
    QString aboutPandoQText =tr( "PandoQ is the Qt GUI frontend for Pandoc written by using C++ language.\n" \
                                 "Copyright 2015,2018 Maxim Fedotov (fedotovmo@gmail.com)\n" \
                                 "This is free software, and you are welcome to redistribute it under certain conditions. \n"\
                                 "This program comes with ABSOLUTELY NO WARRANTY.\n" \
                                 "See the GNU General Public License for more details.\n");

    QMessageBox::information(this,
                             tr("About Pandoc"),
                             aboutPandoQText,
                             QMessageBox::Ok
                             );
}
