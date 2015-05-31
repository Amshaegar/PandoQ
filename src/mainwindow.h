#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QProcess    *AboutPandocProcess;

private slots:

    /* About Pandoc Section */
    void AboutPandocProcessStart();
    void AboutPandocMessageBox( int ExitCode, QProcess::ExitStatus ExitStatus );
    void AboutPandocProcessError( QProcess::ProcessError Error );

};

#endif // MAINWINDOW_H
