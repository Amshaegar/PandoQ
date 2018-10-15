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

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QWidget>
#include <QTranslator>

namespace Ui {
class Settings;
}

/**
  * Settings class.
  */
class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_CancelPushButton_clicked();

    void on_SavePushButton_clicked();

private:
    Ui::Settings *ui;
    QTranslator translator;
    void changeEvent(QEvent *event); /*< Reimplemented for changing the language of the application.*/
};

#endif // SETTINGS_HPP
