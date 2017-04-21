#ifndef LSREGRESSION_H
#define LSREGRESSION_H
#include "csvreader.h"
#include <armadillo>

class LSregression
{
public:
    LSregression();
    void setX();
    void setY();

private:
    arma::mat X;
    arma::mat Y;
    double Sxx,Sxy;
    int n,k;

};

#endif // LSREGRESSION_H
