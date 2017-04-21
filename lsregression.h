#ifndef LSREGRESSION_H
#define LSREGRESSION_H
#include "csvreader.h"
#include <armadillo>

class LSregression
{
public:
    LSregression(csvReader read);

    bool set(std::vector<int> listOfSelected,int y);

    std::string getWarning();
    arma::mat getX();
    arma::mat getY();
    arma::mat getHat();

private:
    csvReader reader;
    arma::mat data;
    arma::mat X;
    arma::mat Y;
    arma::mat Hat;
    int n,k;
    std::string warning;
    bool solve();
};

#endif // LSREGRESSION_H
