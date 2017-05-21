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
#include "ui_dialog1.h"
#include <QTableWidget>
#include <QTableWidgetItem>


int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    MainWindow main;
    Dialog1 d1;
    d1.show();
    if (d1.exec() == QDialog::Accepted)
    {
        main.show();
        main.putdata();
        return app.exec();
    }
    return 0;

}
