//#include "mainwindow.h"
#include "dialog1.h"
#include <QApplication>
#include <QDialog>

//#include "ui_mainwindow.h"
#include "ui_dialog1.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Ui::Dialog1 ui;
    QDialog *dialog = new QDialog;
    ui.setupUi(dialog);
    dialog->show();

    return app.exec();
}
