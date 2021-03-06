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

#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Settings section
    QSettings settings("PandoQ", "PandoQ");

    // Translation section
    QTranslator translator;
    QString language = settings.value("language","en").toString();

    if(language.compare("en") == 0)
        translator.load("./languages/pandoq_en");
    else if(language.compare("ru") == 0)
        translator.load("./languages/pandoq_ru");

    QCoreApplication::installTranslator(&translator);


    try
    {
        w.show();
    }
    catch(...)
    {
        std::cout<<"Unhandled exception.";
    }


    return a.exec();
}
