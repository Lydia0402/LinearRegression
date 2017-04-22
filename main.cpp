#include "mainwindow.h"
#include "dialog1.h"
#include <QApplication>
#include <QDialog>
//#include <QMainWindow>

//#include "ui_mainwindow.h"
#include "ui_dialog1.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Ui::MainWindow w;

// Two ways to show a dialog.
//    Ui::Dialog1 ui;
//    QDialog *dialog = new QDialog;
//    ui.setupUi(dialog);
//    dialog->show();


    MainWindow m;
    Dialog1 d1;
    d1.show();

    if(d1.exec()==QDialog::Accepted){
        m.show();
        return app.exec();
    }

//    w.show();


    return app.exec();
}
