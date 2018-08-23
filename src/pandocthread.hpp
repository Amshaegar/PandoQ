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

#ifndef PANDOCTHREAD_HPP
#define PANDOCTHREAD_HPP

#include <QObject>
#include <QProcess>

class PandocThread : public QObject
{
    Q_OBJECT

    QProcess    *aboutPandocProcess;


public:
    explicit PandocThread(QObject *parent = nullptr);
    ~PandocThread();

signals:
    void AboutPandocMessage(QString message);

private slots:
    void AboutPandoc();
    void AboutPandocMessageBox( int ExitCode, QProcess::ExitStatus ExitStatus );
    void AboutPandocProcessError( QProcess::ProcessError Error );

};

#endif // PANDOCTHREAD_HPP
