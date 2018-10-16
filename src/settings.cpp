#include "settings.hpp"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    QSettings settings("PandoQ", "PandoQ");
    language = settings.value("language","en").toString();
    if (language.compare("en") == 0)
        ui->LangugesComboBox->setCurrentIndex(0);
    else if (language.compare("ru") == 0)
        ui->LangugesComboBox->setCurrentIndex(1);
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
    QSettings settings("PandoQ", "PandoQ");
    switch (ui->LangugesComboBox->currentIndex())
    {
        case 0: translator.load("./languages/pandoq_en");
                settings.setValue("language", "en");
                break;
        case 1: translator.load("./languages/pandoq_ru");
                settings.setValue("language", "ru");
                break;
    }

    QCoreApplication::installTranslator(&translator);


    this->close();
}

void Settings::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    } else
        QWidget::changeEvent(event);
}
