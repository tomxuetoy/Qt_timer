#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class myThread : public QThread
{
  Q_OBJECT

public:
    myThread(QObject *parent = 0);
    void run();

public slots:
    void updateProgress();

signals:
    void progressValue(int x);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showProgress(int);

private slots:
    void on_pushButton_clicked();
    void reminder();

private:
    Ui::MainWindow *ui;
    myThread *onethread;
};

#endif // MAINWINDOW_H
