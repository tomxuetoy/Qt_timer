#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showProgress(int);
    void updateProgress();

private slots:
    void on_pushButton_clicked();
    void reminder();

private:
    Ui::MainWindow *ui;
//    myThread *onethread;

signals:
    void progressValue(int x);
};

#endif // MAINWINDOW_H
