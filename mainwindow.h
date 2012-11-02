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
    void showProgress(float);
    void updateProgress();

private slots:
    void on_pushButton_clicked();
    void reminder();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
//    myThread *onethread;

signals:
    void progressValue(float x);
};

#endif // MAINWINDOW_H
