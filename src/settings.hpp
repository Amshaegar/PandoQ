#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QWidget>

namespace Ui {
class Settings;
}

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
};

#endif // SETTINGS_HPP
