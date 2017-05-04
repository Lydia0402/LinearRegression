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

void MainWindow::putdata()
{
    QStandardItemModel *model;
    model = new QStandardItemModel(csvreader.getNRows(), csvreader.getNCols() + 1);
    this->datatable->setModel(model);

    // Set header (title) for the data table.
    model->setHeaderData(0, Qt::Horizontal, (" "));
    for (int i = 1; i < csvreader.getNCols() + 1; i++)
    {
        QString str = QString::fromStdString(csvreader.getTitleList()[i - 1]);
        model->setHeaderData(i, Qt::Horizontal, (str));
    }

    // Set data for each cell in data table.
    arma::mat matrix = csvreader.getDataMatrix();
    for (int i = 1; i < csvreader.getNRows() + 1; i++)
    {
        QModelIndex rownum = model->index(i, 0, QModelIndex());
        model->setData(rownum, i);
        for (int j = 1; j < csvreader.getNCols() + 1; j++)
        {
            QModelIndex index = model->index(i, j, QModelIndex());
            model->setData(index, matrix(i - 1, j - 1));
        }
    }

    for (int i = 1; i < csvreader.getNCols() + 1; i++)
    {
        QStandardItem *Item = new QStandardItem();
        Item->setCheckable(true);
        Item->setCheckState(Qt::Unchecked);
        model->setItem(0, i, Item);
    }
//    this->datatable->setColumnWidth(0, 40);
    QHeaderView* headerView = this->datatable->verticalHeader();
    headerView->setHidden(true);
    this->datatable->resizeColumnsToContents();
//    this->datatable->horizontalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);
    this->datatable->show();

//    connect(this->datatable, SIGNAL(cellChanged(int,int)), this->datatable, SLOT(colselecttest(int, int)));
}

void MainWindow::col_select_test(int row, int col)
{
//    if (model)
}


// void changeTest(int row, int col)
// {
//     if(tableWidget ->item(row, col)->checkState() == Qt::Checked) //选中
//         ...
//     else
//         ...
// }

//01	QTableWidget *tableWidget = new QTableWidget;
//02	QTableWidgetItem *firstColumn = new QTableWidgetItem(tr("test"));
//03	firstColumn->setCheckState(Qt::Checked);//加入复选框
//04	connect(tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));
//05	void changeTest(int row, int col)
//06	{
//07	    if(tableWidget ->item(row, col)->checkState() == Qt::Checked)
//08	        ...
//09	    else
//10	        ...
//11	}
