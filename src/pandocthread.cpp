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

#include "pandocthread.hpp"

PandocThread::PandocThread(QObject *parent) : QObject(parent),
                                              aboutPandocProcess(new QProcess(this))
{
    connect(aboutPandocProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ),    this,   SLOT( AboutPandocInfo( int, QProcess::ExitStatus ) )  );
    connect(aboutPandocProcess, SIGNAL( error( QProcess::ProcessError )  ),         this,   SLOT( ErrorHandler(QProcess::ProcessError) )     );
}

void PandocThread::AboutPandoc()
{
    QStringList arg;
    arg << "--version";
    aboutPandocProcess->start( "pandoc", arg );
}

void PandocThread::ErrorHandler( QProcess::ProcessError Error )
{
    if ( Error == QProcess::FailedToStart )
    {
        emit ErrorHappened(tr("Can not start Pandoc proccess. Check the pandoc software availability."));
    }
}

void PandocThread::AboutPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        emit ErrorHappened(tr("Pandoc crashed."));
    }
    else if (ExitCode != 0)
    {
        emit ErrorHappened(tr("Pandoc showing version information failed."));
    }

    QString message = aboutPandocProcess->readAllStandardOutput().data();
    emit AboutPandocMessage( message );
}
