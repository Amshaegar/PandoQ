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
                                              aboutPandocProcess(new QProcess(this)),
                                              inputFormatsPandocProcess(new QProcess(this)),
                                              outputFormatsPandocProcess(new QProcess(this)),
                                              convertPandocProcess(new QProcess(this))
{
    // About Pandoc signal handlers
    connect(aboutPandocProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ),    this,   SLOT( AboutPandocInfo( int, QProcess::ExitStatus ) )  );
    connect(aboutPandocProcess, SIGNAL( error( QProcess::ProcessError )  ),         this,   SLOT( ErrorHandler(QProcess::ProcessError) )     );

    // Input/ouptut formats signal handlers
    connect(inputFormatsPandocProcess,  SIGNAL( finished( int, QProcess::ExitStatus ) ),    this,   SLOT( InputFormatsPandocInfo( int, QProcess::ExitStatus ) ) );
    connect(inputFormatsPandocProcess,  SIGNAL( error( QProcess::ProcessError )  ),         this,   SLOT( ErrorHandler(QProcess::ProcessError) )                );
    connect(outputFormatsPandocProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ),    this,   SLOT( OutputFormatsPandocInfo( int, QProcess::ExitStatus ) ));
    connect(outputFormatsPandocProcess, SIGNAL( error( QProcess::ProcessError )  ),         this,   SLOT( ErrorHandler(QProcess::ProcessError) )                );

    // Convert
    connect(convertPandocProcess, SIGNAL( finished( int, QProcess::ExitStatus )  ), this,   SLOT( ConvertPandocInfo(int,QProcess::ExitStatus))  );
    connect(convertPandocProcess, SIGNAL( error( QProcess::ProcessError )  ),       this,   SLOT( ErrorHandler(QProcess::ProcessError) )        );

}

// Slots for getting external signals
void PandocThread::AboutPandoc()
{
    QStringList arg;
    arg << "--version";
    aboutPandocProcess->start( "pandoc", arg );
}

void PandocThread::GetIOFormats()
{
    QStringList arg;
    arg << "--list-input-formats";
    inputFormatsPandocProcess->start( "pandoc", arg );

    arg.clear();
    arg << "--list-output-formats";
    outputFormatsPandocProcess->start( "pandoc", arg );
}

void PandocThread::Convert(QString inputFormat,
                           QString outputFormat,
                           QString inputFile,
                           QString outputFile)
{
    QStringList arg;
    arg << inputFile << "--from" << inputFormat <<"--to" << outputFormat << "-o" << outputFile;
    convertPandocProcess->start( "pandoc", arg );
}


// Slots for getting internal signals
void PandocThread::AboutPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        emit ErrorHappened(tr("Pandoc crashed."));
        return;
    }
    else if (ExitCode != 0)
    {
        emit ErrorHappened(tr("Pandoc showing version information failed."));
        return;
    }

    QString message = aboutPandocProcess->readAllStandardOutput().data();
    emit AboutPandocMessage( message );
}

void PandocThread::InputFormatsPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        emit ErrorHappened(tr("Pandoc crashed."));
        return;
    }
    else if (ExitCode != 0)
    {
        emit ErrorHappened(tr("Pandoc showing version information failed."));
        return;
    }

    QStringList inputFormats = QString(inputFormatsPandocProcess->readAllStandardOutput().data()).split("\r\n");
    emit InputFormatsPandocMessage(inputFormats);
}

void PandocThread::OutputFormatsPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        emit ErrorHappened(tr("Pandoc crashed."));
        return;
    }
    else if (ExitCode != 0)
    {
        emit ErrorHappened(tr("Pandoc showing version information failed."));
        return;
    }

    QStringList outputFormats = QString(outputFormatsPandocProcess->readAllStandardOutput().data()).split("\r\n");
    emit OutputFormatsPandocMessage(outputFormats);
}

void PandocThread::ConvertPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus )
{
    if (ExitStatus == QProcess::CrashExit)
    {
        emit ErrorHappened(tr("Pandoc crashed."));
        return;
    }
    else if (ExitCode != 0)
    {
        emit ErrorHappened(tr("Pandoc showing version information failed."));
        return;
    }

    emit OutputConvertPandocMessage();
}

void PandocThread::ErrorHandler( QProcess::ProcessError Error )
{
    if ( Error == QProcess::FailedToStart )
    {
        emit ErrorHappened(tr("Can not start Pandoc proccess. Check the pandoc software availability."));
    }
}
