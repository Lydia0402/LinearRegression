#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include "QStandardItem"
#include "csvreader.h"
#include <iostream>

extern csvReader csvreader;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
//    ,ui (new Ui::MainWindow)
{
//    ui->setupUi(this);
    setupUi(this);
}

MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

//QTableWidget *tableWidget = new QTableWidget;

void MainWindow::putdata(){
    for (unsigned long i = 0; i < csvreader.getTitleList().size(); i++){
        std::cout << csvreader.getTitleList()[i]<< std::endl;
    }

    /*QStandardItemModel *model;
    model = new QStandardItemModel(csvreader.getNRows(), csvreader.getNCols());
    this->datatable->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Label"));
    model->setHeaderData(1, Qt::Horizontal, tr("Quantity"));

    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 2; ++column) {
            QModelIndex index = model->index(row, column, QModelIndex());
            model->setData(index, QVariant((row+1) * (column+1)));
        }
    }
    this->datatable->show()*/;
}
//tableWidget->setColumnCount(5); //设置列数为5
//tableWidget->setWindowTitle("QTableWidget & Item");
//tableWidget->resize(350, 200); //设置表格
//QStringList header;
//header<<"Month"<<"Description";
//tableWidget->setHorizontalHeaderLabels(header);
//tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
//tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
//tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

//tableWidget->setItem(0,1,new QTableWidgetItem(QIcon("images/IED.png"), "Jan's month"));
//tableWidget->setItem(1,1,new QTableWidgetItem(QIcon("images/IED.png"), "Feb's month"));
//tableWidget->setItem(2,1,new QTableWidgetItem(QIcon("images/IED.png"), "Mar's month"));
//tableWidget->show();
