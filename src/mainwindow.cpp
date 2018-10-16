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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PandocThread *pandocThreadWorker = new PandocThread;
    pandocThreadWorker->moveToThread(&pandocThreadThread);
    connect(&pandocThreadThread, &QThread::finished, pandocThreadWorker, &QObject::deleteLater);
    pandocThreadThread.start();

    connect(ui->actionExit,         SIGNAL( triggered() ),                 qApp,                 SLOT( quit()               )   );
    connect(ui->actionAbout_Pandoc, SIGNAL( triggered() ),                 pandocThreadWorker,   SLOT( AboutPandoc()        )   );
    connect(pandocThreadWorker,     SIGNAL( AboutPandocMessage(QString) ), this,                 SLOT( aboutPandoc(QString) )   );
    connect(ui->actionAbout_PandoQ, SIGNAL( triggered() ),                 this,                 SLOT( aboutPandoQ()        )   );
    connect(ui->actionAbout_Qt,     SIGNAL( triggered() ),                 qApp,                 SLOT( aboutQt()            )   );

    // Pandoc input/output formats
    connect(this,               SIGNAL( getIOFormats() ),                           pandocThreadWorker,   SLOT( GetIOFormats())             );
    connect(pandocThreadWorker, SIGNAL( InputFormatsPandocMessage(QStringList)),    this,                 SLOT( inputFormats(QStringList))  );
    connect(pandocThreadWorker, SIGNAL( OutputFormatsPandocMessage(QStringList)),   this,                 SLOT( outputFormats(QStringList)) );

    // Pandoc convert
    connect(this,  SIGNAL( Convert(QString,QString,QString,QString)),   pandocThreadWorker,   SLOT( Convert(QString,QString,QString,QString))   );
    connect(pandocThreadWorker, SIGNAL( OutputConvertPandocMessage()),  this,                 SLOT( converted() )                               );

    // Pandoc error handler
    connect(pandocThreadWorker, SIGNAL( ErrorHappened(QString) ),   this,   SLOT( pandocThreadErrorHandler(QString))   );

    emit getIOFormats();
}

MainWindow::~MainWindow()
{
    delete ui;
    pandocThreadThread.quit();
    pandocThreadThread.wait();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    } else
        QWidget::changeEvent(event);
}

/* About Section */

void MainWindow::aboutPandoc(QString message)
{
    QMessageBox::about(this, tr("About Pandoc"), message);
}

void MainWindow::aboutPandoQ()
{
    QString aboutPandoQText =tr( "PandoQ is the Qt GUI frontend for Pandoc written by using C++ language.\n\n" \
                                 "This is free software, and you are welcome to redistribute it under certain conditions.\n\n" \
                                 "This program comes with ABSOLUTELY NO WARRANTY.\n\n"\
                                 "See the GNU General Public License for more details.\n\n" \
                                 "Copyright 2015,2018 Maxim Fedotov (fedotovmo@gmail.com)");

    QMessageBox::about(this,tr("About PandoQ"),aboutPandoQText);
}

/* IOFormats section */
void MainWindow::inputFormats(QStringList inputFormats)
{
    ui->FromTextTypeComboBox->insertItems(0,inputFormats);
    ui->FromFileTypeComboBox->insertItems(0,inputFormats);
}

void MainWindow::outputFormats(QStringList outputFormats)
{
    ui->ToTextTypeComboBox->insertItems(0,outputFormats);
    ui->ToFileTypeComboBox->insertItems(0,outputFormats);
}

void MainWindow::converted()
{
    QFile output("output");
    if (output.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->ToPlainTextEdit->clear();
        QTextStream in(&output);
        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->ToPlainTextEdit->appendPlainText(line);
        }
        output.close();
    }

    // Clean after convertation - remove temporary files.
    QFile::remove("output");
    QFile::remove("input");

    ui->ConvertTextPushButton->setEnabled(true);
    ui->ConvertFilePushButton->setEnabled(true);
}

void MainWindow::pandocThreadErrorHandler(QString errorMessage)
{
    QMessageBox::warning(this,
                         tr("Error happened!"),
                         errorMessage,
                         QMessageBox::Ok
                         );
}

void MainWindow::on_ConvertTextPushButton_clicked()
{
    QString inputFormat = ui->FromTextTypeComboBox->currentText();
    QString outputFormat = ui->ToTextTypeComboBox->currentText();

    QFile input("input");
    if (!input.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream in(&input);
    in << "";
    in << ui->FromPlainTextEdit->toPlainText();
    input.close();

    QFile output("output");
    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&output);
    out << "";
    output.close();

    emit Convert(inputFormat, outputFormat, "input", "output");
    ui->ConvertTextPushButton->setDisabled(true);
}

void MainWindow::on_ChooseFileFromPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open File From"), "", "");
    ui->PathToFileFromLineEdit->setText(fileName);
}

void MainWindow::on_ChooseFileToPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open File To"), "", "");
    ui->PathToFileToLineEdit->setText(fileName);
}

void MainWindow::on_ConvertFilePushButton_clicked()
{
    QString inputFormat = ui->FromFileTypeComboBox->currentText();
    QString outputFormat = ui->ToFileTypeComboBox->currentText();
    QString inputFile = ui->PathToFileFromLineEdit->text();
    QString outputFile = ui->PathToFileToLineEdit->text();

    emit Convert(inputFormat, outputFormat, inputFile, outputFile);
    ui->ConvertFilePushButton->setDisabled(true);
}

void MainWindow::on_actionConfigure_PandoQ_triggered()
{
    settingsWidget.show();
}
