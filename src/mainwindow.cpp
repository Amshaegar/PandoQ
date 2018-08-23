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

    PandocThread *pandocThreadWorker = new PandocThread;
    pandocThreadWorker->moveToThread(&pandocThreadThread);
    connect(&pandocThreadThread, &QThread::finished, pandocThreadWorker, &QObject::deleteLater);
    pandocThreadThread.start();

    connect(ui->actionExit,         SIGNAL( triggered() ),                 qApp,                 SLOT( quit()               )   );
    connect(ui->actionAbout_Pandoc, SIGNAL( triggered() ),                 pandocThreadWorker,   SLOT( AboutPandoc()        )   );
    connect(pandocThreadWorker,     SIGNAL( AboutPandocMessage(QString) ), this,                 SLOT( aboutPandoc(QString) )   );
    connect(ui->actionAbout_PandoQ, SIGNAL( triggered() ),                 this,                 SLOT( aboutPandoQ()        )   );
    connect(ui->actionAbout_Qt,     SIGNAL( triggered() ),                 qApp,                 SLOT( aboutQt()            )   );
}

MainWindow::~MainWindow()
{
    delete ui;
    pandocThreadThread.quit();
    pandocThreadThread.wait();
}

/* About Section */

void MainWindow::aboutPandoc(QString message)
{
    QMessageBox::information(this,
                             tr("About Pandoc"),
                             message,
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
