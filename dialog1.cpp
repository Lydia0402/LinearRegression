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
#include "QTableWidget"
#include "csvreader.h"
#include <string>

csvReader csvreader;

bool checkboxval = false;

Dialog1::Dialog1(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

//    QRegExp regExp("");
//    lineEdit->setValidator(new QRegExpValidator(regExp, this));

//    connect(enterButton, SIGNAL(clicked()), this, SLOT(accept()));
//    connect(enterButton, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked(checkboxval)));
}

Dialog1::~Dialog1()
{
    //
}


void Dialog1::on_lineEdit_textChanged()
{
    enterButton->setEnabled(lineEdit->hasAcceptableInput());
}


void Dialog1::on_checkBox_clicked()
{
    checkboxval = !checkboxval;
}


void Dialog1::on_enterButton_clicked()
{
//    if (checkboxval == true ) QMessageBox::warning(this,tr("Warning"),("checkbox."),QMessageBox::Yes);  // check the state of check box
    std::string s = this->lineEdit->text().toStdString();
    if (csvreader.readData(s, checkboxval))                                     // Judge
        accept();
    else
    {
        QString ss = QString::fromStdString(csvreader.getWarning());
        QMessageBox::warning(this,tr("Warning"),(ss),QMessageBox::Yes);    // warning
        this->lineEdit->clear();                                           // clear
        this->lineEdit->setFocus();                                        // back to line 1
    }
}


void Dialog1::on_exitButton_clicked()
{
    this->close();
}
