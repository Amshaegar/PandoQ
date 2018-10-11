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

/** Class that is working with Pandoc CLI.
  * Run in a separate than Main Window thread.
  */

class PandocThread : public QObject
{
    Q_OBJECT

    /** Pandoc process for getting information about Pandoc.
     */
    QProcess*    aboutPandocProcess;

    /** Pandoc process for getting the list of supported input formats.
     */
    QProcess*    inputFormatsPandocProcess;

    /** Pandoc process for getting the list of supported output formats.
     */
    QProcess*    outputFormatsPandocProcess;

    /** Pandoc process that converts the text.
     */
    QProcess*    convertPandocProcess;



public:
    explicit PandocThread(QObject *parent = nullptr);

signals:
    void AboutPandocMessage(QString message);
    void InputFormatsPandocMessage(QStringList inputFormats);
    void OutputFormatsPandocMessage(QStringList outputFormats);
    void OutputConvertPandocMessage();
    void ErrorHappened(QString message);

private slots:
    // Slots for getting external signals
    void AboutPandoc();
    void GetIOFormats();
    void Convert(QString inputFormat,
                 QString outputFormat,
                 QString inputFile,
                 QString outputFile);

    // Slots for getting internal signals
    void AboutPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus );
    void InputFormatsPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus );
    void OutputFormatsPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus );
    void ConvertPandocInfo( int ExitCode, QProcess::ExitStatus ExitStatus );
    void ErrorHandler( QProcess::ProcessError Error );

};

#endif // PANDOCTHREAD_HPP
