#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <vector>
#include "lsregression.h"
#include "csvreader.h"
#include "robustregression.h"
#include "residual.h"

/* This class is the main window of linear regression project
 * This window contains a lot of buttons, labels, data table,
 * widgets, edit lines, etc.
 * This is the main part of GUI of this project*/

class QAction;
class QLabel;


class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void putdata();

    /*Put summary method, which will put summary in the first tab in tab widget,
    * Parameters are summary and the text get from the lsregression summary method*/
    void putsummary(std::vector<std::vector<std::string>> summary, std::vector<std::string> text);



private slots:

    /*These two privite slots are defined by myself,
     * which are used to detect the state change of
     * the check box in the data table          */
    void col_select_test();
    void row_select_test();

    /*These slots are corresponding to the buttons.
     * The name are defined by built-in rule
     * The implementation are made by me.*/
    void on_exitButton_clicked();

    void on_setxbutton_clicked();

    void on_setybutton_clicked();

    void on_methodcombobox_activated(const QString &arg1);

    void on_execButton_clicked();

    void on_cookmeasure_clicked();

    void on_setSbutton_clicked();

    void on_setTbutton_clicked();

    void on_residualbutton_clicked();

    void on_deletebutton_clicked();

    void on_restorebutton_clicked();

private:

    /* This part are all the privite csvreader,
     * regression, and regression stack,
     * In order to share data between functions*/
    csvReader pri_csvreader;
    LSregression pri_ls_simple;
    LSregression pri_ls_multi;
    LSregression pri_ls_rob;
    robustregression pri_robregression;
    residualStack<LSregression> stack_ls;
    residualStack<LSregression> stack_multi;
    residualStack<LSregression> stack_rob;
    int deletetimes = 0;

    Ui::MainWindow *ui;

    bool isdouble(std::string);

    void putResidualsummary(std::vector<std::vector<std::string> > & analysis);

    void plotRegressionLine(double beta0, double beta1);

    void plotScatter(arma::mat & X, arma::mat & Y, LSregression);

    void plotScatter(arma::mat & X, arma::mat & Y, robustregression);

    double significance_num = 0.05;
    double t_num = 2;

    int dataY;
    std::vector<int> dataX;

    std::vector<int> outlierIndex;
    std::vector<int> nonOutlier;

    std::vector<int> deleterow;

    int methodtype = 0;

    // These bool state are used to do button activation
    bool methodActivated = false;
    bool col_set = false;
    bool isrobust = false;
    bool isXset = false;
    bool isYset = false;
    bool iscookmeasure = false;

    int residualRow;
    int residualCol;

};


#endif // MAINWINDOW_H
