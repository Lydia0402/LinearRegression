#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <vector>

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
    void putdata();



private slots:
    void on_exitButton_clicked();
    void col_select_test();
    void on_setxbutton_clicked();

    void on_setybutton_clicked();

    void on_methodcombobox_activated(const QString &arg1);

    void on_execButton_clicked();

    void on_cookmeasure_clicked();

    void on_setSbutton_clicked();

    void on_setTbutton_clicked();

private:
    Ui::MainWindow *ui;

    double significance_num;
    double t_num;
    std::vector<int> dataX;
    int dataY;

    int methodtype = 0;
    bool methodActivated = false;
    bool col_set = false;
    bool isrobust = false;
    bool isXset = false;
    bool isYset = false;
    bool iscookmeasure = false;

//protected:
//    void closeEvent(QCloseEvent *event);
};


#endif // MAINWINDOW_H
