#ifndef CSVREADER_H
#define CSVREADER_H

#include <armadillo>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class csvReader
{

public:
    csvReader(); //Constructor

    bool readData(std::string filename, bool title = true);
    /* Used to read a csv file into this->data (type: arma::mat).
     * The first parameter is (the path plus) the name of the csv file. If this
     * file cannot be opened, this->warning (type: std::string) will be modified
     * to warn that case.
     * The second parameter indicates whether the first line of the csv file is
     * a series of attributes' names. If true, the first line will be read into
     * this->titleList (type: std::vector<std::string>). If false, this->titleList
     * will be set up as its default value: ["x1","x2",...,"xnCols"].
     * If anything goes wrongly in this reading process, this->warning will be
     * changed to indicate the corresbonding error. Please use getWarning() to get
     * the warning message.*/

    arma::mat getDataMatrix();

    std::string getWarning();

    std::vector<std::string> getTitleList();

    int getNRows();

    int getNCols();

private:
    arma::mat data; // Used to store the all the data. Size: nRows * nCols

    int nRows,nCols; /* nRows is the number of data points (usually denoted as n)
                        nCols is the number of attributes  (usually denoted as p) */

    std::vector<std::string> titleList;  // Used to store the name of attributes.

    std::string warning; //Used to store the warning message

    void clearAllInstantVariables(); // Clear all the content

    bool tryLineBreak(std::string filename, bool title, char lineBreak);

};

#endif // CSVREADER_H
