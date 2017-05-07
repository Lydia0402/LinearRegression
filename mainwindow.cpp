#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QObject>
#include "QStandardItem"
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <iostream>
#include <vector>
#include <sstream>
#include "csvreader.h"
#include "lsregression.h"

extern csvReader csvreader;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{

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

    // Resize
    this->datatable->resizeColumnsToContents();

    // Set the table become no edit mode. (Ban users from editing the table)
    this->datatable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Show
    this->tab2->setVisible(false);
    this->tab2->setEnabled(false);
    this->tabWidget->setCurrentIndex(0);
    this->datatable->show();

    /* Connect itemchanged signal to slots.
    *This will listen to the checkbox in table.*/
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(col_select_test()));
}


void MainWindow::col_select_test()
{
    if (methodActivated)
    {
        setxbutton->setEnabled(true);
        setybutton->setEnabled(true);
//        cookmeasure->setCheckable(true);

    }
    else col_set = true;

//    QStandardItemModel *_model = static_cast<QStandardItemModel*>(this->datatable->model());
//    for (int i = 1; i < csvreader.getNCols() + 1; i++){
//        QStandardItem *Item = _model->item(0, i);
//        if(Item->checkState() == Qt::Checked){
//            std::cout << "Yeah";
//        }
//    }
}


void MainWindow::on_setxbutton_clicked()
{
    isXset = true;
    dataX.clear();

    QStandardItemModel *_model = static_cast<QStandardItemModel*>(this->datatable->model());

    // Button set part.
    if (isYset)
    {
        setSbutton->setEnabled(true);
        cookmeasure->setCheckable(true);
        execButton->setEnabled(true);
    }

    if (isrobust && isYset)
    {
        setTbutton->setEnabled(true);
    }

    // Get the changed checkbox.

//    std::vector<int> tempvec;
    for (int i = 1; i < csvreader.getNCols() + 1; i++)
    {
        QStandardItem *Item = _model->item(0, i);
        if (Item->checkState() == Qt::Checked)
        {
           dataX.push_back(i - 1);
           Item->setCheckState(Qt::Unchecked);
        }
    }

    if (methodtype == 1 && dataX.size() != 1)
    {
        QMessageBox::warning(this,tr("Warning"),("Please select only one X for simple linear regression."), QMessageBox::Yes);
    }

    // Background change.
    int datasize = dataX.size();
    for (int i = 0; i < datasize; i++)
    {
        int colnum = dataX[i];
        for (int j = 1; j < csvreader.getNRows() + 1; j++)
        {
            QStandardItem *item = _model->item(j, colnum + 1);
            item->setForeground(QBrush(QColor(0, 0, 255)));
        }
    }

}


void MainWindow::on_setybutton_clicked()
{
    isYset = true;
    // Button set part.
    if (isXset)
    {
        setSbutton->setEnabled(true);
//        cookmeasure->setCheckable(true);
        execButton->setEnabled(true);
    }

    if (isrobust && isXset)
    {
        setTbutton->setEnabled(true);
    }

    // Get the changed checkbox
    QStandardItemModel *_model = static_cast<QStandardItemModel*>(this->datatable->model());
    std::vector<int> tempvec;
    for (int i = 1; i < csvreader.getNCols() + 1; i++)
    {
        QStandardItem *Item = _model->item(0, i);
        if (Item->checkState() == Qt::Checked)
        {
           tempvec.push_back(i - 1);
           Item->setCheckState(Qt::Unchecked);
        }
    }

    if (tempvec.size() != 1)
    {
        QMessageBox::warning(this,tr("Warning"),("Invalid operation, Please select only one Y for regression."), QMessageBox::Yes);
    }
    else
    {
        dataY = tempvec[0];

        // Background change.
        for (int j = 1; j < csvreader.getNRows() + 1; j++)
        {
            QStandardItem *item = _model->item(j, dataY + 1);
            item->setForeground(QBrush(QColor(255, 0, 0)));
        }
    }
}


void MainWindow::on_methodcombobox_activated(const QString &arg1)
{
    // Background reset.
    QStandardItemModel *_model = static_cast<QStandardItemModel*>(this->datatable->model());
    for (int i = 1; i < csvreader.getNRows() + 1; i++)
    {
        for (int j = 1; j < csvreader.getNCols() + 1; j++)
        {
            QStandardItem *item = _model->item(i, j);
            item->setForeground(QBrush(QColor(0, 0, 0)));
        }
    }

    if (arg1 == "Please select")
    {
        cookmeasure->setCheckable(false);
        setxbutton->setEnabled(false);
        setybutton->setEnabled(false);
        setSbutton->setEnabled(false);
        execButton->setEnabled(false);
        setTbutton->setEnabled(false);
    }

    if (arg1 == "Simple Least Square Regression")
    {
        methodtype = 1;
        /* This part is to ensure when the user change method during operation,
         * all the button will be disabled again.                               */
        isXset = isYset = false;
        cookmeasure->setCheckable(false);
        setxbutton->setEnabled(false);
        setybutton->setEnabled(false);
        setSbutton->setEnabled(false);
        execButton->setEnabled(false);
        setTbutton->setEnabled(false);

        methodActivated = true;
        if (col_set){
            setxbutton->setEnabled(true);
            setybutton->setEnabled(true);
        }

    }
    if (arg1 == "Multiple Least Square Regression")
    {
        methodtype = 2;
        /* This part is to ensure when the user change method during operation,
         * all the button will be disabled again.                               */
        isXset = isYset = false;
        cookmeasure->setCheckable(false);
        setxbutton->setEnabled(false);
        setybutton->setEnabled(false);
        setSbutton->setEnabled(false);
        execButton->setEnabled(false);
        setTbutton->setEnabled(false);
        methodActivated = true;

        if (col_set){
            setxbutton->setEnabled(true);
            setybutton->setEnabled(true);
        }

    }
    if (arg1 == "Robust Regression")
    {
        methodtype = 3;
        /* This part is to ensure when the user change method during operation,
         * all the button will be disabled again.                               */
        isXset = isYset = false;
        cookmeasure->setCheckable(false);
        setxbutton->setEnabled(false);
        setybutton->setEnabled(false);
        setSbutton->setEnabled(false);
        execButton->setEnabled(false);
        setTbutton->setEnabled(false);
        methodActivated = true;
        isrobust = true;

        if (col_set){
            setxbutton->setEnabled(true);
            setybutton->setEnabled(true);
        }

    }
}


bool MainWindow::isdouble(std::string s)
{
        std::stringstream sin(s);
        double t;
        char p;
        if (!(sin >> t))
        {
            return false;
        }
        if (sin >> p){
            return false;
        }
        else
        {
             return true;
        }
}


void MainWindow::on_execButton_clicked()
{
    cookmeasure->setCheckable(true);
    residualbutton->setEnabled(true);
//    this->datatable->setVisible(false);
    if (methodtype == 1)
    {
        LSregression lsregression(csvreader);
        lsregression.set(dataX, dataY);
        lsregression.setSignificance(significance_num);
        lsregression.solve();
        std::vector<std::vector<std::string>> summary;
        std::vector<std::string> text;
        lsregression.printSummary(summary, text);
        putsummary(summary, text);
    }

}


void MainWindow::on_cookmeasure_clicked()
{
    iscookmeasure = !iscookmeasure;
}


void MainWindow::on_setSbutton_clicked()
{
    std::string s = this->significanceedit->text().toStdString();
    if (isdouble(s))
    {
        std::stringstream ss(s);
        double temp;
        ss >> temp;
        if (temp < 0 || temp > 1)
        {
            QMessageBox::warning(this,tr("Warning"),("Please input a number in (0, 1)."), QMessageBox::Yes);
        }
        else
        {
            ss >> significance_num;
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),("Please input a number."), QMessageBox::Yes);
    }
    this->significanceedit->clear();

}

void MainWindow::on_setTbutton_clicked()
{
    std::string s = this->huberedit->text().toStdString();
    if (isdouble(s))
    {
        std::stringstream ss(s);
        double temp;
        ss >> temp;
        if (temp < 0)
        {
            QMessageBox::warning(this,tr("Warning"),("Please input a number greater than 0."), QMessageBox::Yes);
        }
        else
        {
            ss >> t_num;
        }

    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),("Please input a number."), QMessageBox::Yes);
    }
    this->significanceedit->clear();

}


void MainWindow::putsummary(std::vector<std::vector<std::string> > summary, std::vector<std::string> text)
{
    int size1 = summary.size();
    for (int i = 0; i < size1; i++)
    {
        int size2 = summary[i].size();

        std::string str;

        for (int j = 0; j < size2; j++)
        {
            str += summary[i][j] + "\t";
        }

        QString qstr = QString::fromStdString(str);
        this->textBrowser->append(qstr);
    }
    this->textBrowser->append(" ");
    int size3 = text.size();

    for (int i = 0; i <size3; i++)
    {
        std::string textstr;
        textstr += text[i];
        QString qstring = QString::fromStdString(textstr);
        this->textBrowser->append(qstring);
    }
    this->textBrowser->append(" ");
    this->textBrowser->append(" ");
    this->textBrowser->append(" ");
}


void MainWindow::plotSetData()
{
    arma::mat originmat = csvreader.getDataMatrix();
    QVector<double> x(csvreader.getNRows()), y(csvreader.getNRows());

    int col_x = dataX[0];
    int col_y = dataY;
    for (int i = 0; i < csvreader.getNRows(); i++)
    {
        x[i] = originmat(i, col_x);
        y[i] = originmat(i, col_y);
    }
    this->graph->xAxis->setLabel("X");
    this->graph->yAxis->setLabel("Y");
    this->graph->xAxis->setRange(-50, 100);
    this->graph->yAxis->setRange(-3000, 10000);
    this->graph->addGraph();
    this->graph->graph(0)->setPen(QColor(50, 50, 50, 255));
    this->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    this->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    this->graph->graph(0)->setData(x, y);
    this->graph->replot();
}



void MainWindow::on_residualbutton_clicked()
{
    if (methodtype == 1)
    {
        plotSetData();
//        this->tab2->setEnabled(true);

    }
}



