#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCore>
#include <QtGui>

int hour, minute, second;
float totalTime;
int percent = 100;
QTimer timer, timer2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(reminder()));

//    onethread = new myThread(this);
    connect(&timer2, SIGNAL(timeout()), this, SLOT(updateProgress()));
    connect(this, SIGNAL(progressValue(float)),
            this, SLOT(showProgress(float)));
}

void MainWindow::showProgress(float Value)
{
    ui->progressBar->setValue(Value);
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

    hour = ui->spinBox_h->text().toInt(&ok, 10);
    minute = ui->spinBox_m->text().toInt(&ok, 10);
    second = ui->spinBox_s->text().toInt(&ok, 10);

    totalTime = (hour*3600 + minute*60 + second)*1000;
    timer.setSingleShot(true);
    timer.start(totalTime); // 1 Hz update rate

    qDebug("totalTime is %f", totalTime);

//    onethread->start(QThread::NormalPriority);

    float step;
    step = totalTime/100;
    timer2.start(step);
}

//Thread part...
//myThread::myThread(QObject *parent)
//    : QThread(parent)
//{

//}

//void myThread::run()
//{
//    QTimer timer2;
//    connect(&timer2, SIGNAL(timeout()), this, SLOT(updateProgress()));
//    timer2.start(1000);
//    exec();
//}

void MainWindow::updateProgress()
{
    percent = percent - 1;
    if(percent <= 0)
        percent = 0;
    emit progressValue(percent);
    if(percent <= 0)    // run once more
        timer2.stop();
    qDebug("percent is %d", percent);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->progressBar->setValue(100);
    ui->spinBox_h->setValue(0);
    ui->spinBox_m->setValue(0);
    ui->spinBox_s->setValue(0);
    percent = 100;
}
