#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>

#include "ui_dialog1.h"
//namespace Ui {
//class Dialog1;
//}

class Dialog1 : public QDialog, public Ui::Dialog1
{
    Q_OBJECT

public:
    Dialog1(QWidget *parent = 0);

//    explicit Dialog1(QWidget *parent = 0);
//    ~Dialog1();

private slots:
    void on_lineEdit_textChanged();
//private:
//    Ui::Dialog1 *ui;

    void on_enterButton_clicked();
};

#endif // DIALOG1_H
