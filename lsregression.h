#ifndef LSREGRESSION_H
#define LSREGRESSION_H
#include "csvreader.h"
#include <armadillo>

class LSregression

{

public:
    LSregression();

    LSregression(csvReader read);

    bool setDataSource(csvReader read);

    bool set(std::vector<int> listOfSelected,int y);

    arma::mat CookMeasure();

    std::string getWarning();
    arma::mat getX();
    arma::mat getY();
    arma::mat getHat();
    arma::mat getbetaHat();
    arma::mat getYHat();
    arma::mat getResidual();
    csvReader getReader();
    int getN();
    int getK();
    bool solve();

private:
    csvReader reader;
    arma::mat data;
    arma::mat X,Y;
    arma::mat betaHat, Hat, YHat, residual, CookResiduals;
    int n,k;
    double SSR,SSres,MSres,SStotal,meanY;
    std::string warning;

};

#endif // LSREGRESSION_H
