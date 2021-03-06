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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QFileDialog>
#include "pandocthread.hpp"

namespace Ui {
class MainWindow;
}

/** Main window class.
  */

#include "settings.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Settings    settingsWidget;

    QThread     pandocThreadThread; /*< Thread that works with Pandoc CLI. All communication with it made by signal/slots.*/

    void changeEvent(QEvent *event); /*< Reimplemented for changing the language of the application.*/

private slots:

    /* About Section */
    void aboutPandoQ(); /*< Slot that shows information about PandoQ.*/
    void aboutPandoc(QString message); /*< Slot that shows information about Pandoc.*/

    /* IOFormats section */
    void inputFormats(QStringList inputFormats);
    void outputFormats(QStringList outputFormats);

    void converted();

    void pandocThreadErrorHandler(QString errorMessage); /*< Slot that handle errors sent by Pandoc thread.*/

    void on_ConvertTextPushButton_clicked();

    void on_ChooseFileFromPushButton_clicked();

    void on_ChooseFileToPushButton_clicked();

    void on_ConvertFilePushButton_clicked();

    void on_actionConfigure_PandoQ_triggered();

signals:
    void getIOFormats();
    void Convert(QString inputFormat,
                 QString outputFormat,
                 QString inputFile,
                 QString outputFile);
};

#endif // MAINWINDOW_H
