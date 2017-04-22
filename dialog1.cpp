//#include "dialog1.h"
//#include "ui_dialog1.h"

//Dialog1::Dialog1(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Dialog1)
//{
//    ui->setupUi(this);
//}

//Dialog1::~Dialog1()
//{
//    delete ui;
//}

#include <QtGui>
#include "dialog1.h"
#include "qmessagebox.h"

Dialog1::Dialog1(QWidget *parent) : QDialog(parent){
    setupUi(this);

//    QRegExp regExp("");
//    lineEdit->setValidator(new QRegExpValidator(regExp, this));

//    connect(enterButton, SIGNAL(clicked()), this, SLOT(accept()));

}
void Dialog1::on_lineEdit_textChanged(){
    enterButton->setEnabled(lineEdit->hasAcceptableInput());
}

void Dialog1::on_enterButton_clicked()
{
    if(this->lineEdit->text()==tr("123"))                    // Judge
        accept();
        else
        {
           QMessageBox::warning(this,tr("Warning"),("Invalid file name or path."),QMessageBox::Yes);    // warning
           this->lineEdit->clear();                      // clear
           this->lineEdit->setFocus();              // back to line 1
        }
}
