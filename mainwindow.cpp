#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include "QStandardItem"
#include "csvreader.h"
#include <iostream>
#include <QObject>

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
    model = new QStandardItemModel(csvreader.getNRows() + 1, csvreader.getNCols() + 1);
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

    // Set ckeckbox.
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

    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(col_select_test()));
}

void MainWindow::col_select_test()
{
    choosebutton->setEnabled(true);
    std::cout << "change";
    QStandardItemModel *_model = static_cast<QStandardItemModel*>(this->datatable->model());
    for (int i = 1; i < csvreader.getNCols() + 1; i++){
        QStandardItem *Item = _model->item(0, i);
        if(Item->checkState() == Qt::Checked){

            std::cout << "Yeah";
        }

    }
}

