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
    QSettings settings("PandoQ","PandoQ");

    switch (ui->LangugesComboBox->currentIndex())
    {
        case 1: translator.load("./languages/pandoq_ru");
                QCoreApplication::installTranslator(&translator);
                settings.setValue("language", "ru");
                break;
    }


    this->close();
}

void Settings::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    } else
        QWidget::changeEvent(event);
}
