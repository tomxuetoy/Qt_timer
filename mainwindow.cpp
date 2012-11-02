#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCore>
#include <QtGui>

int hour, minute, second;
float totalTime;
int percent = 100;
QTimer timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(reminder()));

    onethread = new myThread(this);
    connect(onethread, SIGNAL(progressValue(int)),
            this, SLOT(showProgress(int)));
}

void MainWindow::showProgress(int Value)
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

    qDebug("totalTime is %d", totalTime);

    onethread->start(QThread::NormalPriority);
}

//Thread part...
myThread::myThread(QObject *parent)
    : QThread(parent)
{

}

void myThread::run()
{
    QTimer timer2;
    connect(&timer2, SIGNAL(timeout()), this, SLOT(updateProgress()));
    timer2.start(1000);
    exec();
}

void myThread::updateProgress()
{
    int step;

    step = 100/(totalTime/1000);
    percent = percent - step;
    emit progressValue(percent);
    qDebug("currentValue is %d %f", percent, totalTime);
}
