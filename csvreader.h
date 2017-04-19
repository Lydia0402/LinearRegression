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
    csvReader();
    bool readData(std::string filename, bool title = true);
    arma::mat displaydata();
    std::string getWarning();
    std::vector<std::string> getTitleList();

private:
    arma::mat data; // Used to store the all the data. Size: nRows * nCols
    int nRows,nCols; /* nRows is the number of data points (usually denoted as n)
                        nCols is the number of attributes  (usually denoted as p) */
    std::vector<std::string> titleList; // Used to store the name of attributes.
    std::string warning; //Used to store the warning message
    void clearAllInstantVariables(); // Clear all the content

};

#endif // CSVREADER_H
