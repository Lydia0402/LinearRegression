#include <armadillo>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "csvreader.h"
#include "lsregression.h"
#include "robustregression.h"

#include <QApplication>
#include <QDialog>
#include "mainwindow.h"
#include "dialog1.h"

//#include <QMainWindow>

//#include "ui_mainwindow.h"
#include "ui_dialog1.h"
#include <QTableWidget>
#include <QTableWidgetItem>


int main(int argc, char *argv[]){
//    csvReader a;
//    if (!a.readData("/Users/alan/Code/CPP_regression_project/LinearRegression-Lydia/res/data3.csv",true)) std::cout <<a.getWarning();
//    for (std::string b: a.getTitleList() ) {
//        std::cout <<b<<'\n';
//    }
//    arma::cout <<a.getDataMatrix();
//    LSregression b(a);
//    std::vector<int> in = {1};
//    if (!b.set(in,0)) std::cout<<b.getWarning();
//    else {
////        arma::cout<< b.getY();
////        arma::cout<< b.getX();
////        arma::mat c = b.getX();
////        arma::cout <<c.size();
//        b.solve();
//        arma::cout <<median(b.getbetaHat()) <<"Yes";
//        b.CookMeasure().raw_print(std::cout);
//        robustregression c(b);
//        arma::cout << c.solve();

    QApplication app(argc, argv);
//            Ui::MainWindow w;

//         Two ways to show a dialog.
//            Ui::Dialog1 ui;

//            QDialog *dialog = new QDialog;
//            ui.setupUi(dialog);
//            dialog->show();

    MainWindow main;
    Dialog1 d1;
    d1.show();

    if (d1.exec() == QDialog::Accepted){
        main.show();
        return app.exec();
    }

//    return app.exec();


//    return 0;


//    }
}
