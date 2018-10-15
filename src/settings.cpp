#include "settings.hpp"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_CancelPushButton_clicked()
{
    this->close();
}

void Settings::on_SavePushButton_clicked()
{
    this->close();
}
