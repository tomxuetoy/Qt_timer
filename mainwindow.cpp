#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCore>
#include <QtGui>

int hour, minute, second;
QTimer timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(reminder()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reminder()
{
    // TODO: add popup window
    qDebug("Timer timeout");

    QMessageBox::warning(this,tr("Timeout"),
                         tr("Go ahead!"),
                         QMessageBox::Yes,
                         NULL);
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int totalTime;

    hour = ui->spinBox_h->text().toInt(&ok, 10);
    minute = ui->spinBox_m->text().toInt(&ok, 10);
    second = ui->spinBox_s->text().toInt(&ok, 10);

    totalTime = (hour*3600 + minute*60 + second)*1000;
    timer.setSingleShot(true);
    timer.start(totalTime); // 1 Hz update rate

    qDebug("totalTime is %d", totalTime);
}
