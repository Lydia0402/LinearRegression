#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include "ui_dialog1.h"

/*This class called dialog1 is actually a "login" dialog.
 * Contains mainly following several functions:
 * 1. Prompt user to input the csv file want to use
 * 2. Judge the validity of the file or path.
 * 3. Collect the imformation (Whether the csv file hava a title) */

//namespace DialogUI {
//class Dialog1;
//}

class Dialog1 : public QDialog, Ui::Dialog1
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);


//    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void on_lineEdit_textChanged();

//private:
//    DialogUI::Dialog1 *ui2;

    void on_enterButton_clicked();
    void on_checkBox_clicked();

    void on_exitButton_clicked();
};

#endif // DIALOG1_H
