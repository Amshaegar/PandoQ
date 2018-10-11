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

    connect(this,               SIGNAL( getIOFormats() ),                           pandocThreadWorker,   SLOT( GetIOFormats())             );
    connect(pandocThreadWorker, SIGNAL( InputFormatsPandocMessage(QStringList)),    this,                 SLOT( inputFormats(QStringList))  );
    connect(pandocThreadWorker, SIGNAL( OutputFormatsPandocMessage(QStringList)),   this,                 SLOT( outputFormats(QStringList)) );

    connect(pandocThreadWorker, SIGNAL( ErrorHappened(QString) ),   this,   SLOT( pandocThreadErrorHandler(QString))   );

    emit getIOFormats();
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
    QString aboutPandoQText =tr( "PandoQ is the Qt GUI frontend for Pandoc written by using C++ language.\n\n" \
                                 "This is free software, and you are welcome to redistribute it under certain conditions.\n\n" \
                                 "This program comes with ABSOLUTELY NO WARRANTY.\n\n"\
                                 "See the GNU General Public License for more details.\n\n" \
                                 "Copyright 2015,2018 Maxim Fedotov (fedotovmo@gmail.com)");

    QMessageBox::information(this,
                             tr("About PandoQ"),
                             aboutPandoQText,
                             QMessageBox::Ok
                             );
}

/* IOFormats section */
void MainWindow::inputFormats(QStringList inputFormats)
{
    ui->FromTypeComboBox->insertItems(0,inputFormats);
}

void MainWindow::outputFormats(QStringList outputFormats)
{
    ui->ToTypeComboBox->insertItems(0,outputFormats);
}

void MainWindow::pandocThreadErrorHandler(QString errorMessage)
{
    QMessageBox::warning(this,
                         tr("Error happened!"),
                         errorMessage,
                         QMessageBox::Ok
                         );
}
