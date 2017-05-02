#ifndef ROBUSTREGRESSION_H
#define ROBUSTREGRESSION_H
#include "csvreader.h"
#include <armadillo>
#include "lsregression.h"

class robustregression
{
public:
    robustregression(csvReader read);
    robustregression(LSregression LSR);
    bool setObjective();
    bool set(int x, int y);
    arma::mat solve();

private:
    csvReader reader;
    LSregression initial;
    arma::mat X,Y;
    arma::mat generateW(arma::mat beta);
};

#endif // ROBUSTREGRESSION_H
