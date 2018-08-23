/*
 * Copyright 2015,2018 Maxim Fedotov
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
#include <QProcess>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QProcess    *AboutPandocProcess;

private slots:

    /* About Section */
    void AboutPandocProcessStart();
    void AboutPandocMessageBox( int ExitCode, QProcess::ExitStatus ExitStatus );
    void AboutPandocProcessError( QProcess::ProcessError Error );
    void aboutPandoQ();

};

#endif // MAINWINDOW_H
