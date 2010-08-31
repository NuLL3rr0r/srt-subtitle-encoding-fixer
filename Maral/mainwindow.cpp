#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(444, 133);

    ui->cmbEncoding->addItem("Windows-1250");
    ui->cmbEncoding->addItem("Windows-1251");
    ui->cmbEncoding->addItem("Windows-1252");
    ui->cmbEncoding->addItem("Windows-1253");
    ui->cmbEncoding->addItem("Windows-1254");
    ui->cmbEncoding->addItem("Windows-1255");
    ui->cmbEncoding->addItem("Windows-1256");
    ui->cmbEncoding->addItem("Windows-1257");
    ui->cmbEncoding->addItem("Windows-1258");
    ui->cmbEncoding->setCurrentIndex(6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked()
{
    QFileInfo fi(ui->lnePath->text());
    QString file = QFileDialog::getOpenFileName(this,
                                                tr("Pick a File"),
                                                ui->lnePath->text() == "" ? QDir::homePath() + "/Desktop/" : fi.absolutePath(),
                                                tr("Subtitles (*.srt *.sub);;All Files (*.*)"));

    if (!file.isNull()) {
        ui->lnePath->setText(file);
        ui->cmbEncoding->setEnabled(true);
        ui->btnConv->setEnabled(true);
    }
}

void MainWindow::on_btnConv_clicked()
{
/*    QString data;
    QFile source(ui->lnePath->text());
    if (source.open(QIODevice::ReadOnly | QIODevice::Text)) {
        data = source.readAll().to;
    }

    QFileInfo fi(source);

    QFile target(fi.absolutePath() + "/" + fi.completeBaseName() + "__utf8" + "." + fi.suffix());
    if (target.open(QIODevice::WriteOnly|QIODevice::Text))  {
        target.write(data.toUtf8());
    }*/

    QFile source(ui->lnePath->text());
    if (source.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QFileInfo fi(source);
        QFile target(fi.absolutePath() + "/" + fi.completeBaseName() + "__utf8" + "." + fi.suffix());

        if (target.open(QIODevice::WriteOnly|QIODevice::Text))  {
            QTextStream in(&source);
            QTextStream out(&target);

            in.setCodec(ui->cmbEncoding->currentText().toUtf8());
            out.setCodec("UTF-8");
			out.setGenerateByteOrderMark(true);

            out << in.readAll();

            target.flush();
            target.close();
            source.close();

            QMessageBox::information(this, tr("Done"), tr("Converted Successfully!"));
        }
    }
}
