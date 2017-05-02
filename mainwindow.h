#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
class QAction;
class QLabel;

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    void putdata();
//protected:
//    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
