#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <vector>
#include "lsregression.h"
#include "csvreader.h"

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
    void putsummary(std::vector<std::vector<std::string>> summary, std::vector<std::string> text);



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

    void on_residualbutton_clicked();

private:
    Ui::MainWindow *ui;

    bool isdouble(std::string);
    void putResidualsummary(std::vector<std::vector<std::string> > analysis);

    double significance_num = 0.05;
    double t_num = 2;
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
